#include "playerController/bot/BettingStrategy.h"

namespace playerController {
namespace bot {

BettingStrategy::BettingStrategy() {

}

BettingStrategy::~BettingStrategy() {

}

pokerGame::Decision BettingStrategy::makeDecision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents) {
    if(sharedCards.empty()) {
        return makePreFlopDecision(holeCards, bettingContext, opponents);
    } else {
        return makePostFlopDecision(holeCards, sharedCards, bettingContext, opponents);
    }
}

}
}
