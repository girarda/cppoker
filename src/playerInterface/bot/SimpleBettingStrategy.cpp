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

pokerGame::Decision SimpleBettingStrategy::makePreFlopDecision(std::vector<pokerGame::Card> hole, float minBet, float bigBlind, int numberOfRaises)
{
    pokerGame::Hand hand(hole);
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::HandType::PAIR)
    {
        decision.choice = pokerGame::CALL;
        decision.bet = bigBlind;
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

pokerGame::Decision SimpleBettingStrategy::makePostFlopDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind, int numberOfRaises)
{
    pokerGame::Hand hand(hole, sharedCards);
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
        decision.bet = bigBlind;
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
