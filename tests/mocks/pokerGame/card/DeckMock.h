#ifndef HANDMOCK_H_
#define HANDMOCK_H_

#include "pokerGame/card/Deck.h"
#include "gmock/gmock.h"

namespace test {

class DeckMock : public pokerGame::card::Deck {
public:
    MOCK_METHOD0(burn, void());
    MOCK_CONST_METHOD0(getSumOfPower, int());
    MOCK_METHOD0(shuffle, void ());
    MOCK_METHOD0(draw, pokerGame::card::Card());
    MOCK_CONST_METHOD0(getCount, int());
};

}

#endif
