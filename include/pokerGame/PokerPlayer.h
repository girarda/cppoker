#ifndef Player_H
#define Player_H

#include <string>
#include "pokerGame/Hand.h"
#include "pokerGame/PlayerController.h"

namespace pokerGame
{

class PokerPlayer
{
public:

    PokerPlayer(PlayerController *aPlayerController, float initialMoney);
    virtual ~PokerPlayer();

    virtual Decision makeDecision(float minBet, float bigBlind, std::vector<Card> sharedCards, int numberOfRaises);

    virtual void setMoney(float newValue);

    virtual void startPlaying();
    virtual void stopPlaying();
    virtual void fold();
    virtual void setupForNewRound();

    virtual bool hasBetterHand(const PokerPlayer& other, std::vector<Card> sharedCards) const;
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
    virtual void seePlayerTurn(const PokerPlayer& player);
    virtual void seeDealer(const PokerPlayer& dealer);
    virtual void seeBigBlind(const PokerPlayer& player, float bigBlind);
    virtual void seeSmallBlind(const PokerPlayer& player, float smallBlind);
    virtual void seeRoundWinner(const PokerPlayer& winner, float moneyWon);
    virtual void seeWinner(const PokerPlayer& winner);
    virtual void seeOpponentHole(const PokerPlayer& opponent);
    virtual void seeOpponentMoney(const PokerPlayer& opponnent);
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
