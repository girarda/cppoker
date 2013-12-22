#ifndef PROBABILISTICBETTINGSTRATEGY_H
#define PROBABILISTICBETTINGSTRATEGY_H

#include "BettingStrategy.h"
#include "pokerGame/HandStrengthEvaluator.h"

namespace playerInterface {
namespace bot {

class ProbabilisticBettingStrategy : public BettingStrategy {
public:
    ProbabilisticBettingStrategy(pokerGame::HandStrengthEvaluator* handEvaluator);
    ~ProbabilisticBettingStrategy();

protected:
    virtual pokerGame::Decision makePreFlopDecision(std::vector<pokerGame::Card> hole, float minBet, float bigBlind, int numberOfRaises, int numberOfPlayers);
    virtual pokerGame::Decision makePostFlopDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind, int numberOfRaises, int numberOfPlayers);
    virtual double calculateCoefficient(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, int numberOfRaises, int numberOfPlayers);

private:
    pokerGame::HandStrengthEvaluator* handStrengthEvaluator;
};

}

}

#endif
