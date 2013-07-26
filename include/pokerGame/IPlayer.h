#ifndef IPlayer_H
#define IPlayer_H

#include "pokerGame/Hand.h"

namespace pokerGame
{
enum Choice {FOLD, CHECK, CALL};

typedef struct Decision
{
    Choice choice;
    float bet;
} Decision;

class IPlayer
{
public:
    virtual Decision makeDecision(float minBet) = 0;

    virtual void deliver(const std::string& msg) = 0;

    virtual void seeDealer(std::string dealer) = 0;
    virtual void seeBigBlind(std::string player, float bigBlind) = 0;
    virtual void seeSmallBlind(std::string player, float smallBlind ) = 0;
    virtual void seeWinner(std::string winner) = 0;
    virtual void seeOpponentCards(std::string opponent, const Hand& hand) = 0;
    virtual void seeOpponentMoney(std::string opponent, float money) = 0;
    virtual void seeCards(const Hand& hand) = 0;
    virtual void seeMoney(float money) = 0;
};

}
#endif
