#ifndef BETTINGROUNDMOCK_H_
#define BETTINGROUNDMOCK_H_

#include "pokerGame/BettingRound.h"
#include "gmock/gmock.h"

namespace test {

class BettingRoundMock : public pokerGame::BettingRound {
public:
    MOCK_METHOD3(start, void(pokerGame::GameContext* gameContext, const std::vector<pokerGame::card::Card> &sharedCards, const pokerGame::BettingRoundType &bettingRoundType));
    MOCK_CONST_METHOD0(getCurrentMaximumBid, float());
};

}

#endif
