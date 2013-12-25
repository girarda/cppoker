#ifndef SIMPLEBETTINGSTRATEGY_H
#define SIMPLEBETTINGSTRATEGY_H
#include "BettingStrategy.h"

namespace playerInterface {
namespace bot {

class SimpleBettingStrategy: public BettingStrategy {
public:
    SimpleBettingStrategy();
    virtual ~SimpleBettingStrategy();

protected:
    virtual pokerGame::Decision makePreFlopDecision(std::vector<pokerGame::card::Card> hole, float minBet, float bigBlind, pokerGame::context::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents);
    virtual pokerGame::Decision makePostFlopDecision(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, float minBet, float bigBlind, pokerGame::context::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents);
};

}
}
#endif
