#ifndef HANDMOCK_H_
#define HANDMOCK_H_

#include "core/Hand.h"
#include "gmock/gmock.h"

namespace test
{
    class HandMock : public pcore::Hand
    {
        public:
            MOCK_METHOD1(addCard, void(const pcore::Card &aCard));
    };
}

#endif
