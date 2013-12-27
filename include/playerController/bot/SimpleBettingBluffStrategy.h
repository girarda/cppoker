#ifndef SIMPLEBETTINGBLUFFSTRATEGY_H
#define SIMPLEBETTINGBLUFFSTRATEGY_H

#include "BettingStrategy.h"
#include "pokerGame/modeling/BettingContext.h"

namespace playerController {
namespace bot {

class SimpleBettingBluffStrategy: public BettingStrategy {
public:
    SimpleBettingBluffStrategy();
    virtual ~SimpleBettingBluffStrategy();

protected:
    virtual pokerGame::Decision makePreFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents);
    virtual pokerGame::Decision makePostFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents);
};

}
}

#endif
