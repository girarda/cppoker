#include "include/playerInterface/bot/BettingStrategy.h"

namespace playerInterface
{
namespace bot
{

BettingStrategy::BettingStrategy()
{

}

BettingStrategy::~BettingStrategy()
{

}

pokerGame::Decision BettingStrategy::makeDecision(const pokerGame::Hand& hand, float minBet)
{
    if(isPreFlopHand(hand))
    {
        return makePreFlopDecision(hand, minBet);
    }
    else
    {
        return makePostFlopDecision(hand, minBet);
    }
}

bool BettingStrategy::isPreFlopHand(const pokerGame::Hand& hand) const
{
    return hand.getSize() == 2;
}

}
}
