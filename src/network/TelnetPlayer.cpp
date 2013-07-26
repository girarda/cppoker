#include <boost/bind.hpp>
#include <string>
#include "utils/Utils.h"
#include "network/TelnetPlayer.h"

namespace network
{

const std::string TELNET_NEWLINE = "\n";

TelnetPlayer::TelnetPlayer(boost::asio::io_service& io_service, OnlineRoom* gameRoom) :
    socket(io_service),
    buffer(),
    read_state(RS_NOT_WAITING),
    name(),
    room(gameRoom)
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
    boost::asio::async_write(
                socket,
                boost::asio::buffer(message.c_str(), message.length()),
                boost::bind(&TelnetPlayer::handleWrite, this, boost::asio::placeholders::error)
                );
}

void TelnetPlayer::handleRead(const boost::system::error_code& error)
{
    std::string message = utils::autoToString(&buffer/*is*/);

    buffer.consume(buffer.size()); //clear buffer

    switch (read_state)
    {
    case (RS_WAITING_FOR_NAME):
        setName(message);
        room->join((IPlayer*)this);
        break;
    case (RS_NOT_WAITING):
        sendChatMessage(name, message);
        break;
    case (RS_WAITING_FOR_PLAY):
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

bool TelnetPlayer::isPlaying()
{
    return true;
}

void TelnetPlayer::setName(const std::string& name)
{
    this->name = name;
}

std::string TelnetPlayer::getName()
{
    return name;
}

float TelnetPlayer::getTotalBalance()
{
    return total_balance;
}

void TelnetPlayer::seeMoney(float new_value)
{
    //    total_balance = new_value;
}

void TelnetPlayer::seeDealer(std::string dealer)
{
    //string msg = "Dealer is" + dealer;
    //Write(msg);
}

void TelnetPlayer::seeSmallBlind(std::string payer, float amount)
{
    //string msg = "Small Blind is" + payer + " with amount " + AutoToString(amount);
    //Write(msg);
}

void TelnetPlayer::seeBigBlind(std::string payer, float amount)
{
    //string msg = "Big Blind is" + payer + " with amount " + AutoToString(amount);
    //Write(msg);
}

void TelnetPlayer::seeOpponentMoney(std::string player, float pot)
{
    //string msg = "player " + player + " now has " + AutoToString(bank);
    //Write(msg);
}

void TelnetPlayer::seeOpponentCards(std::string player, const pokerGame::Hand& playersHand)
{
    //string msg = "player " + player + " holds " + players_hand.GetHandTextualDescription();
    //Write(msg);
}

void TelnetPlayer::seeWinner(std::string player)
{
    //string msg = "player " + player + " won " + AutoToString(winnings);
    //Write(msg);
}

void TelnetPlayer::sendChatMessage(std::string sender, std::string message)
{
    std::string msg = "Chat: " + sender + ": " + message;
    //Write(msg);
    room->sendChatMessage(msg);
}

void TelnetPlayer::seeCards(const pokerGame::Hand& hand)
{
    //string msg = "You have been dealt: " + new_card.ToLongString();
    //Write(msg);
}

pokerGame::Decision TelnetPlayer::makeDecision(float minimumBid)
{
    read_state = RS_WAITING_FOR_PLAY;
    while (true)
    {
        deliver("To make a choice, enter:\n\"\"CALL\", \"CHECK\", or \"FOLD\"\n");
        // TODO: wait for answer
        if (choice == "CALL\n")
        {
            decision.choice = pokerGame::CALL;
            float newBet;
            do {
                // TODO: get answer
            } while (0 /*TODO: while the answer is a number*/);
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

}
