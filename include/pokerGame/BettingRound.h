#ifndef BETTINGROUND_H
#define BETTINGROUND_H

#include <vector>
#include "pokerGame/PokerPlayer.h"

namespace pokerGame
{

class BettingRound
{
public:
    BettingRound();

    virtual void start(std::vector<PokerPlayer*> roundPlayers, float blind, int dealerPlayerIndex, int bigBlindPlayerIndex, int smallBlindPlayerIndex, std::vector<Card> );
    virtual float getMinBet() const;

private:
    void playerTurn(PokerPlayer* player);
    void announcePlayerTurn(PokerPlayer* player);
    void announcements(PokerPlayer* player);

    void initialize(std::vector<PokerPlayer*> roundPlayers, float blind, int dealerPlayerIndex, int bigBlindPlayerIndex, int smallBlindPlayerIndex, std::vector<Card> sharedCards);

    std::vector<PokerPlayer*> players;
    float bigBlind;
    float bet;

    int dealerIndex;
    int bigBlindIndex;
    int smallBlindIndex;

    std::vector<Card> sharedCards;
};

}

#endif
