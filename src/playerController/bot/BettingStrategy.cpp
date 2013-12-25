#include "playerController/bot/BettingStrategy.h"

namespace playerController {
namespace bot {

BettingStrategy::BettingStrategy() {

}

BettingStrategy::~BettingStrategy() {

}

pokerGame::Decision BettingStrategy::makeDecision(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, float minBet, float bigBlind, pokerGame::modeling::BettingContext* bettingContext, std::vector<pokerGame::modeling::OpponentModel> opponents) {
    if(sharedCards.empty()) {
        return makePreFlopDecision(hole, minBet, bigBlind, bettingContext, opponents);
    } else {
        return makePostFlopDecision(hole, sharedCards, minBet, bigBlind, bettingContext, opponents);
    }
}

}
}
