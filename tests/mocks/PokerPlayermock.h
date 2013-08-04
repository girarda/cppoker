#ifndef PLAYERMOCK_H_
#define PLAYERMOCK_H_

#include "pokerGame/PokerPlayer.h"
#include "gmock/gmock.h"

namespace test
{
    class PlayerMock : public pokerGame::PokerPlayer
    {
        public:
        PlayerMock(): PokerPlayer(NULL, 0){};

        MOCK_METHOD0(makeDecision, pokerGame::Decision());

        MOCK_METHOD1(setMoney, void(float newValue));
        MOCK_METHOD1(setName, void(std::string name));

        MOCK_METHOD0(startPlaying, void());
        MOCK_METHOD0(fold, void());
        MOCK_METHOD0(setupForNewTableTurn, void());

        MOCK_CONST_METHOD0(isPlaying, bool());
        MOCK_CONST_METHOD0(isFolded, bool());
        MOCK_CONST_METHOD1(hasBetterHand, bool(const PokerPlayer& other));

        MOCK_METHOD1(addCard, void(const pokerGame::Card& card));
        MOCK_METHOD1(addToPot, void(float bet));
        MOCK_METHOD1(winMoney, void(float gainedMoney));

        MOCK_METHOD1(seeGamePhase, void(const std::string& phaseName));
        MOCK_METHOD1(seePlayerTurn, void(const PokerPlayer& player));
        MOCK_METHOD1(seeDealer, void(const PokerPlayer& dealer));
        MOCK_METHOD2(seeBigBlind, void(const PokerPlayer& player, float bigBlind));
        MOCK_METHOD2(seeSmallBlind, void(const PokerPlayer& player, float smallBlind));
        MOCK_METHOD2(seeRoundWinner, void(const PokerPlayer& winner, float moneyWon));
        MOCK_METHOD1(seeWinner, void(const PokerPlayer& winner));
        MOCK_METHOD1(seeOpponentCards, void(const PokerPlayer& opponent));
        MOCK_METHOD1(seeOpponentMoney, void(const PokerPlayer& opponent));
        MOCK_METHOD0(seeCards, void());
        MOCK_METHOD0(seeMoney, void());
    };
}

#endif
