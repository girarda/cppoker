#include "include/playerInterface/bot/BettingStrategy.h"

namespace playerInterface {
namespace bot {

BettingStrategy::BettingStrategy() {

}

BettingStrategy::~BettingStrategy() {

}

pokerGame::Decision BettingStrategy::makeDecision(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, float minBet, float bigBlind, pokerGame::context::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents) {
    if(sharedCards.empty()) {
        return makePreFlopDecision(hole, minBet, bigBlind, bettingContext, opponents);
    } else {
        return makePostFlopDecision(hole, sharedCards, minBet, bigBlind, bettingContext, opponents);
    }
}

}
}
