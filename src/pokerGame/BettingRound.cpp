#include "include/pokerGame/BettingRound.h"
#include <iostream>

namespace pokerGame
{

BettingRound::BettingRound() : gameContext(0), sharedCards(), numberOfRaises(0), currentPlayer(0)
{
}

void BettingRound::start(GameContext* gameContext, std::vector<Card> sharedCards)
{
    initialize(gameContext, sharedCards);
    float currentBet;

    bool entirePass = false;

    do {
        nextPlayer();
        if (currentPlayer == gameContext->dealerIndex) {
            entirePass = true;
        }
        playerTurn(gameContext->players[currentPlayer]);


    } while (!(entirePass && allPotsAreEven()));
}

void BettingRound::initialize(GameContext* gameContext, std::vector<Card> sharedCards){
    this->gameContext = gameContext;
    this->sharedCards = sharedCards;
    this->currentPlayer = gameContext->dealerIndex;
}

void BettingRound::playerTurn(Player* player)
{
    announcePlayerTurn(player);
    announcements(player);
    if(player->isPlaying()) {
        Decision d = player->makeDecision(getCurrentMinimumBid(), gameContext->bigBlind, sharedCards, numberOfRaises, gameContext->players.size());
        if (d.choice == pokerGame::CALL) {
            numberOfRaises++;
        }
    }
}

void BettingRound::announcePlayerTurn(Player* player)
{
    for (Player* p: gameContext->players) {
        p->seePlayerTurn(*player);
    }
}

void BettingRound::announcements(Player* player)
{
    player->seeDealer(*gameContext->players[gameContext->dealerIndex]);
    player->seeBigBlind(*gameContext->players[gameContext->bigBlindIndex], gameContext->bigBlind);
}

float BettingRound::getCurrentMinimumBid() const
{
    float maxBid = gameContext->bigBlind;
    for(Player* p: gameContext->players) {
        if (p->getPot() > maxBid) {
            maxBid = p->getPot();
        }
    }
    return maxBid;
}

void BettingRound::nextPlayer() {
    currentPlayer++;
    if (currentPlayer == gameContext->players.size()) {
        currentPlayer = 0;
    }
    currentPlayer = getNextPlayingPlayer(currentPlayer);

}

int BettingRound::getNextPlayingPlayer(int player) {
    int tmp;
    for (tmp = player; tmp < gameContext->players.size(); tmp++) {
        if (gameContext->players[tmp]->isPlaying()) {
            return tmp;
        }
    }
    for (tmp = 0; tmp < player; tmp++) {
        if (gameContext->players[tmp]->isPlaying()) {
            return tmp;
        }
    }
}

bool BettingRound::allPotsAreEven() const {
    bool first = true;
    float pot;
    for (Player* player: gameContext->players) {
        if (player->isPlaying()) {
            if (first) {
                pot = player->getPot();
                first = false;
            } else {
                if (player->getPot() != pot && !player->isAllIn()) {
                    return false;
                }
            }
        }
    }
    return true;
}

}
