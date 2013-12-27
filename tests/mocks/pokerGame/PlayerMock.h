#ifndef PLAYERMOCK_H_
#define PLAYERMOCK_H_

#include "pokerGame/Player.h"
#include "gmock/gmock.h"

namespace test {

class PlayerMock : public pokerGame::Player {
public:
    PlayerMock(): Player(NULL, 0){};

    MOCK_METHOD3(makeDecision, pokerGame::Decision(const std::vector<pokerGame::card::Card> &sharedCards, const pokerGame::modeling::BettingContext &bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents));

    MOCK_METHOD1(setMoney, void(float newValue));

    MOCK_METHOD0(startPlaying, void());
    MOCK_METHOD0(stopPlaying, void());
    MOCK_METHOD0(fold, void());
    MOCK_METHOD0(setupForNewRound, void());

    MOCK_CONST_METHOD2(hasBetterHand, bool(const pokerGame::Player& other, const std::vector<pokerGame::card::Card> &sharedCards));
    MOCK_CONST_METHOD0(getPot, float());
    MOCK_CONST_METHOD0(getVisibleHoleCards, std::vector<pokerGame::card::Card>());


    MOCK_CONST_METHOD0(isPlaying, bool());
    MOCK_CONST_METHOD0(isFolded, bool());
    MOCK_CONST_METHOD0(lost, bool());

    MOCK_CONST_METHOD0(isAllIn, bool());

    MOCK_METHOD0(showCards, void());

    MOCK_METHOD1(addCardToHole, void(pokerGame::card::Card card));
    MOCK_METHOD1(addToPot, void(float bet));
    MOCK_METHOD1(winMoney, void(float gainedMoney));

    MOCK_METHOD1(seeGamePhase, void(std::string phaseName));
    MOCK_METHOD1(seePlayerTurn, void(const pokerGame::Player& player));
    MOCK_METHOD1(seeDealer, void(const pokerGame::Player& dealer));
    MOCK_METHOD2(seeBigBlind, void(const pokerGame::Player& player, float bigBlind));
    MOCK_METHOD2(seeSmallBlind, void(const pokerGame::Player& player, float smallBlind));
    MOCK_METHOD2(seeRoundWinner, void(const pokerGame::Player& winner, float moneyWon));
    MOCK_METHOD1(seeWinner, void(const pokerGame::Player& winner));
    MOCK_METHOD1(seeOpponentHoleCards, void(const pokerGame::Player& opponent));
    MOCK_METHOD1(seeOpponentMoney, void(const pokerGame::Player& opponent));
    MOCK_METHOD0(seeHoleCards, void());
    MOCK_METHOD0(seeMoney, void());

    MOCK_CONST_METHOD0(getMoney, float());
};

}

#endif
