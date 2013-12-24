#ifndef PROBABILISTICBETTINGSTRATEGY_H
#define PROBABILISTICBETTINGSTRATEGY_H

#include "BettingStrategy.h"
#include "pokerGame/HandStrengthEvaluator.h"
#include "pokerGame/simulator/PreFlopStatistics.h"

namespace playerInterface {
namespace bot {

class ProbabilisticBettingStrategy : public BettingStrategy {
public:
    ProbabilisticBettingStrategy(pokerGame::HandStrengthEvaluator* handEvaluator, pokerGame::simulator::PreFlopStatistics* statistics);
    ~ProbabilisticBettingStrategy();

protected:
    virtual pokerGame::Decision makePreFlopDecision(std::vector<pokerGame::Card> hole, float minBet, float bigBlind, pokerGame::BettingContext* bettingContext);
    virtual pokerGame::Decision makePostFlopDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind, pokerGame::BettingContext* bettingContext);
    virtual double calculateCoefficient(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, pokerGame::BettingContext* bettingContext);

private:
    pokerGame::Decision makeDecisionBasedOnProbabilities(double p, float minBet, float bigBlind);

    pokerGame::HandStrengthEvaluator* handStrengthEvaluator;
    pokerGame::simulator::PreFlopStatistics* preFlopStatistics;

    static const double RAISE_THRESHOLD;
    static const double CALL_THRESHOLD;
};

}

}

#endif
