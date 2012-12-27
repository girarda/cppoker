/**-------------------------/// GameEngine.cpp \\\---------------------------
 *
 * <b>GameEngine.cpp</b>
 * @version : 1.0
 * @since : 2012 Dec 25
 *
 * @description :
 *     Implementation of the GameEngine class
 * @usage :
 *
 * @author : Alexandre Girard | girarda.92@gmail.com
 * @copyright girarda
 * @TODO : Actions when CHECK or CALL
 *
 *--------------------------\\\ GameEngine.cpp ///---------------------------*/

#include "src/core/GameEngine.h"

namespace pcore
{
    /**
     * \fn GameEngine::GameEngine()
     *
     * \brief Default GameEngine constructor
     */
    GameEngine::GameEngine(): mVPlayers(), mPlayingPlayers(0), mPot(0), mBigBlind(20),
    mBigBlindPlayer(0), mSmallBlindPlayer(0), mDealer(0), mBet(0)
    {
    }

    /**
     * \fn void GameEngine::startGame()
     *
     * \brief starts a new poker game
     */
    void GameEngine::startGame()
    {
        while(mPlayingPlayers > 1)
        {
            tableTurn();
            if (mTableTurns % 2 == 0)
                mBigBlind *= 2;
        }
        announceWinner();
    }

    /**
     * \fn void GameEngine::tableTurn()
     *
     * \brief One round
     */
    void GameEngine::tableTurn()
    {
        initTableTurn();

        preFlop();
        if (mPlayingPlayers > 1)
            flop();
        if (mPlayingPlayers > 1)
            turn();
        if (mPlayingPlayers > 1)
            river();
        showdown();

        mTableTurns++;
    }

    /**
     * \fn void GameEngine::preFlop()
     *
     * \brief The Pre-flop phase.
     */
    void GameEngine::preFlop()
    {
        for (Player p: mVPlayers)
        {
            p.addCard(mDeck.draw());
            p.addCard(mDeck.draw());
        }
        playRound(mBigBlind);
    }

    /**
     * \fn void GameEngine::flop()
     *
     * \brief The Flop phase.
     */
    void GameEngine::flop()
    {
        Card c1 = mDeck.draw();
        Card c2 = mDeck.draw();
        Card c3 = mDeck.draw();
        for (Player p: mVPlayers)
        {
            p.addCard(c1);
            p.addCard(c2);    
            p.addCard(c3);    
        }
        playRound(mBigBlind);
    }

    /**
     * \fn void GameEngine::turn()
     *
     * \brief The Turn phase.
     */
    void GameEngine::turn()
    {
        Card c1 = mDeck.draw();
        for (Player p: mVPlayers)
        {
            p.addCard(c1);
        }
        playRound(2*mBigBlind);
    }

    /**
     * \fn void GameEngine::river()
     *
     * \brief The River phase.
     */
    void GameEngine::river()
    {
        Card c1 = mDeck.draw();
        for (Player p: mVPlayers)
        {
            p.addCard(c1);
        }
        playRound(2*mBigBlind);
    }

    /**
     * \fn void GameEngine::showdown()
     *
     * \brief The Showdown phase.
     */
    void GameEngine::showdown()
    {
        Player* winner = &mVPlayers[0];
        for (Player p: mVPlayers)
        {
            if (p.getHand() > winner->getHand())
                winner = &p;
        }
        winner->setMoney(winner->getMoney() + mPot);
        announceWinner();
    }

    /**
     * \fn void GameEngine::playerTurn(Player& player, Money minBet)
     *
     * \brief Announce the information to a player and ask for his decision.
     */
    void GameEngine::playerTurn(Player& player, Money minBet)
    {
        announcements(player);
        if (player.isPlaying() && !player.isFolded())
        {
            Decision d = player.makeDecision();
            if (d == CHECK)
            {
                if (player.getPot() < mBet)
                {
                    Money m = mBet-player.getPot();
                    player.addToPot(m);
                    mPot += m;
                    
                }
            }
            else if (d == FOLD)
            {
                player.setFold(true);
            }
            else
            {
                Money m = mBet-player.getPot() + minBet;
                player.addToPot(m);
                mPot += m;
                mBet += minBet;
            }
        }
    }

    /**
     * \fn void GameEngine::announcements(const Player& player)
     *
     * \brief Announce the game's information to the player
     */
    void GameEngine::announcements(const Player& player)
    {
        player.seeDealer(mDealer->getName());
        player.seeBigBlind(mBigBlindPlayer->getName(), mBigBlind);
        player.seeSmallBlind(mSmallBlindPlayer->getName(), mBigBlind/2);
        player.seeCards();
        player.seeMoney();

        for (Player p : mVPlayers)
        {
            player.seeOpponentCards(p.getName(), p.getHand());
            player.seeOpponentMoney(p.getName(), p.getMoney());
        }
    }

    /**
     * \fn void GameEngine::announceWinner()
     *
     * \brief Announce to the players who the winner is
     */
    void GameEngine::announceWinner()
    {
        std::string winner;
        for (Player p: mVPlayers)
        {
            if (p.isPlaying())
                winner = p.getName();
            break;
        }
        for (Player p: mVPlayers)
        {
            p.seeWinner(winner);
        }
    }

    /**
     * \fn void GameEngine::addPlayer(const Player& player)
     * 
     * \brief Add a new player in the game
     */
    void GameEngine::addPlayer(const Player& player)
    {
        mVPlayers.push_back(player);
        mPlayingPlayers++;
    }

    /**
     * \fn void GameEngine::playRound(Money minBet)
     *
     * \brief Every player on the table plays
     */
    void GameEngine::playRound(Money minBet)
    {

        for (Player p: mVPlayers)
        {
            playerTurn(p, minBet);
        }
    }

    /**
     * \fn void GameEngine::initTableTurn()
     *
     * \brief Initialises the table and the players before a new round.
     */
    void GameEngine::initTableTurn()
    {
        mPot = 0;
        mBet = 0;
        mDeck.shuffle();
        for (Player p: mVPlayers)
        {
            p.setFold(false);
            p.clearPot();
        }
    }
}
