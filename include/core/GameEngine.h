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

namespace pcore
{

class GameEngine
{
    public:
        GameEngine();

        void start();
        void tableTurn();
        void playerTurn(Player* player, float minBet);
        void announcements(const Player* player);

        void preFlop();
        void flop();
        void turn();
        void river();
        void showdown();

        void addPlayer(Player* player);
        void playRound(float minBet);

        float getTotalPot();

        void announceWinner();
        void initTableTurn();
        void betBlinds();

        int getNumberOfPlayers() const;

    private:

        Deck mDeck;
        std::vector<Player*> mVPlayers;
        int mPlayingPlayers;
        int mTableTurns;
        float mBet;
        float mBigBlind;
        Player* mBigBlindPlayer;
        Player* mSmallBlindPlayer;
        Player* mDealer;
};
}

