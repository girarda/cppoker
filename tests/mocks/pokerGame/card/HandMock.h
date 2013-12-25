#ifndef HANDMOCK_H_
#define HANDMOCK_H_

#include "pokerGame/card/Hand.h"
#include "gmock/gmock.h"

namespace test {

class HandMock : public pokerGame::card::Hand {
public:
    MOCK_CONST_METHOD1(addCard, void(const pokerGame::card::Card &aCard));
    MOCK_CONST_METHOD0(getSize, int());
    MOCK_CONST_METHOD0(getSumOfPower, int());
    MOCK_CONST_METHOD0(hasPair, bool());
    MOCK_CONST_METHOD0(getHandValue, pokerGame::card::HandValue());
};

}

#endif
