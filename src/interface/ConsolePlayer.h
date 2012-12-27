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
        
        virtual void seeDealer(std::string dealer) const;
        virtual void seeBigBlind(std::string player, pcore::Money bigBlind) const;
        virtual void seeSmallBlind(std::string player, pcore::Money smallBlind) const;
        virtual void seeWinner(std::string winner) const;
        virtual void seeOpponentCards(std::string opponent, const pcore::Hand& hand) const;
        virtual void seeOpponentMoney(std::string opponent, pcore::Money money) const;
        virtual void seeCards(const pcore::Hand& han) const;
        virtual void seeMoney() const;

        virtual pcore::Money getMoney() const ;
        virtual pcore::Money getPot() const;
        virtual std::string getName() const;

        virtual void clearPot();
        virtual void addToPot(pcore::Money m);
    private:
        std::string mName;
        pcore::Money mMoney;
        pcore::Money mPot;
    };
}
