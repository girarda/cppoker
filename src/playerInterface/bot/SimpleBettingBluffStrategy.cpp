#include "playerInterface/bot/SimpleBettingBluffStrategy.h"

namespace playerInterface
{
namespace bot
{

SimpleBettingBluffStrategy::SimpleBettingBluffStrategy()
{

}

SimpleBettingBluffStrategy::~SimpleBettingBluffStrategy()
{

}

pokerGame::Decision SimpleBettingBluffStrategy::makePreFlopDecision(std::vector<pokerGame::Card> hole, float minBet, float bigBlind, int numberOfRaises)
{
    pokerGame::Hand hand(hole);
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::HandType::PAIR || hand.getSumOfPower() < 9)
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

pokerGame::Decision SimpleBettingBluffStrategy::makePostFlopDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind, int numberOfRaises)
{
    pokerGame::Hand hand(hole, sharedCards);
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::HandType::HIGH_CARD || hand.getHandValue().type >= pokerGame::THREE_OF_A_KIND)
    {
        decision.choice = pokerGame::CALL;
        decision.bet = bigBlind;
    }
    else if(minBet == 0)
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

}
}
