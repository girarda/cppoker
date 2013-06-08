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
    GameEngine::GameEngine(): mVPlayers(), mPlayingPlayers(0), mBigBlind(20),
    mBigBlindPlayer(0), mSmallBlindPlayer(0), mDealer(0), mBet(0)
    {
    }

    /**
     * \fn void GameEngine::startGame()
     *
     * \brief starts a new poker game
     */
    void GameEngine::start()
    {
        for (Player* p: mVPlayers)
        {
            p->start();
        }
        /*while(mPlayingPlayers > 1)
        {
            tableTurn();
            if (mTableTurns % 2 == 0)
                mBigBlind *= 2;
        }
        announceWinner();*/
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
        for (Player* p: mVPlayers)
        {
            p->addCard(mDeck.draw());
            p->addCard(mDeck.draw());
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
        for (Player* p: mVPlayers)
        {
            p->addCard(c1);
            p->addCard(c2);    
            p->addCard(c3);    
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
        for (Player* p: mVPlayers)
        {
            p->addCard(c1);
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
        for (Player* p: mVPlayers)
        {
            p->addCard(c1);
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
        Player* winner = mVPlayers[0];
        for (Player* p: mVPlayers)
        {
            if (p->hasBetterHand(*winner))
                winner = p;
        }
        winner->winMoney(getTotalPot());
        announceWinner();
    }

    /**
     * \fn void GameEngine::playerTurn(Player& player, Money minBet)
     *
     * \brief Announce the information to a player and ask for his decision.
     */
    void GameEngine::playerTurn(Player* player, Money minBet)
    {
        announcements(player);
        if (player->isPlaying() && !player->isFolded())
        {
            Decision d = player->makeDecision();
            if (d == CHECK)
            {
                if (player->getPot() < mBet)
                {
                    player->addToPot(mBet); 
                }
            }
            else if (d == FOLD)
            {
                player->fold();
            }
            else
            {
                mBet += minBet;
                player->addToPot(mBet);
            }
        }
    }

    /**
     * \fn void GameEngine::announcements(const Player& player)
     *
     * \brief Announce the game's information to the player
     */
    void GameEngine::announcements(const Player* player)
    {
        player->seeDealer(*mDealer);
        player->seeBigBlind(*mBigBlindPlayer, mBigBlind);
        player->seeSmallBlind(*mSmallBlindPlayer, mBigBlind/2);
        player->seeCards();
        player->seeMoney();

        for (Player* p : mVPlayers)
        {
            player->seeOpponentCards(*p);
            player->seeOpponentMoney(*p);
        }
    }

    /**
     * \fn void GameEngine::announceWinner()
     *
     * \brief Announce to the players who the winner is
     */
    void GameEngine::announceWinner()
    {
        Player* winner;
        for (Player* p: mVPlayers)
        {
            if (p->isPlaying())
            {
                winner = p;
                break;
            }
        }
        for (Player* p: mVPlayers)
        {
            p->seeWinner(*winner);
        }
    }

    /**
     * \fn void GameEngine::addPlayer(const Player* player)
     * 
     * \brief Add a new player in the game
     */
    void GameEngine::addPlayer(Player* player)
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

        for (Player* p: mVPlayers)
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
        mBet = 0;
        mDeck.shuffle();
        for (Player* p: mVPlayers)
        {
            p->setupForNewTableTurn();
        }
    }

    Money GameEngine::getTotalPot()
    {
        Money totalPot = 0;
        for (Player* p: mVPlayers)
        {
            totalPot += p->getPot();
        }
        return totalPot;
    }

    int GameEngine::getNumberOfPlayers() const
    {
        return mVPlayers.size();
    }
}



