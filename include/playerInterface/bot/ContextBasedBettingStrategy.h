#ifndef BOTCONTEXTBASEDBETTINGSTRATEGY_H
#define BOTCONTEXTBASEDBETTINGSTRATEGY_H
#include "BettingStrategy.h"
#include "pokerGame/HandStrengthEvaluator.h"

namespace playerInterface {
namespace bot {

class ContextBasedBettingStrategy: public BettingStrategy{
public:
    ContextBasedBettingStrategy(pokerGame::HandStrengthEvaluator* handEvaluator, BettingStrategy* secondBettingStrategy);
    virtual ~ContextBasedBettingStrategy();

protected:
    virtual pokerGame::Decision makePreFlopDecision(std::vector<pokerGame::Card> hole, float minBet, float bigBlind, pokerGame::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents);
    virtual pokerGame::Decision makePostFlopDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind, pokerGame::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents);

    pokerGame::HandStrengthEvaluator* handStrengthEvaluator;
    BettingStrategy* secondaryBettingStrategy;
};

}
}
#endif
