#include "pokerGame/PlayerController.h"
#include <string>
#include "pokerGame/card/Hand.h"
#include "playerInterface/bot/BettingStrategy.h"

namespace playerInterface {

class BotPlayerController : public pokerGame::PlayerController {
public:
    BotPlayerController(bot::BettingStrategy* botBettingStrategy);
    virtual ~BotPlayerController();

    virtual pokerGame::Decision makeDecision(std::vector<pokerGame::card::Card> hole, std::vector<pokerGame::card::Card> sharedCards, float minBet, float bigBlind, pokerGame::context::BettingContext* bettingContext, std::vector<pokerGame::OpponentModel> opponents);

    virtual void deliver(const std::string &msg);

    virtual void seeDealer(std::string dealer);
    virtual void seeBigBlind(std::string player, float bigBlind);
    virtual void seeSmallBlind(std::string player, float smallBlind);
    virtual void seeRoundWinner(std::string winner, float moneyWon);
    virtual void seeWinner(std::string winner);
    virtual void seeOpponentHole(std::string opponent, const pokerGame::card::Hand& hand);
    virtual void seeOpponentMoney(std::string opponent, float money);
    virtual void seeHole(std::vector<pokerGame::card::Card> hole);
    virtual void seeMoney(float money);

    virtual void seePlayerTurn(std::string player);
    virtual void seeGamePhase(std::string phaseName);

private:
    bot::BettingStrategy* bettingStrategy;
};

}
