#ifndef IPLAYERMOCK_H_
#define IPLAYERMOCK_H_

#include "core/IPlayer.h"
#include "gmock/gmock.h"

namespace test
{
    class IPlayerMock : public pcore::IPlayer
    {
        public:
        MOCK_METHOD1(makeDecision, pcore::Decision(const pcore::Money& minBet));

        MOCK_CONST_METHOD1(seeDealer, void(const std::string dealer));
        MOCK_CONST_METHOD2(seeBigBlind, void(const std::string player, pcore::Money bigBlind));
        MOCK_CONST_METHOD2(seeSmallBlind, void(std::string player, pcore::Money smallBlind));
        MOCK_CONST_METHOD1(seeWinner, void(const std::string winner));
        MOCK_CONST_METHOD2(seeOpponentCards, void(std::string opponent, const pcore:: Hand&));
        MOCK_CONST_METHOD2(seeOpponentMoney, void(std::string opponent, pcore::Money));
        MOCK_CONST_METHOD1(seeCards, void(const pcore::Hand& hand));
        MOCK_CONST_METHOD1(seeMoney, void(const pcore::Money& money));
    };
}

#endif
