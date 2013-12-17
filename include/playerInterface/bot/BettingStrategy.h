#ifndef BETTINGSTRATEGY_H
#define BETTINGSTRATEGY_H

#include "pokerGame/Hand.h"
#include "pokerGame/Decision.h"

namespace playerInterface
{
namespace bot
{

class BettingStrategy
{
public:
    BettingStrategy();
    virtual ~BettingStrategy();
    virtual pokerGame::Decision makeDecision(const pokerGame::Hand& hand, float minBet);

protected:
    virtual pokerGame::Decision makePreFlopDecision(const pokerGame::Hand& hand, float minBet) = 0;
    virtual pokerGame::Decision makePostFlopDecision(const pokerGame::Hand& hand, float minBet) = 0;

private:
    bool isPreFlopHand(const pokerGame::Hand& hand) const;
};

}
}
#endif
