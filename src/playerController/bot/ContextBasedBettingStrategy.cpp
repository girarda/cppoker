#include "playerController/bot/ContextBasedBettingStrategy.h"

namespace playerController {
namespace bot {

ContextBasedBettingStrategy::ContextBasedBettingStrategy(pokerGame::card::HandStrengthEvaluator* handEvaluator,BettingStrategy* secondBettingStrategy) : handStrengthEvaluator(handEvaluator), secondaryBettingStrategy(secondBettingStrategy) {
}

ContextBasedBettingStrategy::~ContextBasedBettingStrategy() {
}

pokerGame::Decision ContextBasedBettingStrategy::makePreFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents) {
    return secondaryBettingStrategy->makeDecision(holeCards, std::vector<pokerGame::card::Card>(), bettingContext, opponents);
}

pokerGame::Decision ContextBasedBettingStrategy::makePostFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents) {
    double handStrength = handStrengthEvaluator->evaluate(holeCards, sharedCards, bettingContext.getNumberOfPlayers());
    int opponentsModeledCount = 0;
    int oppponentsWithBetterEstimatedHandStrength = 0;

    for (pokerGame::modeling::OpponentModel opponent: opponents) {
        if (opponent.getNumberOfOccurrences() > 10 && opponent.getHandStrengthDeviation() <= 0.15) {
            opponentsModeledCount++;
            if (opponent.getHandStrengthAverage() > handStrength) {
                oppponentsWithBetterEstimatedHandStrength++;
            }
        }
    }

    if ((double) opponentsModeledCount / bettingContext.getNumberOfPlayers() < 0.15) {
        // If not enough context actions, fallback on secondary strategy
        return secondaryBettingStrategy->makeDecision(holeCards, sharedCards, bettingContext, opponents);
    } else {
        return decideBet(bettingContext.getMinBet(), bettingContext.getBigBlind(), oppponentsWithBetterEstimatedHandStrength, opponentsModeledCount);
    }
}

}
}
