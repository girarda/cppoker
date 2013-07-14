//
// Server.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "communication/Server.h"

ChatServer::ChatServer(boost::asio::io_service& io_service, const tcp::endpoint& endpoint) :
    ioService(io_service),
    acceptor(io_service, endpoint)
{
  ChatSessionPtr newSession(new ChatSession(ioService, room));
  acceptor.async_accept(newSession->getSocket(),
      boost::bind(&ChatServer::handleAccept, this, newSession,
        boost::asio::placeholders::error));
}

void ChatServer::handleAccept(ChatSessionPtr session,
    const boost::system::error_code& error)
{
  if (!error)
  {
    session->start();
    ChatSessionPtr newSession(new ChatSession(ioService, room));
    acceptor.async_accept(newSession->getSocket(),
        boost::bind(&ChatServer::handleAccept, this, newSession,
          boost::asio::placeholders::error));
  }
}
