#ifndef SIMPLEBETTINGBLUFFSTRATEGY_H
#define SIMPLEBETTINGBLUFFSTRATEGY_H

#include "BettingStrategy.h"
#include "pokerGame/context/BettingContext.h"

namespace playerInterface {
namespace bot {

class SimpleBettingBluffStrategy: public BettingStrategy {
public:
    SimpleBettingBluffStrategy();
    virtual ~SimpleBettingBluffStrategy();

protected:
    virtual pokerGame::Decision makePreFlopDecision(std::vector<pokerGame::card::Card> hole, float minBet, float bigBlind, pokerGame::context::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents);
    virtual pokerGame::Decision makePostFlopDecision(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, float minBet, float bigBlind, pokerGame::context::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents);
};

}
}

#endif
