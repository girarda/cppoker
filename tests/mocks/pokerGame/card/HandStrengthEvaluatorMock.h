#ifndef HANDSTRENGTHEVALUATORMOCK_H_
#define HANDSTRENGTHEVALUATORMOCK_H_

#include "pokerGame/card/HandStrengthEvaluator.h"
#include "gmock/gmock.h"

namespace test {

class HandStrengthEvaluatorMock : public pokerGame::card::HandStrengthEvaluator {
public:
    MOCK_METHOD3(evaluate, double(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, int numberOfPlayers));
};

}

#endif
