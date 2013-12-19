#ifndef BETTINGROUND_H
#define BETTINGROUND_H

#include <vector>
#include "pokerGame/PokerPlayer.h"

namespace pokerGame
{

class BettingRound
{
public:
    BettingRound(std::vector<PokerPlayer*> roundPlayers, float blind, int dealerPlayerIndex, int bigBlindPlayerIndex, int smallBlindPlayerIndex);

    void start();

    void playerTurn(PokerPlayer* player);
    void announcePlayerTurn(PokerPlayer* player);
    void announcements(PokerPlayer* player);

    float getMinBet() const;

private:
    std::vector<PokerPlayer*> players;
    float bigBlind;
    float bet;

    int dealerIndex;
    int bigBlindIndex;
    int smallBlindIndex;
};

}

#endif
