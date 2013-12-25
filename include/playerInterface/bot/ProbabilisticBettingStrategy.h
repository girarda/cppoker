#ifndef PROBABILISTICBETTINGSTRATEGY_H
#define PROBABILISTICBETTINGSTRATEGY_H

#include "BettingStrategy.h"
#include "pokerGame/card/HandStrengthEvaluator.h"
#include "pokerGame/simulator/PreFlopStatistics.h"

namespace playerInterface {
namespace bot {

class ProbabilisticBettingStrategy : public BettingStrategy {
public:
    ProbabilisticBettingStrategy(pokerGame::card::HandStrengthEvaluator* handEvaluator, pokerGame::simulator::PreFlopStatistics* statistics);
    ~ProbabilisticBettingStrategy();

protected:
    virtual pokerGame::Decision makePreFlopDecision(std::vector<pokerGame::card::Card> hole, float minBet, float bigBlind, pokerGame::context::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents);
    virtual pokerGame::Decision makePostFlopDecision(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, float minBet, float bigBlind, pokerGame::context::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents);
    virtual double calculateCoefficient(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, pokerGame::context::BettingContext* bettingContext);

private:
    pokerGame::Decision makeDecisionBasedOnProbabilities(double p, float minBet, float bigBlind);

    pokerGame::card::HandStrengthEvaluator* handStrengthEvaluator;
    pokerGame::simulator::PreFlopStatistics* preFlopStatistics;

    static const double RAISE_THRESHOLD;
    static const double CALL_THRESHOLD;
};

}

}

#endif
