#ifndef HOLECARDSEQUIVALENCEMOCK_H
#define HOLECARDSEQUIVALENCEMOCK_H

#include "pokerGame/HoleCardsEquivalence.h"
#include "gmock/gmock.h"

namespace test {

class HoleCardsEquivalenceMock : public pokerGame::HoleCardsEquivalence {
public:
    HoleCardsEquivalenceMock() :pokerGame::HoleCardsEquivalence(2,3) {}
    MOCK_CONST_METHOD0(getNumber1, int());
    MOCK_CONST_METHOD0(getNumber2, int());
    MOCK_CONST_METHOD0(equivalenceToCards, std::vector<pokerGame::Card>());
};

}

#endif
