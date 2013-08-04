#ifndef IPLAYERMOCK_H_
#define IPLAYERMOCK_H_

#include "pokerGame/Player.h"
#include "gmock/gmock.h"

namespace test
{
    class IPlayerMock : public pokerGame::Player
    {
        public:
        MOCK_METHOD1(makeDecision, pokerGame::Decision(const float minBet));

        MOCK_METHOD1(deliver, void(const std::string& msg));

        MOCK_METHOD1(seeGamePhase, void(const std::string gamePhase));
        MOCK_METHOD1(seePlayerTurn, void(const std::string playerTurn));
        MOCK_METHOD1(seeDealer, void(const std::string dealer));
        MOCK_METHOD2(seeBigBlind, void(const std::string player, float bigBlind));
        MOCK_METHOD2(seeSmallBlind, void(std::string player, float smallBlind));
        MOCK_METHOD1(seeWinner, void(const std::string winner));
        MOCK_METHOD2(seeRoundWinner, void(const std::string winner, float moneyWon));
        MOCK_METHOD2(seeOpponentCards, void(std::string opponent, const pokerGame:: Hand&));
        MOCK_METHOD2(seeOpponentMoney, void(std::string opponent, float));
        MOCK_METHOD1(seeCards, void(const pokerGame::Hand& hand));
        MOCK_METHOD1(seeMoney, void(const float money));
    };
}

#endif
