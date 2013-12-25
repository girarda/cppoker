#ifndef HOLECARDSEQUIVALENCEMOCK_H
#define HOLECARDSEQUIVALENCEMOCK_H

#include "pokerGame/simulation/HoleCardsEquivalence.h"
#include "gmock/gmock.h"

namespace test {

class HoleCardsEquivalenceMock : public pokerGame::simulation::HoleCardsEquivalence {
public:
    HoleCardsEquivalenceMock() :pokerGame::simulation::HoleCardsEquivalence(2,3) {}
    MOCK_CONST_METHOD0(getNumber1, int());
    MOCK_CONST_METHOD0(getNumber2, int());
    MOCK_CONST_METHOD0(equivalenceToCards, std::vector<pokerGame::card::Card>());
};

}

#endif
