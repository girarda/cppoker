//
// Server.h
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef SERVER_H
#define SERVER_H

#include <list>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "communication/ChatMessage.h"
#include "communication/ChatParticipant.h"
#include "communication/ChatRoom.h"
#include "communication/Chatsession.h"

using boost::asio::ip::tcp;

class ChatServer
{
public:
  ChatServer(boost::asio::io_service& io_service, const tcp::endpoint& endpoint);

  void handleAccept(ChatSessionPtr session, const boost::system::error_code& error);

private:
  boost::asio::io_service& ioService;
  tcp::acceptor acceptor;
  ChatRoom room;
};

typedef boost::shared_ptr<ChatServer> ChatServerPtr;
typedef std::list<ChatServerPtr> ChatServerList;

#endif
