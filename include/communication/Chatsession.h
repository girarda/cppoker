//
// ChatSession.h
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CHATSESSION_H
#define CHATSESSION_H

#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "communication/ChatParticipant.h"
#include "communication/ChatRoom.h"

using boost::asio::ip::tcp;

class ChatSession
  : public ChatParticipant,
    public boost::enable_shared_from_this<ChatSession>
{
public:
  ChatSession(boost::asio::io_service& io_service, ChatRoom& room);

  tcp::socket& getSocket();

  void start();

  void deliver(const ChatMessage& msg);

  void handleReadHeader(const boost::system::error_code& error);

  void handleReadBody(const boost::system::error_code& error);

  void handleWrite(const boost::system::error_code& error);

private:
  tcp::socket socket;
  ChatRoom& room;
  ChatMessage readMessage;
  ChatMessageQueue writeMessages;
};

typedef boost::shared_ptr<ChatSession> ChatSessionPtr;


#endif
