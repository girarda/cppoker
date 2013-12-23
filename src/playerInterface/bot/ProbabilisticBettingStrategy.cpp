#include "playerInterface/bot/ProbabilisticBettingStrategy.h"
#include "pokerGame/HoleCardsEquivalence.h"

namespace playerInterface {
namespace bot {

ProbabilisticBettingStrategy::ProbabilisticBettingStrategy(pokerGame::HandStrengthEvaluator* handEvaluator, pokerGame::simulator::PreFlopStatistics* statistics) : handStrengthEvaluator(handEvaluator), preFlopStatistics(statistics) {
}

ProbabilisticBettingStrategy::~ProbabilisticBettingStrategy() {
}

pokerGame::Decision ProbabilisticBettingStrategy::makePreFlopDecision(std::vector<pokerGame::Card> hole, float minBet, float bigBlind, int numberOfRaises, int numberOfPlayers) {
    preFlopStatistics->load("../preflop_simulation.data");
    pokerGame::HoleCardsEquivalence equivalence(hole[0].getRank(), hole[1].getRank());
    double p = preFlopStatistics->getWinningProbability(&equivalence, numberOfPlayers);
    return makeDecisionBasedOnProbabilities(p, minBet, bigBlind);
}

pokerGame::Decision ProbabilisticBettingStrategy::makePostFlopDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind, int numberOfRaises, int numberOfPlayers) {
    double p = calculateCoefficient(hole, sharedCards, numberOfRaises, numberOfPlayers);
    return makeDecisionBasedOnProbabilities(p, minBet, bigBlind);
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

pokerGame::Decision ProbabilisticBettingStrategy::makeDecisionBasedOnProbabilities(double p, float minBet, float bigBlind) {
    pokerGame::Decision decision;
    if (p > RAISE_THRESHOLD) {
        decision.choice = pokerGame::RAISE;
        decision.bet = minBet + bigBlind;
    } else if (p > CALL_THRESHOLD || minBet == 0) {
        decision.choice = pokerGame::CALL;
        decision.bet = minBet;
    } else {
        decision.choice = pokerGame::FOLD;
        decision.bet = 0;
    }
    return decision;
}

const double ProbabilisticBettingStrategy::RAISE_THRESHOLD(0.8);
const double ProbabilisticBettingStrategy::CALL_THRESHOLD(0.4);


}
}
