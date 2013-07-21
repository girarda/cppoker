/*
* TelnetServer.h
*
* This is the entry point for the TelnetServer providing the
* pathway for people to play Poker via a Telnet connection.
*
* The Telnet service is provided by the Boost::ASIO (Asyncronous IO Library)
*/

#ifndef TELNETSERVER_H_
#define TELNETSERVER_H_

#include <boost/asio.hpp>
#include "core/IPlayer.h"
#include "network/OnlineRoom.h"
#include "network/OnlineUser.h"

namespace network
{

const short TELNET_PORT_NUMBER = 13305;

using boost::asio::ip::tcp;

class Server {
public:
Server(OnlineRoom* onlineRoom);
void InitialiseService();
private:
boost::asio::io_service io_service;
tcp::acceptor connection_acceptor;

OnlineRoom* room;

void StartAccept();
void HandleAccept(OnlineUser* newUser, const boost::system::error_code& error);
};

}

#endif
