#ifndef HANDSTRENGTHEVALUATORMOCK_H_
#define HANDSTRENGTHEVALUATORMOCK_H_

#include "pokerGame/HandStrengthEvaluator.h"
#include "gmock/gmock.h"

namespace test
{
    class HandStrengthEvaluatorMock : public pokerGame::HandStrengthEvaluator
    {
        public:
            MOCK_METHOD3(evaluate, double(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, int numberOfPlayers));
    };
}

#endif
