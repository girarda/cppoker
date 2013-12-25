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
    virtual pokerGame::Decision makePreFlopDecision(std::vector<pokerGame::card::Card> hole, float minBet, float bigBlind, pokerGame::modeling::BettingContext* bettingContext, std::vector<pokerGame::modeling::OpponentModel> opponents);
    virtual pokerGame::Decision makePostFlopDecision(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, float minBet, float bigBlind, pokerGame::modeling::BettingContext* bettingContext, std::vector<pokerGame::modeling::OpponentModel> opponents);
    virtual double calculateCoefficient(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, pokerGame::modeling::BettingContext* bettingContext);

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
