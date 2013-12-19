#include "include/pokerGame/BettingRound.h"
#include <iostream>

namespace pokerGame
{

BettingRound::BettingRound(std::vector<PokerPlayer*> roundPlayers, float blind, int dealerPlayerIndex, int bigBlindPlayerIndex, int smallBlindPlayerIndex) : players(roundPlayers), bigBlind(blind), bet(bigBlind), dealerIndex(dealerPlayerIndex), bigBlindIndex(bigBlindPlayerIndex), smallBlindIndex(smallBlindPlayerIndex)
{
}

void BettingRound::start()
{
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

void BettingRound::playerTurn(PokerPlayer* player)
{
    if(player->isPlaying()) {
        Decision d = player->makeDecision(bet, bigBlind);
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
