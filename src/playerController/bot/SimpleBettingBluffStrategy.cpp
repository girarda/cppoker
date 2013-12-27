#include "playerController/bot/SimpleBettingBluffStrategy.h"

namespace playerController {
namespace bot {

SimpleBettingBluffStrategy::SimpleBettingBluffStrategy() {

}

SimpleBettingBluffStrategy::~SimpleBettingBluffStrategy() {

}

pokerGame::Decision SimpleBettingBluffStrategy::makePreFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, pokerGame::modeling::BettingContext* bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents) {
    pokerGame::card::Hand hand(holeCards);
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::card::HandType::PAIR || hand.getSumOfPower() < 9) {
        decision.choice = pokerGame::RAISE;
        decision.bet = bettingContext->getMinBet() + bettingContext->getBigBlind();
    } else if(hand.getSumOfPower() > 16)
    {
        decision.choice = pokerGame::CALL;
        decision.bet = bettingContext->getMinBet();
    } else
    {
        decision.choice = pokerGame::FOLD;
        decision.bet = 0;
    }
    return decision;
}

pokerGame::Decision SimpleBettingBluffStrategy::makePostFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, pokerGame::modeling::BettingContext* bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents) {
    pokerGame::card::Hand hand(holeCards, sharedCards);
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::card::HandType::HIGH_CARD || hand.getHandValue().type >= pokerGame::card::THREE_OF_A_KIND) {
        decision.choice = pokerGame::RAISE;
        decision.bet = bettingContext->getMinBet() + bettingContext->getBigBlind();
    } else if(bettingContext->getMinBet() == 0) {
        decision.choice = pokerGame::CALL;
        decision.bet = bettingContext->getMinBet();
    } else {
        decision.choice = pokerGame::FOLD;
        decision.bet = 0;
    }
    return decision;
}

}
}
