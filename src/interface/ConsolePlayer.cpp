/**-------------------------/// ConsolePlayer.cpp \\\---------------------------
 *
 * <b>ConsolePlayer.cpp</b>
 * @version : 1.0
 * @since : 2012 Dec 23
 *
 * @description :
 *     Implementation of the ConsolePlayer class.
 * @usage :
 *
 * @author : Alexandre Girard | girarda.92@gmail.com
 * @copyright girarda
 * @TODO : MISSING METHODS, MAKEDECISION, ADD DOC
 *
 *--------------------------\\\ ConsolePlayer.cpp ///---------------------------*/

#include "src/interface/ConsolePlayer.h"
#include <iostream>

namespace pinterface
{
    /**
     * \fn ConsolePlayer::ConsolePlayer(std::string name, pcore::Money initMoney)
     *
     * \brief The ConsolePlayer constructor
     *
     * \param[in] name The name of the player
     * \param[in] initMoney The player's initial money
     */
    ConsolePlayer::ConsolePlayer(std::string name, pcore::Money initMoney): mName(name), mMoney(initMoney), mPot(0)
    {
    }

    /**
     * \fn pcore::Decision ConsolePlayer::makeDecision()
     *
     * \brief Get the player's decision from the cin.
     *
     * \return the player's Decision
     */
    pcore::Decision ConsolePlayer::makeDecision()
    {
        
        std::string choice;
        
        while (true)
        {
            std::cout << "To make a choice, enter:" << std::endl <<
                "\"CALL\", \"CHECK\", or \"FOLD\"" << std::endl;
            std::cin >> choice;
            if (choice == "CALL\n")
            {
                //TODO call
                return pcore::CALL;
            }
            else if (choice == "CHECK\n")
            {
                //TODO check
                return pcore::CHECK;
            }
            else if (choice == "FOLD\n")
            {
                //TODO fold
                return pcore::FOLD;
            }
        }
    }

    /**
     * \fn void ConsolePlayer::setMoney(pcore::Money newValue)
     *
     * \brief Sets the new amount of money the player has.
     *
     * \param[in] newValue The new amount of money
     */
    void ConsolePlayer::setMoney(pcore::Money newValue)
    {
        mMoney = newValue;
    }

    /**
     * \fn void ConsolePlayer::setName(std::string name)
     *
     * \brief Sets the new player's name.
     *
     * \param[in] The new name
     */
    void ConsolePlayer::setName(std::string name)
    {
        mName = name;
    }

    /**
     * \fn void ConsolePlayer::seeDealer(std::string dealer)
     * 
     * \brief Announce who the dealer is.
     *
     * \param[in] The name of the dealer
     */
    void ConsolePlayer::seeDealer(std::string dealer)
    {
        std::cout << "The new dealer is " << dealer << "." << std::endl;
    }

    /**
     * \fn void ConsolePlayer::seeBigBlind(std::string player, pcore::Money bigBlind)
     *
     * \brief Announce who the big blind is and its value.
     *
     * \param[in] player The name of the player
     * \param[in] bigBlind the big blind's value
     */
    void ConsolePlayer::seeBigBlind(std::string player, pcore::Money bigBlind)
    {
        std::cout << "The big blind is " << bigBlind << " and the owned by " << player << "." << std::endl;
    }

    /**
     * \fn void ConsolePlayer::seeSmallBlind(std::string player, pcore::Money smallBlind)
     *
     * \brief Announce who the small blind is and its value.
     *
     * \param[in] player The name of the player
     * \param[in] smallBlind The value of the small blind
     */
    void ConsolePlayer::seeSmallBlind(std::string player, pcore::Money smallBlind)
    {
        std::cout << "The small blind is " << smallBlind << " and the owned by " << player << "." << std::endl;
    }

    /**
     * \fn void ConsolePlayer::seeWinner(std::string winner)
     *
     * \brief Announce who the winner is.
     *
     * \param[in] winner The name of the winner
     */
    void ConsolePlayer::seeWinner(std::string winner)
    {
        std::cout << "The winner is " << winner << "." << std::endl;
    }

    /**
     * \fn void ConsolePlayer::seeOpponentCards(std::string opponent, const pcore::Hand& hand)
     *
     * \brief Announce the opponnent's cards.
     *
     * \param[in] opponent The name of the opponent
     * \param[in] hand The opponent's hand
     */
    void ConsolePlayer::seeOpponentCards(std::string opponent, const pcore::Hand& hand)
    {
        //TODO
    }

    /**
     * \fn void ConsolePlayer::seeOpponentMoney(std::string opponent, pcore::Money money)
     *
     * \brief Announce the opponent's money.
     *
     * \param[in] opponent The opponent's name
     * \param[in] money The opponent's money
     */
    void ConsolePlayer::seeOpponentMoney(std::string opponent, pcore::Money money)
    {
        //TODO
    }

    /**
     * \fn pcore::Money ConsolePlayer::getMoney() const
     * 
     * \brief Return the player's amount of money.
     *
     * \return the player's amount of money
     */
    pcore::Money ConsolePlayer::getMoney() const
    {
        return mMoney;
    }

    /**
     * \fn pcore::Money ConsolePlayer::getPot() const
     *
     * \brief Return the player's pot.
     *
     * \return the player's pot
     */
    pcore::Money ConsolePlayer::getPot() const
    {
        return mPot;
    }

    /**
     * \fn std::string ConsolePlayer::getName() const
     *
     * \brief Return the player's name.
     *
     * \return the player's name
     */
    std::string ConsolePlayer::getName() const
    {
        return mName;
    }
}
