#include "include/pokerGame/BettingRound.h"
#include <iostream>

namespace pokerGame
{

BettingRound::BettingRound() : players(), bigBlind(0), bet(0), dealerIndex(0), bigBlindIndex(0), smallBlindIndex(0)
{
}

void BettingRound::start(std::vector<PokerPlayer*> roundPlayers, float blind, int dealerPlayerIndex, int bigBlindPlayerIndex, int smallBlindPlayerIndex, std::vector<Card> sharedCards)
{
    initialize(roundPlayers, blind, dealerPlayerIndex, bigBlindPlayerIndex, smallBlindPlayerIndex, sharedCards);
    float currentBet;
    do {
        currentBet = bet;
        for (int i = bigBlindIndex; i < players.size(); i++) {
            playerTurn(players[i]);
        }
        for (int i = 0; i < bigBlindIndex; i++) {
            playerTurn(players[i]);
        }
    } while (bet != currentBet);
}

void BettingRound::initialize(std::vector<PokerPlayer*> roundPlayers, float blind, int dealerPlayerIndex, int bigBlindPlayerIndex, int smallBlindPlayerIndex, std::vector<Card> sharedCards){
    players = roundPlayers;
    bigBlind = blind;
    bet = bigBlind;
    dealerIndex = dealerPlayerIndex;
    bigBlindIndex = bigBlindPlayerIndex;
    smallBlindIndex = smallBlindPlayerIndex;
    this->sharedCards = sharedCards;
}

void BettingRound::playerTurn(PokerPlayer* player)
{
    announcePlayerTurn(player);
    announcements(player);
    if(player->isPlaying()) {
        Decision d = player->makeDecision(bet, bigBlind, sharedCards);
        if (d.choice == pokerGame::CALL) {
            bet += d.bet;
        }
    }
}

void BettingRound::announcePlayerTurn(PokerPlayer* player)
{
    for (PokerPlayer* p: players) {
        p->seePlayerTurn(*player);
    }
}

void BettingRound::announcements(PokerPlayer* player)
{
    player->seeDealer(*players[dealerIndex]);
    player->seeBigBlind(*players[bigBlindIndex], bigBlind);
}

float BettingRound::getMinBet() const
{
    return bet;
}

}
