#include "playerController/ConsolePlayer.h"
#include "utils/Utils.h"
#include <iostream>

namespace playerController {

ConsolePlayer::ConsolePlayer() {
}

pokerGame::Decision ConsolePlayer::makeDecision(const std::vector<pokerGame::card::Card> &holeCards, const std::vector<pokerGame::card::Card> &sharedCards, float minBet, float bigBlind, pokerGame::modeling::BettingContext* bettingContext, const std::vector<pokerGame::modeling::OpponentModel> &opponents) {

    std::string choice;
    pokerGame::Decision decision;

    while (true) {
        std::cout << "To make a choice, enter:" << std::endl <<
                     "\"RAISE\", \"CALL\", or \"FOLD\"" << std::endl;
        std::cin >> choice;
        if (choice == "RAISE\n") {
            decision.choice = pokerGame::RAISE;
            float newBet;
            do {
                std::cin >> newBet;
            } while (std::cin.fail() && newBet > minBet);
            decision.bet = newBet;
        } else if (choice == "CALL") {
            decision.choice = pokerGame::CALL;
            decision.bet = 0;
        } else if (choice == "FOLD\n") {
            decision.choice = pokerGame::FOLD;
            decision.bet = 0;
        }
    }
    return decision;
}

void ConsolePlayer::seeDealer(std::string dealer) {
    std::string message = "The new dealer is " + dealer + ".";
    deliver(message);
}

void ConsolePlayer::seeBigBlind(std::string player, float bigBlind) {
    std::string message = "The big blind is " + utils::toString(bigBlind) + " and the owned by " + player + ".";
    deliver(message);
}

void ConsolePlayer::seeSmallBlind(std::string player, float smallBlind) {
    std::string message = "The small blind is " + utils::toString(smallBlind) + " and the owned by " + player + ".";
    deliver(message);
}

void ConsolePlayer::seeWinner(std::string winner) {
    std::string message = "The winner is " + winner + ".";
    deliver(message);
}

void ConsolePlayer::seeOpponentHole(std::string opponent, const pokerGame::card::Hand& hand) {
    std::string msg = "Player " + opponent + " has " + hand.toString() + ".";
    deliver(msg);
}

void ConsolePlayer::seeOpponentMoney(std::string opponent, float money) {
    std::stringstream ss;
    ss << "Player " << opponent << " has " << money << "$.";
    deliver(ss.str());
}

void ConsolePlayer::seeHoleCards(const std::vector<pokerGame::card::Card> &holeCards) {
    std::string msg = "You cards are: " + holeCards[0].toString() + " ," + holeCards[1].toString();
    deliver(msg);
}

void ConsolePlayer::seeMoney(float money) {
    std::stringstream ss;
    ss <<  "You currently have " << money << "$.";
    deliver(ss.str());
}

void ConsolePlayer::deliver(std::string msg) {
    std::cout << msg << std::endl;
}

}
