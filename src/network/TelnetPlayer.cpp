#include <boost/bind.hpp>

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

TelnetPlayer::~TelnetPlayer() {

}

void TelnetPlayer::start() {

Write("Please enter your name: ");
read_state = RS_WAITING_FOR_NAME;

boost::asio::async_read_until(
socket,
buffer,
TELNET_NEWLINE,
boost::bind(&TelnetPlayer::HandleRead, this, _1)
);
}

tcp::socket& TelnetPlayer::GetSocket() {
return socket;
}

void TelnetPlayer::Write(const std::string& message) {
boost::asio::async_write(
socket,
boost::asio::buffer(message.c_str(), message.length()),
boost::bind(&TelnetPlayer::HandleWrite, this, boost::asio::placeholders::error)
);
}

void TelnetPlayer::HandleRead(const boost::system::error_code& error) {

//std::istream is(&buffer);
std::string message = AutoToString(&buffer/*is*/);
//std::cout << "Read this: " << is << "\n";

buffer.consume(buffer.size()); //clear buffer

switch (read_state) {
case (RS_WAITING_FOR_NAME):
SetName(message);
room->join((IPlayer*)this);
break;
case (RS_NOT_WAITING):
ChatMessage(name, message);
break;
case (RS_WAITING_FOR_PLAY):
break;
}
read_state = RS_NOT_WAITING;
boost::asio::async_read_until(
socket,
buffer,
TELNET_NEWLINE,
boost::bind(&TelnetPlayer::HandleRead, this, _1)
);
}

void TelnetPlayer::HandleWrite(const boost::system::error_code& error) {}

bool TelnetPlayer::IsPlaying() {
return true;
}

void TelnetPlayer::SetName(const std::string& name) {
this->name = name;
}

string TelnetPlayer::GetName() {
//return name;
}

float TelnetPlayer::GetTotalBalance() {
return total_balance;
}

void TelnetPlayer::seeMoney(float new_value) const {
//total_balance = new_value;
}

void TelnetPlayer::seeDealer(std::string dealer) const {
//string msg = "Dealer is" + dealer;
//Write(msg);
}

void TelnetPlayer::seeSmallBlind(std::string payer, float amount) const {
//string msg = "Small Blind is" + payer + " with amount " + AutoToString(amount);
//Write(msg);
}

void TelnetPlayer::seeBigBlind(std::string payer, float amount) const {
//string msg = "Big Blind is" + payer + " with amount " + AutoToString(amount);
//Write(msg);
}

void TelnetPlayer::seeOpponentMoney(std::string player, float pot) const {
//string msg = "player " + player + " now has " + AutoToString(bank);
//Write(msg);
}

void TelnetPlayer::seeOpponentCards(std::string player, const Hand& players_hand) const{
//string msg = "player " + player + " holds " + players_hand.GetHandTextualDescription();
//Write(msg);
}

void TelnetPlayer::seeWinner(std::string player)const {
//string msg = "player " + player + " won " + AutoToString(winnings);
//Write(msg);
}

void TelnetPlayer::ChatMessage(std::string sender, std::string message) {
string msg = "Chat: " + sender + ": " + message;
//Write(msg);
room->deliver(msg);
}

void TelnetPlayer::seeCards(const Hand& hand) const {
//string msg = "You have been dealt: " + new_card.ToLongString();
//Write(msg);
}

Decision TelnetPlayer::makeDecision(float minimum_bid) {
Decision gc;
return gc;
}

void TelnetPlayer::deliver(const std::string& msg)
{
    Write(msg);
}

}
