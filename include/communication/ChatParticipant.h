//
// ChatParticipant.h
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CHATPARTICIPANT_H
#define CHATPARTICIPANT_H

#include <boost/shared_ptr.hpp>
#include "communication/ChatMessage.h"


class ChatParticipant
{
public:
  virtual ~ChatParticipant() {}
  virtual void deliver(const ChatMessage& msg) = 0;
};

typedef boost::shared_ptr<ChatParticipant> ChatParticipantPtr;

#endif
