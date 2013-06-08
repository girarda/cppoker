#ifndef PLAYERMOCK_H_
#define PLAYERMOCK_H_

#include "core/Player.h"
#include "gmock/gmock.h"

namespace test
{
    class PlayerMock : public pcore::Player
    {
        public:
        PlayerMock(): Player(NULL){};

        MOCK_METHOD0(makeDecision, pcore::Decision());

        MOCK_METHOD1(setMoney, void(pcore::Money newValue));
        MOCK_METHOD1(setName, void(std::string name));

        MOCK_METHOD0(start, void());
        MOCK_METHOD0(fold, void());
        MOCK_METHOD0(setupForNewTableTurn, void());

        MOCK_CONST_METHOD0(isPlaying, bool());
        MOCK_CONST_METHOD0(isFolded, bool());
        MOCK_CONST_METHOD1(hasBetterHand, bool(const Player& other));

        MOCK_METHOD1(addCard, void(const pcore::Card& card));
        MOCK_METHOD1(addToPot, void(pcore::Money bet));
        MOCK_METHOD1(winMoney, void(pcore::Money gainedMoney));

        MOCK_CONST_METHOD1(seeDealer, void(const Player& dealer));
        MOCK_CONST_METHOD2(seeBigBlind, void(const Player& player, pcore::Money bigBlind));
        MOCK_CONST_METHOD2(seeSmallBlind, void(const Player& player, pcore::Money smallBlind));
        MOCK_CONST_METHOD1(seeWinner, void(const Player& winner));
        MOCK_CONST_METHOD1(seeOpponentCards, void(const Player& opponent));
        MOCK_CONST_METHOD1(seeOpponentMoney, void(const Player& opponent));
        MOCK_CONST_METHOD0(seeCards, void());
        MOCK_CONST_METHOD0(seeMoney, void());
    };
}

#endif
