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
    virtual pokerGame::Decision makePreFlopDecision(std::vector<pokerGame::Card> hole, float minBet, float bigBlind);
    virtual pokerGame::Decision makePostFlopDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind);
};

}
}
#endif
