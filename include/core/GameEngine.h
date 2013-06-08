/**-------------------------/// GameEngine.h \\\---------------------------
 *
 * <b>Player</b>
 * @version : 1.0
 * @since : 2012 Dec 25
 *
 * @description :
 *     Interface of the GameEngine class.
 * @usage :
 *
 * @author : Alexandre Girard | girarda.92@gmail.com
 * @copyright girarda
 * @TODO : ADD DOC
 *
 *--------------------------\\\ GameEngine.h ///---------------------------*/

#include "core/Player.h"
#include "core/Deck.h"
#include "core/Money.h"

namespace pcore
{

class GameEngine
{
    public:
        GameEngine();

        void start();
        void tableTurn();
        void playerTurn(Player* player, pcore::Money minBet);
        void announcements(const Player* player);

        void preFlop();
        void flop();
        void turn();
        void river();
        void showdown();

        void addPlayer(Player* player);
        void playRound(Money minBet);

        Money getTotalPot();

        void announceWinner();
        void initTableTurn();

        int getNumberOfPlayers() const;

    private:

        Deck mDeck;
        std::vector<Player*> mVPlayers;
        int mPlayingPlayers;
        int mTableTurns;
        Money mBet;
        Money mBigBlind;
        Player* mBigBlindPlayer;
        Player* mSmallBlindPlayer;
        Player* mDealer;
};
}

