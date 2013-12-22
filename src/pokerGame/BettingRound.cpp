#include "include/pokerGame/BettingRound.h"
#include <iostream>

namespace pokerGame
{

BettingRound::BettingRound() : gameContext(0),bet(0), sharedCards(), numberOfRaises(0)
{
}

void BettingRound::start(GameContext* gameContext, std::vector<Card> sharedCards)
{
    initialize(gameContext, sharedCards);
    float currentBet;
    do {
        currentBet = bet;
        for (int i = gameContext->bigBlindIndex; i < gameContext->players.size(); i++) {
            playerTurn(gameContext->players[i]);
        }
        for (int i = 0; i < gameContext->bigBlindIndex; i++) {
            playerTurn(gameContext->players[i]);
        }
    } while (bet != currentBet);
}

void BettingRound::initialize(GameContext* gameContext, std::vector<Card> sharedCards){
    this->gameContext = gameContext;
    this->sharedCards = sharedCards;
    this->bet = gameContext->bigBlind;
}

void BettingRound::playerTurn(PokerPlayer* player)
{
    announcePlayerTurn(player);
    announcements(player);
    if(player->isPlaying()) {
        Decision d = player->makeDecision(bet, gameContext->bigBlind, sharedCards, numberOfRaises, gameContext->players.size());
        if (d.choice == pokerGame::CALL) {
            bet += d.bet;
            numberOfRaises++;
        }
    }
}

void BettingRound::announcePlayerTurn(PokerPlayer* player)
{
    for (PokerPlayer* p: gameContext->players) {
        p->seePlayerTurn(*player);
    }
}

void BettingRound::announcements(PokerPlayer* player)
{
    player->seeDealer(*gameContext->players[gameContext->dealerIndex]);
    player->seeBigBlind(*gameContext->players[gameContext->bigBlindIndex], gameContext->bigBlind);
}

float BettingRound::getMinBet() const
{
    return bet;
}

}
