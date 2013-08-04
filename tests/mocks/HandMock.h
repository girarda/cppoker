#ifndef HANDMOCK_H_
#define HANDMOCK_H_

#include "pokerGame/Hand.h"
#include "gmock/gmock.h"

namespace test
{
    class HandMock : public pokerGame::Hand
    {
        public:
            MOCK_METHOD1(addCard, void(const pokerGame::Card &aCard));
    };
}

#endif
