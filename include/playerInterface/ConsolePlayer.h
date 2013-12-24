#include "pokerGame/PlayerController.h"
#include <string>

namespace playerInterface {

class ConsolePlayer : public pokerGame::PlayerController {
public:
    ConsolePlayer();

    virtual pokerGame::Decision makeDecision(std::vector<pokerGame::Card> hole, std::vector<pokerGame::Card> sharedCards, float minBet, float bigBlind, pokerGame::context::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents);

    virtual void deliver(const std::string &msg);

    virtual void seeDealer(std::string dealer);
    virtual void seeBigBlind(std::string player, float bigBlind);
    virtual void seeSmallBlind(std::string player, float smallBlind);
    virtual void seeWinner(std::string winner);
    virtual void seeOpponentHole(std::string opponent, const pokerGame::Hand& hand);
    virtual void seeOpponentMoney(std::string opponent, float money);
    virtual void seeHole(std::vector<pokerGame::Card> hole);
    virtual void seeMoney(float money);
};

}
