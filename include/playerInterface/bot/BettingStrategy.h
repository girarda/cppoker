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
    virtual pokerGame::Decision makeDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind);

protected:
    virtual pokerGame::Decision makePreFlopDecision(std::vector<pokerGame::Card> hole, float minBet, float bigBlind) = 0;
    virtual pokerGame::Decision makePostFlopDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind) = 0;

private:
    bool isPreFlopHand(const pokerGame::Hand& hand) const;
};

}
}
#endif
