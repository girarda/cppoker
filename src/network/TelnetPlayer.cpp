#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <string>
#include "utils/Utils.h"
#include "network/TelnetPlayer.h"
#include <sstream>

namespace network
{

const std::string TelnetPlayer::TELNET_NEWLINE = "\r\n";

TelnetPlayer::TelnetPlayer(boost::asio::io_service& io_service, OnlineRoom* gameRoom) :
    socket(io_service),
    buffer(),
    read_state(RS_NOT_WAITING),
    room(gameRoom),
    choice("")
{
}

TelnetPlayer::~TelnetPlayer()
{
}

void TelnetPlayer::start()
{
    deliver("Please enter your name: ");
    read_state = RS_WAITING_FOR_NAME;

    boost::asio::async_read_until(
                socket,
                buffer,
                TELNET_NEWLINE,
                boost::bind(&TelnetPlayer::handleRead, this, _1)
                );
}

tcp::socket& TelnetPlayer::getSocket()
{
    return socket;
}

void TelnetPlayer::deliver(const std::string& message)
{
    std::string msg = message + TELNET_NEWLINE;
    boost::asio::async_write(
                socket,
                boost::asio::buffer(msg.c_str(), msg.length()),
                boost::bind(&TelnetPlayer::handleWrite, this, boost::asio::placeholders::error)
                );
}

void TelnetPlayer::handleRead(const boost::system::error_code& error)
{
    std::string message = utils::toString(&buffer);

    buffer.consume(buffer.size()); //clear buffer
    utils::trimString(message, TELNET_NEWLINE);

    switch (read_state)
    {
    case (RS_WAITING_FOR_NAME):
        setName(message);
        room->join((Player*)this);
        break;
    case (RS_NOT_WAITING):
        sendChatMessage(name, message);
        break;
    case (RS_WAITING_FOR_PLAY):
        choice = message;
        break;
    case (RS_WAITING_FOR_CALL_BET):
        choice = message;
        break;
    }
    read_state = RS_NOT_WAITING;
    boost::asio::async_read_until(
                socket,
                buffer,
                TELNET_NEWLINE,
                boost::bind(&TelnetPlayer::handleRead, this, _1)
                );
}

void TelnetPlayer::handleWrite(const boost::system::error_code& error)
{
}

void TelnetPlayer::seeMoney(float money)
{
    std::stringstream ss;
    ss <<  "You currently have " << money << "$.";
    deliver(ss.str());
}

void TelnetPlayer::seeGamePhase(std::string gamePhase)
{
    std::string msg = "--- Entering " + gamePhase + " ---";
    deliver(msg);
}

void TelnetPlayer::seePlayerTurn(std::string player)
{
    std::string msg = "It is now " + player + "'s turn.";
    deliver(msg);
}

void TelnetPlayer::seeDealer(std::string dealer)
{
    std::string msg = "Dealer is " + dealer;
    deliver(msg);
}

void TelnetPlayer::seeSmallBlind(std::string payer, float amount)
{
    std::stringstream ss;
    ss << "Small Blind is " << payer << " with amount " << utils::toString(amount);
    deliver(ss.str());
}

void TelnetPlayer::seeBigBlind(std::string payer, float amount)
{
    std::stringstream ss;
    ss << "Big Blind is " << payer + " with amount " << utils::toString(amount);
    deliver(ss.str());
}

void TelnetPlayer::seeOpponentMoney(std::string player, float money)
{
    std::stringstream ss;
    ss << "Player " << player << " has " << money << "$.";
    deliver(ss.str());
}

void TelnetPlayer::seeOpponentCards(std::string player, const pokerGame::Hand& playersHand)
{
    std::string msg = "Player " + player + " has " + playersHand.toString() + ".";
    deliver(msg);
}

void TelnetPlayer::seeRoundWinner(std::string player, float moneyWon)
{
    std::stringstream ss;
    ss << "player " << player + " won " << moneyWon << "$ this round.";
    deliver(ss.str());
}

void TelnetPlayer::seeWinner(std::string player)
{
    std::string msg = "player " + player + " won the game.";
    deliver(msg);
}

void TelnetPlayer::sendChatMessage(std::string sender, std::string message)
{
    std::string msg = "Chat: " + sender + ": " + message;
    room->sendChatMessage(msg);
}

void TelnetPlayer::seeCards(const pokerGame::Hand& hand)
{
    std::string msg = "You cards are: " + hand.toString();
    deliver(msg);
}

pokerGame::Decision TelnetPlayer::makeDecision(float minimumBid)
{
    read_state = RS_WAITING_FOR_PLAY;
    decision.choice = pokerGame::WAITING;
    while (decision.choice == pokerGame::WAITING)
    {
        std::stringstream ss;
        ss << "The minimum bet is " << minimumBid << "." << TELNET_NEWLINE
              << "To make a choice, enter:\n\"\"CALL\", \"CHECK\", or \"FOLD\"\n";
        deliver(ss.str());
        while (choice == "")
        {
            boost::this_thread::sleep(boost::posix_time::milliseconds(100));
        }
        if (choice == "CALL")
        {
            read_state = RS_WAITING_FOR_CALL_BET;
            decision.choice = pokerGame::CALL;
            float newBet(-1);
            deliver("How much do you want to call?");
            choice = "";
            do {
                boost::this_thread::sleep(boost::posix_time::milliseconds(100));
                std::istringstream ss(choice);
                ss >> newBet;
            } while (newBet == -1);
            decision.bet = newBet;
        }

        else if (choice == "CHECK")
        {
            decision.choice = pokerGame::CHECK;
            decision.bet = 0;
        }
        else if (choice == "FOLD")
        {
            decision.choice = pokerGame::FOLD;
            decision.bet = 0;
        }
        choice = "";
    }
    return decision;
}

}
