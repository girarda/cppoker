#include "playerController/bot/ProbabilisticBettingStrategy.h"
#include "pokerGame/simulation/HoleCardsEquivalence.h"

namespace playerController {
namespace bot {

ProbabilisticBettingStrategy::ProbabilisticBettingStrategy(pokerGame::card::HandStrengthEvaluator* handEvaluator, pokerGame::simulation::PreFlopStatistics* statistics) : handStrengthEvaluator(handEvaluator), preFlopStatistics(statistics) {
}

ProbabilisticBettingStrategy::~ProbabilisticBettingStrategy() {
}

pokerGame::Decision ProbabilisticBettingStrategy::makePreFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents) {
    preFlopStatistics->load("../preflop_simulation.data");
    pokerGame::simulation::HoleCardsEquivalence equivalence(holeCards[0].getRank(), holeCards[1].getRank());
    double p = preFlopStatistics->getWinningProbability(&equivalence, bettingContext.getNumberOfPlayers());
    return makeDecisionBasedOnProbabilities(p, bettingContext.getMinBet(), bettingContext.getBigBlind());
}

pokerGame::Decision ProbabilisticBettingStrategy::makePostFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents) {
    double p = calculateCoefficient(holeCards, sharedCards, bettingContext);
    return makeDecisionBasedOnProbabilities(p, bettingContext.getMinBet(), bettingContext.getBigBlind());
}

double ProbabilisticBettingStrategy::calculateCoefficient(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, const pokerGame::modeling::BettingContext &bettingContext) {
    double p = handStrengthEvaluator->evaluate(holeCards, sharedCards, bettingContext.getNumberOfPlayers());

    // Decision depends on the number of players
    p *= (1 + bettingContext.getNumberOfPlayers()/20);

    // Be riskier in further rounds?

    // Be more careful if there are lots of raises
    if(bettingContext.hasManyRaises()) {
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
