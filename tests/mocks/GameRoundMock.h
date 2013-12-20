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
        MOCK_METHOD5(playRound, void(std::vector<pokerGame::PokerPlayer*> roundPlayers, float blind, int dealerPlayerIndex, int bigBlindPlayerIndex, int smallBlindPlayerIndex));
    };
}

#endif
