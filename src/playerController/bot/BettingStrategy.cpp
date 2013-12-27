#include "playerController/bot/BettingStrategy.h"

namespace playerController {
namespace bot {

BettingStrategy::BettingStrategy() {

}

BettingStrategy::~BettingStrategy() {

}

pokerGame::Decision BettingStrategy::makeDecision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, float minBet, float bigBlind, pokerGame::modeling::BettingContext* bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents) {
    if(sharedCards.empty()) {
        return makePreFlopDecision(holeCards, minBet, bigBlind, bettingContext, opponents);
    } else {
        return makePostFlopDecision(holeCards, sharedCards, minBet, bigBlind, bettingContext, opponents);
    }
}

}
}
