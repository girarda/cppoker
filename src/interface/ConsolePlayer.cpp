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

#include "interface/ConsolePlayer.h"
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
    ConsolePlayer::ConsolePlayer()
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
     * \fn void ConsolePlayer::seeDealer(std::string dealer) const
     * 
     * \brief Announce who the dealer is.
     *
     * \param[in] The name of the dealer
     */
    void ConsolePlayer::seeDealer(std::string dealer) const
    {
        std::cout << "The new dealer is " << dealer << "." << std::endl;
    }

    /**
     * \fn void ConsolePlayer::seeBigBlind(std::string player, pcore::Money bigBlind) const
     *
     * \brief Announce who the big blind is and its value.
     *
     * \param[in] player The name of the player
     * \param[in] bigBlind the big blind's value
     */
    void ConsolePlayer::seeBigBlind(std::string player, pcore::Money bigBlind) const
    {
        std::cout << "The big blind is " << bigBlind << " and the owned by " << player << "." << std::endl;
    }

    /**
     * \fn void ConsolePlayer::seeSmallBlind(std::string player, pcore::Money smallBlind) const
     *
     * \brief Announce who the small blind is and its value.
     *
     * \param[in] player The name of the player
     * \param[in] smallBlind The value of the small blind
     */
    void ConsolePlayer::seeSmallBlind(std::string player, pcore::Money smallBlind) const
    {
        std::cout << "The small blind is " << smallBlind << " and the owned by " << player << "." << std::endl;
    }

    /**
     * \fn void ConsolePlayer::seeWinner(std::string winner) const
     *
     * \brief Announce who the winner is.
     *
     * \param[in] winner The name of the winner
     */
    void ConsolePlayer::seeWinner(std::string winner) const
    {
        std::cout << "The winner is " << winner << "." << std::endl;
    }

    /**
     * \fn void ConsolePlayer::seeOpponentCards(std::string opponent, const pcore::Hand& hand) const
     *
     * \brief Announce the opponnent's cards.
     *
     * \param[in] opponent The name of the opponent
     * \param[in] hand The opponent's hand
     */
    void ConsolePlayer::seeOpponentCards(std::string opponent, const pcore::Hand& hand) const
    {
        //TODO
    }

    /**
     * \fn void ConsolePlayer::seeOpponentMoney(std::string opponent, pcore::Money money) const
     *
     * \brief Announce the opponent's money.
     *
     * \param[in] opponent The opponent's name
     * \param[in] money The opponent's money
     */
    void ConsolePlayer::seeOpponentMoney(std::string opponent, pcore::Money money) const
    {
        //TODO
    }

    /**
     * \fn void ConsolePlayer::seeCards(pcore::Hand hand) const
     * 
     * \brief Announce the player's cards
     *
     * \param[in] the player's hand
     */
    void ConsolePlayer::seeCards(const pcore::Hand& hand) const
    {
        //TODO
    }

    /**
     * \fn void ConsolePlayer::seeMoney() const
     *
     * \brief Announce the player's money
     */
    void ConsolePlayer::seeMoney() const
    {
        //TODO
    }
}
