#include "playerInterface/ConsolePlayer.h"
#include "utils/Utils.h"
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

void ConsolePlayer::seeDealer(std::string dealer)
{
    std::string message = "The new dealer is " + dealer + ".";
    deliver(message);
}

void ConsolePlayer::seeBigBlind(std::string player, float bigBlind)
{
    std::string message = "The big blind is " + utils::toString(bigBlind) + " and the owned by " + player + ".";
    deliver(message);
}

void ConsolePlayer::seeSmallBlind(std::string player, float smallBlind)
{
    std::string message = "The small blind is " + utils::toString(smallBlind) + " and the owned by " + player + ".";
    deliver(message);
}

void ConsolePlayer::seeWinner(std::string winner)
{
    std::string message = "The winner is " + winner + ".";
    deliver(message);
}

void ConsolePlayer::seeOpponentCards(std::string opponent, const pokerGame::Hand& hand)
{
    //TODO
}

void ConsolePlayer::seeOpponentMoney(std::string opponent, float money)
{
    //TODO
}

void ConsolePlayer::seeCards(const pokerGame::Hand& hand)
{
    //TODO
}

void ConsolePlayer::seeMoney(float money)
{
    //TODO
}

void ConsolePlayer::deliver(const std::string &msg)
{
    std::cout << msg << std::endl;
}

}
