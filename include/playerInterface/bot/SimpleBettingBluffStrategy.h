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
    virtual pokerGame::Decision makePreFlopDecision(const pokerGame::Hand& hand, float minBet, float bigBlind);
    virtual pokerGame::Decision makePostFlopDecision(const pokerGame::Hand& hand, float minBet, float bigBlind);
};

}
}

#endif
