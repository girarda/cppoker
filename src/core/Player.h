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

        void seeDealer(std::string dealer);
        void seeBigBlind(std::string player, Money bigBlind);
        void seeSmallBlind(std::string player, Money smallBlind);
        void seeWinner(std::string winner);
        void seeOpponentCards(std::string opponnent, const Hand& hand);
        void seeOpponentMoney(std::string opponnent, Money money); 

    private:
        Hand mHand;

        IPlayer *mPlayer;

        bool mBigBlind;
        bool mSmallBlind;
        bool mIsPlaying;

};

}

#endif
