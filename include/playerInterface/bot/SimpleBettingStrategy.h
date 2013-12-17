#ifndef SIMPLEBETTINGSTRATEGY_H
#define SIMPLEBETTINGSTRATEGY_H
#include "BettingStrategy.h"

namespace playerInterface
{
namespace bot
{

class SimpleBettingStrategy: public BettingStrategy
{
public:
    SimpleBettingStrategy();
    virtual ~SimpleBettingStrategy();

protected:
    virtual pokerGame::Decision makePreFlopDecision(const pokerGame::Hand& hand, float minBet);
    virtual pokerGame::Decision makePostFlopDecision(const pokerGame::Hand& hand, float minBet);
};

}
}
#endif
