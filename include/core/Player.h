/**-------------------------/// Player.h \\\---------------------------
 *
 * <b>Player</b>
 * @version : 1.0
 * @since : 2012 Dec 23
 *
 * @description :
 *     Interface of the Player class.
 * @usage :
 *
 * @author : Alexandre Girard | girarda.92@gmail.com
 * @copyright girarda
 * @TODO : ADD DOC
 *
 *--------------------------\\\ Player.h ///---------------------------*/

#ifndef Player_H
#define Player_H

#include <string>
#include "core/Hand.h"
#include "core/IPlayer.h"
#include "core/Money.h"

namespace pcore
{

class Player
{
    public:

        Player(IPlayer *playerImpl);

        virtual Decision makeDecision(const Money &minBet);

        virtual void setMoney(Money newValue);
        virtual void setName(std::string name);

        virtual void start();
        virtual void fold();
        virtual void setupForNewTableTurn();

        virtual bool hasBetterHand(const Player& other) const;
        virtual Money getPot() const;

        virtual bool isPlaying() const;
        virtual bool isFolded() const;

        virtual void addCard(const Card& card);
        virtual void addToPot(Money moneyToAdd);
        virtual void winMoney(Money gainedMoney);

        virtual void seeDealer(const Player& dealer) const;
        virtual void seeBigBlind(const Player& player, Money bigBlind) const;
        virtual void seeSmallBlind(const Player& player, Money smallBlind) const;
        virtual void seeWinner(const Player& winner) const;
        virtual void seeOpponentCards(const Player& opponent) const;
        virtual void seeOpponentMoney(const Player& opponnent) const; 
        virtual void seeCards() const;
        virtual void seeMoney() const;
        
        // for testing purposes
        Player(IPlayer *playerImpl, Hand* hand);
        Money getMoney() const;

    private:
        enum State {
            PLAYING,
            FOLDED,
            NOT_PLAYING
        };
        void clearPot();

        Hand mHand;

        IPlayer *mPlayer;

        State mCurrentState;

        std::string mName;
        pcore::Money mMoney;
        pcore::Money mPot;

};

}

#endif
