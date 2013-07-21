/*
* TelnetPlayer.h
*
* Connects the GameEngine to a Player communicating via a Telnet session.
*/

#ifndef TELNETPLAYER_H_
#define TELNETPLAYER_H_

#include <boost/asio.hpp>

#include "core/IPlayer.h"
#include "network/OnlineUser.h"
#include "core/Hand.h"

#include "network/OnlineRoom.h"

namespace network
{

using namespace pcore;
using namespace std;
using boost::asio::ip::tcp;

enum SOCKET_READ_STATE {
RS_WAITING_FOR_NAME,
RS_WAITING_FOR_PLAY,
RS_NOT_WAITING
};

class TelnetPlayer : public IPlayer, public OnlineUser {

public:
TelnetPlayer(boost::asio::io_service& io_service, OnlineRoom* room);
virtual void start();
//void ReadyForInput();
virtual tcp::socket& GetSocket();

bool IsPlaying();
string GetName();
float GetTotalBalance();
void SetTotalBalance(float new_value);

virtual void seeDealer(std::string dealer) const;
virtual void seeBigBlind(std::string player, float bigBlind) const;
virtual void seeSmallBlind(std::string player, float smallBlind ) const;
virtual void seeWinner(std::string winner) const;
virtual void seeOpponentCards(std::string opponent, const Hand& hand) const;
virtual void seeOpponentMoney(std::string opponent, float money) const;
virtual void seeCards(const Hand& hand) const;
virtual void seeMoney(float money) const;

void ChatMessage(std::string sender, std::string message);
void CardDealt(const Hand& hand, const Card& new_card);
Decision makeDecision(float minimum_bid);

virtual void deliver(const std::string& msg);

private:
tcp::socket socket;
boost::asio::streambuf buffer;
SOCKET_READ_STATE read_state;

std::string name;
float total_balance;

OnlineRoom* room;

void SetName(const std::string& name);

void Write(const std::string& message);
void HandleRead(const boost::system::error_code& error);
void HandleWrite(const boost::system::error_code& error);

~TelnetPlayer();
};

template <class T>
std::string AutoToString(const T& obj) {
stringstream ss;
ss << obj;
return ss.str();
}

}

#endif
