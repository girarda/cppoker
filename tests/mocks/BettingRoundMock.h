#ifndef IPLAYERMOCK_H_
#define IPLAYERMOCK_H_

#include "pokerGame/BettingRound.h"
#include "gmock/gmock.h"

namespace test
{
    class BettingRoundMock : public pokerGame::BettingRound
    {
        public:
        MOCK_METHOD2(start, void(pokerGame::GameContext* gameContext, std::vector<pokerGame::Card> sharedCards));
        MOCK_CONST_METHOD0(getMinBet, float());
    };
}

#endif
