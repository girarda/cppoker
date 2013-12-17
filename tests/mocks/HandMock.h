#ifndef HANDMOCK_H_
#define HANDMOCK_H_

#include "pokerGame/Hand.h"
#include "gmock/gmock.h"

namespace test
{
    class HandMock : public pokerGame::Hand
    {
        public:
            MOCK_CONST_METHOD1(addCard, void(const pokerGame::Card &aCard));
            MOCK_CONST_METHOD0(getSize, int());
            MOCK_CONST_METHOD0(getSumOfPower, int());
            MOCK_CONST_METHOD0(hasPair, bool());
            MOCK_CONST_METHOD0(getVisibleHand, pokerGame::Hand());
            MOCK_CONST_METHOD0(getHandValue, pokerGame::HandValue());
    };
}

#endif
