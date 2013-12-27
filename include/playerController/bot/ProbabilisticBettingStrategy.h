#ifndef PROBABILISTICBETTINGSTRATEGY_H
#define PROBABILISTICBETTINGSTRATEGY_H

#include "BettingStrategy.h"
#include "pokerGame/card/HandStrengthEvaluator.h"
#include "pokerGame/simulation/PreFlopStatistics.h"

namespace playerController {
namespace bot {

class ProbabilisticBettingStrategy : public BettingStrategy {
public:
    ProbabilisticBettingStrategy(pokerGame::card::HandStrengthEvaluator* handEvaluator, pokerGame::simulation::PreFlopStatistics* statistics);
    ~ProbabilisticBettingStrategy();

protected:
    virtual pokerGame::Decision makePreFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents);
    virtual pokerGame::Decision makePostFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents);
    virtual double calculateCoefficient(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, const pokerGame::modeling::BettingContext &bettingContext);

private:
    pokerGame::Decision makeDecisionBasedOnProbabilities(double p, float minBet, float bigBlind);

    pokerGame::card::HandStrengthEvaluator* handStrengthEvaluator;
    pokerGame::simulation::PreFlopStatistics* preFlopStatistics;

    static const double RAISE_THRESHOLD;
    static const double CALL_THRESHOLD;
};

}

}

#endif
