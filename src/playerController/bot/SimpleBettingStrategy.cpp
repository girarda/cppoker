#include "playerController/bot/SimpleBettingStrategy.h"

namespace playerController {
namespace bot {

SimpleBettingStrategy::SimpleBettingStrategy() {
}

SimpleBettingStrategy::~SimpleBettingStrategy() {
}

pokerGame::Decision SimpleBettingStrategy::makePreFlopDecision(std::vector<pokerGame::card::Card> hole, float minBet, float bigBlind, pokerGame::modeling::BettingContext* bettingContext, std::vector<pokerGame::modeling::OpponentModel> opponents) {
    pokerGame::card::Hand hand(hole);
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::card::HandType::PAIR) {
        decision.choice = pokerGame::RAISE;
        decision.bet = minBet + bigBlind;
    } else if(hand.getSumOfPower() > 16) {
        decision.choice = pokerGame::CALL;
        decision.bet = minBet;
    } else {
        decision.choice = pokerGame::FOLD;
        decision.bet = 0;
    }
    return decision;
}

pokerGame::Decision SimpleBettingStrategy::makePostFlopDecision(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, float minBet, float bigBlind, pokerGame::modeling::BettingContext* bettingContext, std::vector<pokerGame::modeling::OpponentModel> opponents) {
    pokerGame::card::Hand hand(hole, sharedCards);
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::card::HandType::HIGH_CARD) {
        if(minBet == 0) {
            decision.choice = pokerGame::CALL;
            decision.bet = minBet;
        } else {
            decision.choice = pokerGame::FOLD;
            decision.bet = 0;
        }
    } else if(hand.getHandValue().type >= pokerGame::card::STRAIGHT) {
        decision.choice = pokerGame::RAISE;
        decision.bet = minBet + bigBlind;
    } else {
        decision.choice = pokerGame::CALL;
        decision.bet = minBet;
    }
    return decision;
}

}
}