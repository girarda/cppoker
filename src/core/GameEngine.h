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

#include "src/core/Player.h"
#include "src/core/Deck.h"

namespace pcore
{

class GameEngine
{
    public:
        GameEngine();

        void startGame();
        void tableTurn();
        void playerTurn(Player& player, pcore::Money minBet);
        void announcements(const Player& player);

        void preFlop();
        void flop();
        void turn();
        void river();
        void showdown();

        void addPlayer(const Player& player);
        void playRound(Money minBet);

    private:
        void announceWinner();
        void initTableTurn();

        Deck mDeck;
        std::vector<Player> mVPlayers;
        int mPlayingPlayers;
        int mTableTurns;
        Money mPot;
        Money mBet;
        Money mBigBlind;
        Player* mBigBlindPlayer;
        Player* mSmallBlindPlayer;
        Player* mDealer;
};
}

