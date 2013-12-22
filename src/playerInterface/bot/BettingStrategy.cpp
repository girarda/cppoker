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

pokerGame::Decision BettingStrategy::makeDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind, int numberOfRaises, int numberOfPlayers)
{
    if(sharedCards.empty())
    {
        return makePreFlopDecision(hole, minBet, bigBlind, numberOfRaises, numberOfPlayers);
    }
    else
    {
        return makePostFlopDecision(hole, sharedCards, minBet, bigBlind, numberOfRaises, numberOfPlayers);
    }
}

}
}
