#include "pokerGame/PlayerController.h"
#include <string>

namespace playerController {

class ConsolePlayer : public pokerGame::PlayerController {
public:
    ConsolePlayer();

    virtual pokerGame::Decision makeDecision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, pokerGame::modeling::BettingContext* bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents);

    virtual void deliver(std::string msg);

    virtual void seeDealer(std::string dealer);
    virtual void seeBigBlind(std::string player, float bigBlind);
    virtual void seeSmallBlind(std::string player, float smallBlind);
    virtual void seeWinner(std::string winner);
    virtual void seeOpponentHole(std::string opponent, const pokerGame::card::Hand& hand);
    virtual void seeOpponentMoney(std::string opponent, float money);
    virtual void seeHoleCards(const std::vector<pokerGame::card::Card> &hole);
    virtual void seeMoney(float money);
};

}
