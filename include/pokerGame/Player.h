#ifndef Player_H
#define Player_H

#include <string>
#include "pokerGame/Hand.h"
#include "pokerGame/IPlayer.h"

namespace pokerGame
{

class Player
{
public:

    Player(IPlayer *playerImpl, float initialMoney);
    ~Player();

    virtual Decision makeDecision(float minBet);

    virtual void setMoney(float newValue);
    virtual void setName(std::string name);

    virtual void startPlaying();
    virtual void fold();
    virtual void setupForNewTableTurn();

    virtual bool hasBetterHand(const Player& other) const;
    virtual float getPot() const;

    virtual bool isPlaying() const;
    virtual bool isFolded() const;

    virtual void addCard(const Card& card);
    virtual void addToPot(float moneyToAdd);
    virtual void winMoney(float gainedMoney);

    virtual void seeDealer(const Player& dealer);
    virtual void seeBigBlind(const Player& player, float bigBlind);
    virtual void seeSmallBlind(const Player& player, float smallBlind);
    virtual void seeWinner(const Player& winner);
    virtual void seeOpponentCards(const Player& opponent);
    virtual void seeOpponentMoney(const Player& opponnent);
    virtual void seeCards();
    virtual void seeMoney();

    virtual void deliver(const std::string& msg);

    // for testing purposes
    Player(IPlayer *playerImpl, float initialMoney ,Hand* hand);
    float getMoney() const;

private:
    enum State {
        PLAYING,
        FOLDED,
        NOT_PLAYING
    };
    void clearPot();

    Hand hand;

    IPlayer *playerImpl;

    State currentState;

    std::string name;
    float money;
    float pot;
};

}

#endif
