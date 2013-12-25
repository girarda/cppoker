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
    virtual pokerGame::Decision makePreFlopDecision(std::vector<pokerGame::card::Card> hole, float minBet, float bigBlind, pokerGame::modeling::BettingContext* bettingContext, std::vector<pokerGame::modeling::OpponentModel> opponents);
    virtual pokerGame::Decision makePostFlopDecision(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, float minBet, float bigBlind, pokerGame::modeling::BettingContext* bettingContext, std::vector<pokerGame::modeling::OpponentModel> opponents);
    virtual pokerGame::Decision decideBet(float minBet, float bigBlind, int oppponentsWithBetterEstimatedHandStrength, int opponentsModeledCount) = 0;

private:
    pokerGame::card::HandStrengthEvaluator* handStrengthEvaluator;
    BettingStrategy* secondaryBettingStrategy;
};

}
}
#endif
