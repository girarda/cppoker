#include "pokerGame/IPlayer.h"
#include <string>

namespace playerInterface
{

class ConsolePlayer : public pokerGame::IPlayer
{
public:
    ConsolePlayer();

    virtual pokerGame::Decision makeDecision(float minBet);

    virtual void seeDealer(std::string dealer) const;
    virtual void seeBigBlind(std::string player, float bigBlind) const;
    virtual void seeSmallBlind(std::string player, float smallBlind) const;
    virtual void seeWinner(std::string winner) const;
    virtual void seeOpponentCards(std::string opponent, const pokerGame::Hand& hand) const;
    virtual void seeOpponentMoney(std::string opponent, float money) const;
    virtual void seeCards(const pokerGame::Hand& hand) const;
    virtual void seeMoney(float money) const;
};

}
