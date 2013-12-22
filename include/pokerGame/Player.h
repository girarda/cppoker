#ifndef Player_H
#define Player_H

#include <string>
#include "pokerGame/Hand.h"
#include "pokerGame/PlayerController.h"

namespace pokerGame
{

class Player
{
public:

    Player(PlayerController *aPlayerController, float initialMoney);
    virtual ~Player();

    virtual Decision makeDecision(float minBet, float bigBlind, std::vector<Card> sharedCards, int numberOfRaises, int numberOfPlayers);

    virtual void setMoney(float newValue);

    virtual void startPlaying();
    virtual void stopPlaying();
    virtual void fold();
    virtual void setupForNewRound();

    virtual bool hasBetterHand(const Player& other, std::vector<Card> sharedCards) const;
    virtual float getPot() const;
    virtual std::vector<Card> getVisibleHole() const;

    virtual bool isPlaying() const;
    virtual bool isFolded() const;
    virtual bool lost() const;

    virtual void showCards();

    virtual void addCardToHole(const Card& card);
    virtual void addToPot(float moneyToAdd);
    virtual void winMoney(float gainedMoney);

    virtual void seeGamePhase(std::string phaseName);
    virtual void seePlayerTurn(const Player& player);
    virtual void seeDealer(const Player& dealer);
    virtual void seeBigBlind(const Player& player, float bigBlind);
    virtual void seeSmallBlind(const Player& player, float smallBlind);
    virtual void seeRoundWinner(const Player& winner, float moneyWon);
    virtual void seeWinner(const Player& winner);
    virtual void seeOpponentHole(const Player& opponent);
    virtual void seeOpponentMoney(const Player& opponnent);
    virtual void seeHole();
    virtual void seeMoney();


    virtual std::string getName() const;

    virtual void deliver(const std::string& msg);

    float getMoney() const;

private:
    enum State {
        PLAYING,
        FOLDED,
        NOT_PLAYING
    };

    void clearPot();

    void discardCards();

    std::vector<Card> hole;

    PlayerController *playerController;

    State currentState;

    float money;
    float pot;
};

}

#endif
