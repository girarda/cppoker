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

        MOCK_METHOD4(makeDecision, pokerGame::Decision(float minBet, float bigBlind, std::vector<pokerGame::Card> sharedCards, int numberOfRaises));

        MOCK_METHOD1(setMoney, void(float newValue));

        MOCK_METHOD0(startPlaying, void());
        MOCK_METHOD0(stopPlaying, void());
        MOCK_METHOD0(fold, void());
        MOCK_METHOD0(setupForNewRound, void());

        MOCK_CONST_METHOD2(hasBetterHand, bool(const PokerPlayer& other, std::vector<pokerGame::Card> sharedCards));
        MOCK_CONST_METHOD0(getPot, float());
        MOCK_CONST_METHOD0(getVisibleHole, std::vector<pokerGame::Card>());


        MOCK_CONST_METHOD0(isPlaying, bool());
        MOCK_CONST_METHOD0(isFolded, bool());
        MOCK_CONST_METHOD0(lost, bool());

        MOCK_METHOD0(showCards, void());

        MOCK_METHOD1(addCardToHole, void(const pokerGame::Card& card));
        MOCK_METHOD1(addToPot, void(float bet));
        MOCK_METHOD1(winMoney, void(float gainedMoney));

        MOCK_METHOD1(seeGamePhase, void(std::string phaseName));
        MOCK_METHOD1(seePlayerTurn, void(const pokerGame::PokerPlayer& player));
        MOCK_METHOD1(seeDealer, void(const pokerGame::PokerPlayer& dealer));
        MOCK_METHOD2(seeBigBlind, void(const pokerGame::PokerPlayer& player, float bigBlind));
        MOCK_METHOD2(seeSmallBlind, void(const pokerGame::PokerPlayer& player, float smallBlind));
        MOCK_METHOD2(seeRoundWinner, void(const pokerGame::PokerPlayer& winner, float moneyWon));
        MOCK_METHOD1(seeWinner, void(const pokerGame::PokerPlayer& winner));
        MOCK_METHOD1(seeOpponentHole, void(const pokerGame::PokerPlayer& opponent));
        MOCK_METHOD1(seeOpponentMoney, void(const pokerGame::PokerPlayer& opponent));
        MOCK_METHOD0(seeHole, void());
        MOCK_METHOD0(seeMoney, void());
    };
}

#endif
