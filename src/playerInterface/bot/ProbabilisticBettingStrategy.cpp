#include "playerInterface/bot/ProbabilisticBettingStrategy.h"

namespace playerInterface
{
namespace bot
{

ProbabilisticBettingStrategy::ProbabilisticBettingStrategy(pokerGame::HandStrengthEvaluator* handEvaluator) : handStrengthEvaluator(handEvaluator)
{
}

ProbabilisticBettingStrategy::~ProbabilisticBettingStrategy()
{
}

pokerGame::Decision ProbabilisticBettingStrategy::makePreFlopDecision(std::vector<pokerGame::Card> hole, float minBet, float bigBlind, int numberOfRaises, int numberOfPlayers)
{
    // TODO: Find a good way to evaluate hole's value
    // In the meantime, this is the same decision making as SimpleBettingStrategy's pre flop
    pokerGame::Hand hand(hole);
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::HandType::PAIR)
    {
        decision.choice = pokerGame::CALL;
        decision.bet = minBet + bigBlind;
    }
    else if(hand.getSumOfPower() > 16)
    {
        decision.choice = pokerGame::CHECK;
        decision.bet = minBet;
    }
    else
    {
        decision.choice = pokerGame::FOLD;
        decision.bet = 0;
    }
    return decision;
}

pokerGame::Decision ProbabilisticBettingStrategy::makePostFlopDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind, int numberOfRaises, int numberOfPlayers)
{
    pokerGame::Hand hand(hole, sharedCards);
    pokerGame::Decision decision;
    double p = calculateCoefficient(hole, sharedCards, numberOfRaises, numberOfPlayers);
    if (p > 0.8) {
        decision.choice = pokerGame::CALL;
        decision.bet = minBet + bigBlind;
    } else if (p > 0.4 || minBet == 0) {
        decision.choice = pokerGame::CHECK;
        decision.bet = minBet;
    } else {
        decision.choice = pokerGame::FOLD;
        decision.bet = 0;
    }
    return decision;
}

double ProbabilisticBettingStrategy::calculateCoefficient(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, int numberOfRaises, int numberOfPlayers) {
    double p = handStrengthEvaluator->evaluate(hole, sharedCards, numberOfPlayers);

    // Decision depends on the number of players
    p *= (1 + numberOfPlayers/20);

    // Be riskier in further rounds?

    // Be more careful if there are lots of raises
    if(numberOfRaises > 3) {
        p -= 0.3;
    }
    return p;
}

}

}

