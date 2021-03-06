#ifndef Player_H
#define Player_H

#include <string>
#include <vector>
#include "pokerGame/modeling/OpponentModel.h"
#include "pokerGame/card/Hand.h"
#include "pokerGame/PlayerController.h"
#include "pokerGame/modeling/BettingContext.h"

namespace pokerGame {

class Player {
public:

    Player(PlayerController *aPlayerController, float initialMoney);
    virtual ~Player();

    virtual Decision makeDecision(const std::vector<card::Card> &sharedCards, const modeling::BettingContext &bettingContext, const std::vector<modeling::OpponentModel> &opponents);

    virtual void setMoney(float newValue);

    virtual void startPlaying();
    virtual void stopPlaying();
    virtual void fold();
    virtual void setupForNewRound();

    virtual bool hasBetterHand(const Player& other, const std::vector<card::Card> &sharedCards) const;
    virtual float getPot() const;
    virtual std::vector<card::Card> getVisibleHoleCards() const;

    virtual bool isPlaying() const;
    virtual bool isFolded() const;
    virtual bool lost() const;

    virtual bool isAllIn() const;

    virtual void showCards();

    virtual void addCardToHole(card::Card card);
    virtual void addToPot(float moneyToAdd);
    virtual void winMoney(float gainedMoney);

    virtual void seeGamePhase(std::string phaseName);
    virtual void seePlayerTurn(const Player& player);
    virtual void seeDealer(const Player& dealer);
    virtual void seeBigBlind(const Player& player, float bigBlind);
    virtual void seeSmallBlind(const Player& player, float smallBlind);
    virtual void seeRoundWinner(const Player& winner, float moneyWon);
    virtual void seeWinner(const Player& winner);
    virtual void seeOpponentHoleCards(const Player& opponent);
    virtual void seeOpponentMoney(const Player& opponnent);
    virtual void seeHoleCards();
    virtual void seeMoney();


    virtual std::string getName() const;

    virtual void deliver(std::string msg);

    virtual float getMoney() const;

private:
    enum State {
        PLAYING,
        FOLDED,
        NOT_PLAYING
    };

    void clearPot();

    void discardCards();

    std::vector<card::Card> holeCards;

    PlayerController *playerController;

    State currentState;

    float money;
    float pot;
};

}

#endif
