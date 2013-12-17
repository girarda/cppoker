#include "pokerGame/PlayerController.h"
#include <string>
#include "pokerGame/Hand.h"

namespace playerInterface
{

class SimpleBotPlayerController : public pokerGame::PlayerController
{
public:
    SimpleBotPlayerController();

    virtual pokerGame::Decision makeDecision(const pokerGame::Hand& hand, float minBet);

    virtual void deliver(const std::string &msg);

    virtual void seeDealer(std::string dealer);
    virtual void seeBigBlind(std::string player, float bigBlind);
    virtual void seeSmallBlind(std::string player, float smallBlind);
    virtual void seeRoundWinner(std::string winner, float moneyWon);
    virtual void seeWinner(std::string winner);
    virtual void seeOpponentCards(std::string opponent, const pokerGame::Hand& hand);
    virtual void seeOpponentMoney(std::string opponent, float money);
    virtual void seeCards(const pokerGame::Hand& hand);
    virtual void seeMoney(float money);

    virtual void seePlayerTurn(std::string player);
    virtual void seeGamePhase(std::string phaseName);

private:
    pokerGame::Decision makePreFlopDecision(const pokerGame::Hand& hand, float minBet);
    pokerGame::Decision makePostFlopDecision(const pokerGame::Hand& hand, float minBet);

    bool isPreFlopHand(const pokerGame::Hand& hand) const;
};

}
