#include "playerInterface/bot/ContextBasedBettingStrategy.h"

namespace playerInterface {
namespace bot {

ContextBasedBettingStrategy::ContextBasedBettingStrategy(pokerGame::HandStrengthEvaluator* handEvaluator,BettingStrategy* secondBettingStrategy) : handStrengthEvaluator(handEvaluator), secondaryBettingStrategy(secondBettingStrategy) {
}

ContextBasedBettingStrategy::~ContextBasedBettingStrategy() {
}

pokerGame::Decision ContextBasedBettingStrategy::makePreFlopDecision(std::vector<pokerGame::Card> hole, float minBet, float bigBlind, pokerGame::context::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents) {
    return secondaryBettingStrategy->makeDecision(hole, std::vector<pokerGame::Card>(), minBet, bigBlind, bettingContext, opponents);
}

pokerGame::Decision ContextBasedBettingStrategy::makePostFlopDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind, pokerGame::context::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents) {
    double handStrength = handStrengthEvaluator->evaluate(hole, sharedCards, bettingContext->getNumberOfPlayers());
    int opponentsModeledCount = 0;
    int oppponentsWithBetterEstimatedHandStrength = 0;

    for (pokerGame::OpponentModel opponent: opponents) {
        if (opponent.getNumberOfOccurrences() > 10 && opponent.getHandStrengthDeviation() <= 0.15) {
            opponentsModeledCount++;
            if (opponent.getHandStrengthAverage() > handStrength) {
                oppponentsWithBetterEstimatedHandStrength++;
            }
        }
    }

    if ((double) opponentsModeledCount / bettingContext->getNumberOfPlayers() < 0.15) {
        // If not enough context actions, fallback on secondary strategy
        return secondaryBettingStrategy->makeDecision(hole, sharedCards, minBet, bigBlind, bettingContext, opponents);
    } else {
        return decideBet(minBet, bigBlind, oppponentsWithBetterEstimatedHandStrength, opponentsModeledCount);
    }
}

}
}
