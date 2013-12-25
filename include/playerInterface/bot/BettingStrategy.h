#ifndef BETTINGSTRATEGY_H
#define BETTINGSTRATEGY_H

#include "pokerGame/card/Hand.h"
#include "pokerGame/Decision.h"
#include "pokerGame/context/BettingContext.h"
#include "pokerGame/OpponentModel.h"

namespace playerInterface {
namespace bot {

class BettingStrategy {
public:
    BettingStrategy();
    virtual ~BettingStrategy();
    virtual pokerGame::Decision makeDecision(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, float minBet, float bigBlind, pokerGame::context::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents);

protected:
    virtual pokerGame::Decision makePreFlopDecision(std::vector<pokerGame::card::Card> hole, float minBet, float bigBlind, pokerGame::context::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents) = 0;
    virtual pokerGame::Decision makePostFlopDecision(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, float minBet, float bigBlind, pokerGame::context::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents) = 0;

private:
    bool isPreFlopHand(const pokerGame::card::Hand& hand) const;
};

}
}
#endif
