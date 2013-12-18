#include "pokerGame/PlayerController.h"
#include <string>

namespace playerInterface
{

class ConsolePlayer : public pokerGame::PlayerController
{
public:
    ConsolePlayer();

    virtual pokerGame::Decision makeDecision(const pokerGame::Hand& hand, float minBet, float bigBlind);

    virtual void deliver(const std::string &msg);

    virtual void seeDealer(std::string dealer);
    virtual void seeBigBlind(std::string player, float bigBlind);
    virtual void seeSmallBlind(std::string player, float smallBlind);
    virtual void seeWinner(std::string winner);
    virtual void seeOpponentCards(std::string opponent, const pokerGame::Hand& hand);
    virtual void seeOpponentMoney(std::string opponent, float money);
    virtual void seeCards(const pokerGame::Hand& hand);
    virtual void seeMoney(float money);
};

}
