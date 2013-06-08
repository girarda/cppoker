/**-------------------------/// IPlayer.h \\\---------------------------
 *
 * <b>IPlayer.h</b>
 * @version : 1.0
 * @since : 2012 Sep 03
 *
 * @description :
 *     Interface of the Player class
 * @usage :
 *
 * @author : Alexandre Girard | girarda.92@gmail.com
 * @copyright girarda
 * @TODO :
 *
 *--------------------------\\\ IPlayer.h ///---------------------------*/

#ifndef IPlayer_H
#define IPlayer_H

#include "core/Hand.h"
#include "core/Money.h"

namespace pcore
{
    enum Decision {FOLD, CHECK, CALL};

    class IPlayer
    {
    public:
        virtual Decision makeDecision() = 0;

        virtual void seeDealer(std::string dealer) const = 0;
        virtual void seeBigBlind(std::string player, Money bigBlind) const = 0;
        virtual void seeSmallBlind(std::string player, Money smallBlind ) const = 0;
        virtual void seeWinner(std::string winner) const = 0;
        virtual void seeOpponentCards(std::string opponent, const Hand& hand) const = 0;
        virtual void seeOpponentMoney(std::string opponent, Money money) const = 0;
        virtual void seeCards(const Hand& hand) const = 0;
        virtual void seeMoney() const = 0;
    };
    
}
#endif
