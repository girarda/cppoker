#ifndef IPLAYERMOCK_H_
#define IPLAYERMOCK_H_

#include "pokerGame/PlayerController.h"
#include "gmock/gmock.h"

namespace test {

class PlayerControllerMock : public pokerGame::PlayerController {
public:
    MOCK_METHOD6(makeDecision, pokerGame::Decision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, float minBet, float bigBlind, pokerGame::modeling::BettingContext* bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents));

    MOCK_METHOD1(deliver, void(std::string msg));

    MOCK_METHOD1(seeGamePhase, void(std::string gamePhase));
    MOCK_METHOD1(seePlayerTurn, void(std::string playerName));
    MOCK_METHOD1(seeDealer, void(std::string dealer));
    MOCK_METHOD2(seeBigBlind, void(std::string player, float bigBlind));
    MOCK_METHOD2(seeSmallBlind, void(std::string player, float smallBlind));
    MOCK_METHOD1(seeWinner, void(std::string winner));
    MOCK_METHOD2(seeRoundWinner, void(std::string winner, float moneyWon));
    MOCK_METHOD2(seeOpponentHole, void(std::string opponent, const pokerGame::card::Hand&));
    MOCK_METHOD2(seeOpponentMoney, void(std::string opponent, float));
    MOCK_METHOD1(seeHoleCards, void(const std::vector<pokerGame::card::Card> &holeCards));
    MOCK_METHOD1(seeMoney, void(const float money));

    MOCK_CONST_METHOD0(getName, std::string());
};

}

#endif
