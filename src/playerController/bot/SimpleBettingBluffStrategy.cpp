#include "playerController/bot/SimpleBettingBluffStrategy.h"

namespace playerController {
namespace bot {

SimpleBettingBluffStrategy::SimpleBettingBluffStrategy() {

}

SimpleBettingBluffStrategy::~SimpleBettingBluffStrategy() {

}

pokerGame::Decision SimpleBettingBluffStrategy::makePreFlopDecision(std::vector<pokerGame::card::Card> hole, float minBet, float bigBlind, pokerGame::modeling::BettingContext* bettingContext, std::vector<pokerGame::modeling::OpponentModel> opponents) {
    pokerGame::card::Hand hand(hole);
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::card::HandType::PAIR || hand.getSumOfPower() < 9) {
        decision.choice = pokerGame::RAISE;
        decision.bet = minBet + bigBlind;
    } else if(hand.getSumOfPower() > 16)
    {
        decision.choice = pokerGame::CALL;
        decision.bet = minBet;
    } else
    {
        decision.choice = pokerGame::FOLD;
        decision.bet = 0;
    }
    return decision;
}

pokerGame::Decision SimpleBettingBluffStrategy::makePostFlopDecision(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, float minBet, float bigBlind, pokerGame::modeling::BettingContext* bettingContext, std::vector<pokerGame::modeling::OpponentModel> opponents) {
    pokerGame::card::Hand hand(hole, sharedCards);
    pokerGame::Decision decision;
    if(hand.getHandValue().type == pokerGame::card::HandType::HIGH_CARD || hand.getHandValue().type >= pokerGame::card::THREE_OF_A_KIND) {
        decision.choice = pokerGame::RAISE;
        decision.bet = minBet + bigBlind;
    } else if(minBet == 0) {
        decision.choice = pokerGame::CALL;
        decision.bet = minBet;
    } else {
        decision.choice = pokerGame::FOLD;
        decision.bet = 0;
    }
    return decision;
}

}
}
