#ifndef IPLAYERMOCK_H_
#define IPLAYERMOCK_H_

#include "pokerGame/BettingRound.h"
#include "gmock/gmock.h"

namespace test
{
    class GameRoundMock : public pokerGame::GameRound
    {
        public:
        GameRoundMock(): GameRound(NULL, NULL){};
        MOCK_METHOD1(playRound, void(pokerGame::GameContext* gameContext));
    };
}

#endif
