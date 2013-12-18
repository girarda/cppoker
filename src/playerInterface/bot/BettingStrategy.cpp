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

pokerGame::Decision BettingStrategy::makeDecision(const pokerGame::Hand& hand, float minBet, float bigBlind)
{
    if(isPreFlopHand(hand))
    {
        return makePreFlopDecision(hand, minBet, bigBlind);
    }
    else
    {
        return makePostFlopDecision(hand, minBet, bigBlind);
    }
}

bool BettingStrategy::isPreFlopHand(const pokerGame::Hand& hand) const
{
    return hand.getSize() == 2;
}

}
}
