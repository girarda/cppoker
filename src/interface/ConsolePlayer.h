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

#include "src/core/IPlayer.h"
#include <string>

namespace pinterface
{
    class ConsolePlayer : public pcore::IPlayer
    {
    public:
        ConsolePlayer(std::string name, pcore::Money initMoney);

        virtual pcore::Decision makeDecision();

        virtual void setMoney(pcore::Money newValue);
        virtual void setName(std::string name);
        
        virtual void seeDealer(std::string dealer);
        virtual void seeBigBlind(std::string player, pcore::Money bigBlind);
        virtual void seeSmallBlind(std::string player, pcore::Money smallBlind);
        virtual void seeWinner(std::string winner);
        virtual void seeOpponentCards(std::string opponent, const pcore::Hand& hand);
        virtual void seeOpponentMoney(std::string opponent, pcore::Money money);

        virtual pcore::Money getMoney() const ;
        virtual pcore::Money getPot() const;
        virtual std::string getName() const;
    private:
        std::string mName;
        pcore::Money mMoney;
        pcore::Money mPot;
    };
}
