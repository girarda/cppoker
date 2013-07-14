//
// ChatRoom.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "communication/ChatRoom.h"
#include <boost/bind.hpp>

void ChatRoom::join(ChatParticipantPtr participant)
{
  participants.insert(participant);
  std::for_each(recentMessages.begin(), recentMessages.end(),
      boost::bind(&ChatParticipant::deliver, participant, _1));
}

void ChatRoom::leave(ChatParticipantPtr participant)
{
  participants.erase(participant);
}

void ChatRoom::deliver(const ChatMessage& msg)
{
  recentMessages.push_back(msg);
  while (recentMessages.size() > MAX_RENCENT_MESSAGES)
    recentMessages.pop_front();

  std::for_each(participants.begin(), participants.end(),
      boost::bind(&ChatParticipant::deliver, _1, boost::ref(msg)));
}
