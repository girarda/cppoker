#ifndef Player_H
#define Player_H

#include <string>
#include "pokerGame/Hand.h"
#include "pokerGame/Player.h"

namespace pokerGame
{

class PokerPlayer
{
public:

    PokerPlayer(Player *playerImpl, float initialMoney);
    virtual ~PokerPlayer();

    virtual Decision makeDecision(float minBet);

    virtual void setMoney(float newValue);

    virtual void startPlaying();
    virtual void fold();
    virtual void setupForNewTableTurn();
    virtual void stopPlaying();

    virtual bool hasBetterHand(const PokerPlayer& other) const;
    virtual float getPot() const;

    virtual bool isPlaying() const;
    virtual bool isFolded() const;

    virtual void showCards();

    virtual void addCard(const Card& card);
    virtual void addToPot(float moneyToAdd);
    virtual void winMoney(float gainedMoney);

    virtual void seeGamePhase(const std::string& phaseName);
    virtual void seePlayerTurn(const PokerPlayer& player);
    virtual void seeDealer(const PokerPlayer& dealer);
    virtual void seeBigBlind(const PokerPlayer& player, float bigBlind);
    virtual void seeSmallBlind(const PokerPlayer& player, float smallBlind);
    virtual void seeRoundWinner(const PokerPlayer& winner, float moneyWon);
    virtual void seeWinner(const PokerPlayer& winner);
    virtual void seeOpponentCards(const PokerPlayer& opponent);
    virtual void seeOpponentMoney(const PokerPlayer& opponnent);
    virtual void seeCards();
    virtual void seeMoney();


    virtual std::string getName() const;

    virtual void deliver(const std::string& msg);

    // for testing purposes
    PokerPlayer(Player *playerImpl, float initialMoney ,Hand* hand);
    float getMoney() const;

private:
    enum State {
        PLAYING,
        FOLDED,
        NOT_PLAYING
    };

    void clearPot();
    Hand getVisibleHand() const;

    Hand hand;

    Player *playerImpl;

    State currentState;

    float money;
    float pot;
};

}

#endif
