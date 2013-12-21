#ifndef IPLAYERMOCK_H_
#define IPLAYERMOCK_H_

#include "pokerGame/BettingRound.h"
#include "gmock/gmock.h"

namespace test
{
    class BettingRoundMock : public pokerGame::BettingRound
    {
        public:
        MOCK_METHOD6(start, void(std::vector<pokerGame::PokerPlayer*> roundPlayers, float blind, int dealerPlayerIndex, int bigBlindPlayerIndex, int smallBlindPlayerIndex, std::vector<pokerGame::Card> sharedCards));
        MOCK_CONST_METHOD0(getMinBet, float());
    };
}

#endif
