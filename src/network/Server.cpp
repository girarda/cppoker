#include <boost/bind.hpp>

#include "network/Server.h"
#include "network/TelnetPlayer.h"

namespace network
{

Server::Server(OnlineRoom* onlineRoom) :
io_service(),
  room(onlineRoom),
connection_acceptor(io_service, tcp::endpoint(tcp::v4(), TELNET_PORT_NUMBER))
{ }

void Server::InitialiseService() {

StartAccept();
io_service.run();

}

void Server::StartAccept() {

TelnetPlayer *new_player = new TelnetPlayer(io_service, room);

connection_acceptor.async_accept(
new_player->GetSocket(),
boost::bind(
&Server::HandleAccept,
this,
new_player,
boost::asio::placeholders::error
)
);

}

void Server::HandleAccept(OnlineUser* newUser, const boost::system::error_code& error) {

if (!error) {
newUser->start();
}

StartAccept();
}

}
