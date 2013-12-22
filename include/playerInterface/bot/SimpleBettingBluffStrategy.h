#ifndef SIMPLEBETTINGBLUFFSTRATEGY_H
#define SIMPLEBETTINGBLUFFSTRATEGY_H

#include "BettingStrategy.h"

namespace playerInterface
{
namespace bot
{

class SimpleBettingBluffStrategy: public BettingStrategy
{
public:
    SimpleBettingBluffStrategy();
    virtual ~SimpleBettingBluffStrategy();

protected:
    virtual pokerGame::Decision makePreFlopDecision(std::vector<pokerGame::Card> hole, float minBet, float bigBlind, int numberOfRaises, int numberOfPlayers);
    virtual pokerGame::Decision makePostFlopDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind, int numberOfRaises, int numberOfPlayers);
};

}
}

#endif
