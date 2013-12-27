#ifndef BETTINGSTRATEGY_H
#define BETTINGSTRATEGY_H

#include "pokerGame/card/Hand.h"
#include "pokerGame/Decision.h"
#include "pokerGame/modeling/BettingContext.h"
#include "pokerGame/modeling/OpponentModel.h"

namespace playerController {
namespace bot {

class BettingStrategy {
public:
    BettingStrategy();
    virtual ~BettingStrategy();
    virtual pokerGame::Decision makeDecision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents);

protected:
    virtual pokerGame::Decision makePreFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents) = 0;
    virtual pokerGame::Decision makePostFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents) = 0;

private:
    bool isPreFlopHand(const pokerGame::card::Hand& hand) const;
};

}
}
#endif
