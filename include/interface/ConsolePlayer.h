/**-------------------------/// ConsolePlayer.h \\\---------------------------
 *
 * <b>ConsolePlayer.h</b>
 * @version : 1.0
 * @since : 2012 Dec 23
 *
 * @description :
 *     Interface of the ConsolePlayer class
 * @usage :
 *
 * @author : Alexandre Girard | girarda.92@gmail.com
 * @copyright girarda
 * @TODO :
 *
 *--------------------------\\\ ConsolePlayer.h ///---------------------------*/

#include "core/IPlayer.h"
#include "core/Money.h"
#include <string>

namespace pinterface
{
    class ConsolePlayer : public pcore::IPlayer
    {
    public:
        ConsolePlayer();

        virtual pcore::Decision makeDecision(const pcore::Money& minBet);

        virtual void seeDealer(std::string dealer) const;
        virtual void seeBigBlind(std::string player, pcore::Money bigBlind) const;
        virtual void seeSmallBlind(std::string player, pcore::Money smallBlind) const;
        virtual void seeWinner(std::string winner) const;
        virtual void seeOpponentCards(std::string opponent, const pcore::Hand& hand) const;
        virtual void seeOpponentMoney(std::string opponent, pcore::Money money) const;
        virtual void seeCards(const pcore::Hand& hand) const;
        virtual void seeMoney(const pcore::Money& money) const;
    };
}
