//
// ChatSession.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "include/communication/Chatsession.h"

ChatSession::ChatSession(boost::asio::io_service& io_service, ChatRoom& room) :
    socket(io_service),
    room(room)
{
}

tcp::socket& ChatSession::getSocket()
{
  return socket;
}

void ChatSession::start()
{
  room.join(shared_from_this());
  boost::asio::async_read(socket,
      boost::asio::buffer(readMessage.getData(), ChatMessage::HEADER_LENGTH),
      boost::bind(
        &ChatSession::handleReadHeader, shared_from_this(),
        boost::asio::placeholders::error));
}

void ChatSession::deliver(const ChatMessage& msg)
{
  bool write_in_progress = !writeMessages.empty();
  writeMessages.push_back(msg);
  if (!write_in_progress)
  {
    boost::asio::async_write(socket,
        boost::asio::buffer(writeMessages.front().getData(),
          writeMessages.front().getLength()),
        boost::bind(&ChatSession::handleWrite, shared_from_this(),
          boost::asio::placeholders::error));
  }
}

void ChatSession::handleReadHeader(const boost::system::error_code& error)
{
  if (!error && readMessage.decodeHeader())
  {
    boost::asio::async_read(socket,
        boost::asio::buffer(readMessage.getBody(), readMessage.getBodyLength()),
        boost::bind(&ChatSession::handleReadBody, shared_from_this(),
          boost::asio::placeholders::error));
  }
  else
  {
    room.leave(shared_from_this());
  }
}

void ChatSession::handleReadBody(const boost::system::error_code& error)
{
  if (!error)
  {
    room.deliver(readMessage);
    boost::asio::async_read(socket,
        boost::asio::buffer(readMessage.getData(), ChatMessage::HEADER_LENGTH),
        boost::bind(&ChatSession::handleReadHeader, shared_from_this(),
          boost::asio::placeholders::error));
  }
  else
  {
    room.leave(shared_from_this());
  }
}

void ChatSession::handleWrite(const boost::system::error_code& error)
{
  if (!error)
  {
    writeMessages.pop_front();
    if (!writeMessages.empty())
    {
      boost::asio::async_write(socket,
          boost::asio::buffer(writeMessages.front().getData(),
            writeMessages.front().getLength()),
          boost::bind(&ChatSession::handleWrite, shared_from_this(),
            boost::asio::placeholders::error));
    }
  }
  else
  {
    room.leave(shared_from_this());
  }
}
