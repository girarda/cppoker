#ifndef IPlayer_H
#define IPlayer_H

#include <vector>
#include "pokerGame/modeling/OpponentModel.h"
#include "pokerGame/card/Hand.h"
#include "pokerGame/Decision.h"
#include "pokerGame/modeling/BettingContext.h"

namespace pokerGame {

class PlayerController {
public:
    PlayerController();
    virtual ~PlayerController();

    virtual Decision makeDecision(const std::vector<card::Card> &hole, const std::vector<card::Card> &sharedCards, const modeling::BettingContext &bettingContext, const std::vector<modeling::OpponentModel> &opponents) = 0;

    virtual void deliver(std::string msg) = 0;

    virtual void seeGamePhase(std::string phaseName) = 0;

    virtual void seeDealer(std::string dealer) = 0;
    virtual void seeBigBlind(std::string player, float bigBlind) = 0;
    virtual void seeSmallBlind(std::string player, float smallBlind ) = 0;
    virtual void seeRoundWinner(std::string winner, float moneyWon) = 0;
    virtual void seeWinner(std::string winner) = 0;
    virtual void seeOpponentHole(std::string opponent, const card::Hand& hand) = 0;
    virtual void seeOpponentMoney(std::string opponent, float money) = 0;
    virtual void seeHoleCards(const std::vector<card::Card> &holeCards) = 0;
    virtual void seeMoney(float money) = 0;

    virtual void seePlayerTurn(std::string player) = 0;

    virtual std::string getName() const;
    virtual void setName(std::string newName);

protected:
    std::string name;
};

}
#endif
