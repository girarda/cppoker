//
// ChatMessage.h
// ~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef CHAT_MESSAGE_H
#define CHAT_MESSAGE_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

class ChatMessage
{
public:
  enum { HEADER_LENGTH = 4 };
  enum { MAX_BODY_LENGTH = 512 };

  ChatMessage();

  const char* getData() const;

  char* getData();

  size_t getLength() const;

  const char* getBody() const;

  char* getBody();

  size_t getBodyLength() const;

  void getBodyLength(size_t length);

  bool decodeHeader();

  void encodeHeader();

private:
  char data[HEADER_LENGTH + MAX_BODY_LENGTH];
  size_t bodyLength;
};

#endif
