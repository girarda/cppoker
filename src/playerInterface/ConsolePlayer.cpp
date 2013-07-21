#include "playerInterface/ConsolePlayer.h"
#include <iostream>

namespace playerInterface
{
ConsolePlayer::ConsolePlayer()
{
}

pokerGame::Decision ConsolePlayer::makeDecision(float minBet)
{

    std::string choice;
    pokerGame::Decision decision;

    while (true)
    {
        std::cout << "To make a choice, enter:" << std::endl <<
                     "\"CALL\", \"CHECK\", or \"FOLD\"" << std::endl;
        std::cin >> choice;
        if (choice == "CALL\n")
        {
            decision.choice = pokerGame::CALL;
            float newBet;
            do {
                std::cin >> newBet;
            } while (std::cin.fail());
            decision.bet = newBet;
        }

        else if (choice == "CHECK\n")
        {
            decision.choice = pokerGame::CHECK;
            decision.bet = 0;
        }
        else if (choice == "FOLD\n")
        {
            decision.choice = pokerGame::FOLD;
            decision.bet = 0;
        }
    }
    return decision;
}

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

void ConsolePlayer::seeWinner(std::string winner) const
{
    std::cout << "The winner is " << winner << "." << std::endl;
}

void ConsolePlayer::seeOpponentCards(std::string opponent, const pokerGame::Hand& hand) const
{
    //TODO
}

void ConsolePlayer::seeOpponentMoney(std::string opponent, float money) const
{
    //TODO
}

void ConsolePlayer::seeCards(const pokerGame::Hand& hand) const
{
    //TODO
}

void ConsolePlayer::seeMoney(float money) const
{
    //TODO
}

}
