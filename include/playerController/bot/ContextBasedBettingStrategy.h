#ifndef BOTCONTEXTBASEDBETTINGSTRATEGY_H
#define BOTCONTEXTBASEDBETTINGSTRATEGY_H
#include "BettingStrategy.h"
#include "pokerGame/card/HandStrengthEvaluator.h"

namespace playerController {
namespace bot {

class ContextBasedBettingStrategy: public BettingStrategy{
public:
    ContextBasedBettingStrategy(pokerGame::card::HandStrengthEvaluator* handEvaluator, BettingStrategy* secondBettingStrategy);
    virtual ~ContextBasedBettingStrategy();

protected:
    virtual pokerGame::Decision makePreFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents);
    virtual pokerGame::Decision makePostFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents);
    virtual pokerGame::Decision decideBet(float minBet, float bigBlind, int oppponentsWithBetterEstimatedHandStrength, int opponentsModeledCount) = 0;

private:
    pokerGame::card::HandStrengthEvaluator* handStrengthEvaluator;
    BettingStrategy* secondaryBettingStrategy;
};

}
}
#endif
