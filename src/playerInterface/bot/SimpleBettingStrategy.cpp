#include "include/playerInterface/bot/SimpleBettingStrategy.h"

namespace playerInterface
{
namespace bot
{

SimpleBettingStrategy::SimpleBettingStrategy()
{

}

SimpleBettingStrategy::~SimpleBettingStrategy()
{

}

pokerGame::Decision SimpleBettingStrategy::makePreFlopDecision(const pokerGame::Hand& hand, float minBet)
{
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::HandType::PAIR)
    {
        decision.choice = pokerGame::CALL;
        decision.bet = minBet;
    }
    else if(hand.getSumOfPower() > 16)
    {
        decision.choice = pokerGame::CHECK;
        decision.bet = 0;
    }
    else
    {
        decision.choice = pokerGame::FOLD;
        decision.bet = 0;
    }
    return decision;
}

pokerGame::Decision SimpleBettingStrategy::makePostFlopDecision(const pokerGame::Hand& hand, float minBet)
{
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::HandType::HIGH_CARD)
    {
        if(minBet == 0)
        {
            decision.choice = pokerGame::CHECK;
            decision.bet = 0;
        }
        else
        {
            decision.choice = pokerGame::FOLD;
            decision.bet = 0;
        }
    }
    else if(hand.getHandValue().type >= pokerGame::STRAIGHT)
    {
        decision.choice = pokerGame::CALL;
        decision.bet = minBet;
    }
    else
    {
        decision.choice = pokerGame::CHECK;
        decision.bet = 0;
    }
    return decision;
}

}
}
