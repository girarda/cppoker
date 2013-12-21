#ifndef BETTINGROUND_H
#define BETTINGROUND_H

#include <vector>
#include "pokerGame/PokerPlayer.h"
#include "GameContext.h"

namespace pokerGame
{

class BettingRound
{
public:
    BettingRound();

    virtual void start(GameContext* gameContext, std::vector<Card> sharedCards);
    virtual float getMinBet() const;

private:
    void playerTurn(PokerPlayer* player);
    void announcePlayerTurn(PokerPlayer* player);
    void announcements(PokerPlayer* player);

    void initialize(GameContext* gameContext, std::vector<Card> sharedCards);

    GameContext* gameContext;
    float bet;
    std::vector<Card> sharedCards;
    int numberOfRaises;
};

}

#endif
