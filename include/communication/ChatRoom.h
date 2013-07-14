//
// ChatRoom.h
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CHATROOM_H
#define CHATROOM_H

#include <deque>
#include <set>
#include "communication/ChatParticipant.h"
#include <boost/bind.hpp>

typedef std::deque<ChatMessage> ChatMessageQueue;

class ChatRoom
{
public:

  void join(ChatParticipantPtr participant);
  void leave(ChatParticipantPtr participant);
  void deliver(const ChatMessage& msg);

private:
  std::set<ChatParticipantPtr> participants;
  enum { MAX_RENCENT_MESSAGES = 100 };
  ChatMessageQueue recentMessages;
};

#endif
