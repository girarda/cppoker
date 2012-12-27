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

#include "src/core/Hand.h"

namespace pcore
{
    typedef float Money;
    enum Decision {FOLD, CHECK, CALL};

    class IPlayer
    {
    public:
        virtual Decision makeDecision() = 0;

        virtual void setMoney(Money newValue) = 0;
        virtual void setName(std::string name) = 0;
        
        virtual void seeDealer(std::string dealer) const = 0;
        virtual void seeBigBlind(std::string player, Money bigBlind) const = 0;
        virtual void seeSmallBlind(std::string player, Money smallBlind ) const = 0;
        virtual void seeWinner(std::string winner) const = 0;
        virtual void seeOpponentCards(std::string opponent, const Hand& hand) const = 0;
        virtual void seeOpponentMoney(std::string opponent, Money money) const = 0;
        virtual void seeCards(const Hand& hand) const = 0;
        virtual void seeMoney() const = 0;

        virtual Money getPot() const = 0;
        virtual Money getMoney() const = 0;
        virtual std::string getName() const = 0;

        virtual void clearPot() = 0;
        virtual void addToPot(Money m) = 0;
    };
    
}
#endif
