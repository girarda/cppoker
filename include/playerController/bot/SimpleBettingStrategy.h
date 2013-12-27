#ifndef SIMPLEBETTINGSTRATEGY_H
#define SIMPLEBETTINGSTRATEGY_H
#include "BettingStrategy.h"

namespace playerController {
namespace bot {

class SimpleBettingStrategy: public BettingStrategy {
public:
    SimpleBettingStrategy();
    virtual ~SimpleBettingStrategy();

protected:
    virtual pokerGame::Decision makePreFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents);
    virtual pokerGame::Decision makePostFlopDecision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents);
};

}
}
#endif
