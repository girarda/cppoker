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
    pcore::Decision ConsolePlayer::makeDecision(float minBet)
    {
        
        std::string choice;
        pcore::Decision decision;
        
        while (true)
        {
            std::cout << "To make a choice, enter:" << std::endl <<
                "\"CALL\", \"CHECK\", or \"FOLD\"" << std::endl;
            std::cin >> choice;
            if (choice == "CALL\n")
            {
                decision.choice = pcore::CALL;
                float newBet;
                do {
                    std::cin >> newBet;
                } while (std::cin.fail());
                decision.bet = newBet;
             }
            
            else if (choice == "CHECK\n")
            {
                decision.choice = pcore::CHECK;
                decision.bet = 0;
            }
            else if (choice == "FOLD\n")
            {
                decision.choice = pcore::FOLD;
                decision.bet = 0;
            }
        }
        return decision;
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

    void ConsolePlayer::seeBigBlind(std::string player, float bigBlind) const
    {
        std::cout << "The big blind is " << bigBlind << " and the owned by " << player << "." << std::endl;
    }

    void ConsolePlayer::seeSmallBlind(std::string player, float smallBlind) const
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

    void ConsolePlayer::seeOpponentMoney(std::string opponent, float money) const
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
    void ConsolePlayer::seeMoney(float money) const
    {
        //TODO
    }
}
