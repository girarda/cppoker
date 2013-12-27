#include "playerController/bot/SimpleBettingStrategy.h"

namespace playerController {
namespace bot {

SimpleBettingStrategy::SimpleBettingStrategy() {
}

SimpleBettingStrategy::~SimpleBettingStrategy() {
}

pokerGame::Decision SimpleBettingStrategy::makePreFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, pokerGame::modeling::BettingContext* bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents) {
    pokerGame::card::Hand hand(holeCards);
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::card::HandType::PAIR) {
        decision.choice = pokerGame::RAISE;
        decision.bet = bettingContext->getMinBet() + bettingContext->getBigBlind();
    } else if(hand.getSumOfPower() > 16) {
        decision.choice = pokerGame::CALL;
        decision.bet = bettingContext->getMinBet();
    } else {
        decision.choice = pokerGame::FOLD;
        decision.bet = 0;
    }
    return decision;
}

pokerGame::Decision SimpleBettingStrategy::makePostFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards,pokerGame::modeling::BettingContext* bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents) {
    pokerGame::card::Hand hand(holeCards, sharedCards);
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::card::HandType::HIGH_CARD) {
        if(bettingContext->getMinBet() == 0) {
            decision.choice = pokerGame::CALL;
            decision.bet = bettingContext->getMinBet();
        } else {
            decision.choice = pokerGame::FOLD;
            decision.bet = 0;
        }
    } else if(hand.getHandValue().type >= pokerGame::card::STRAIGHT) {
        decision.choice = pokerGame::RAISE;
        decision.bet = bettingContext->getMinBet() + bettingContext->getBigBlind();
    } else {
        decision.choice = pokerGame::CALL;
        decision.bet = bettingContext->getMinBet();
    }
    return decision;
}

}
}
