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
#include "src/core/Hand.h"
#include "src/core/IPlayer.h"

namespace pcore
{

class Player
{
    public:
        Player(IPlayer *playerImpl);

        Decision makeDecision();

        void setMoney(Money newValue);
        void setName(std::string name);
        void setFold(bool fold);
        void clearPot();

        Money getMoney() const;
        std::string getName() const;
        Hand getHand() const;
        Money getPot() const;

        bool isPlaying() const;
        bool isFolded() const;

        void addCard(const Card& card);
        void addToPot(Money m);

        void seeDealer(std::string dealer) const;
        void seeBigBlind(std::string player, Money bigBlind) const;
        void seeSmallBlind(std::string player, Money smallBlind) const;
        void seeWinner(std::string winner) const;
        void seeOpponentCards(std::string opponnent, const Hand& hand) const;
        void seeOpponentMoney(std::string opponnent, Money money) const; 
        void seeCards() const;
        void seeMoney() const;

    private:
        Hand mHand;

        IPlayer *mPlayer;

        bool mBigBlind;
        bool mSmallBlind;
        bool mIsPlaying;
        bool mIsFolded;

};

}

#endif
