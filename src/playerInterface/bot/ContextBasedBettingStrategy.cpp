#include "playerInterface/bot/ContextBasedBettingStrategy.h"

namespace playerInterface {
namespace bot {

ContextBasedBettingStrategy::ContextBasedBettingStrategy(pokerGame::HandStrengthEvaluator* handEvaluator,BettingStrategy* secondBettingStrategy) : secondaryBettingStrategy(secondBettingStrategy) {
}

ContextBasedBettingStrategy::~ContextBasedBettingStrategy() {
}

pokerGame::Decision ContextBasedBettingStrategy::makePreFlopDecision(std::vector<pokerGame::Card> hole, float minBet, float bigBlind, pokerGame::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents) {
    return secondaryBettingStrategy->makeDecision(hole, std::vector<pokerGame::Card>(), minBet, bigBlind, bettingContext, opponents);
}

pokerGame::Decision ContextBasedBettingStrategy::makePostFlopDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind, pokerGame::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents) {
    double p = handStrengthEvaluator->evaluate(hole, sharedCards, bettingContext->getNumberOfPlayers());
    int opponentsModeledCount = 0;
    int oppponentsWithBetterEstimatedHandStrength = 0;

    for (pokerGame::OpponentModel opponent: opponents) {
    }
    pokerGame::Decision decision;
    return decision;
}

}
}
