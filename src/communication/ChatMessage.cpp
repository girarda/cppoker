//
// ChatMessage.cpp
// ~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include "communication/ChatMessage.h"

ChatMessage::ChatMessage() : bodyLength(0)
{
}

const char* ChatMessage::getData() const
{
  return data;
}

char* ChatMessage::getData()
{
  return data;
}

size_t ChatMessage::getLength() const
{
  return HEADER_LENGTH + bodyLength;
}

const char* ChatMessage::getBody() const
{
  return data + HEADER_LENGTH;
}

char* ChatMessage::getBody()
{
  return data + HEADER_LENGTH;
}

size_t ChatMessage::getBodyLength() const
{
  return bodyLength;
}

void ChatMessage::getBodyLength(size_t length)
{
  bodyLength = length;
  if (bodyLength > MAX_BODY_LENGTH)
    bodyLength = MAX_BODY_LENGTH;
}

bool ChatMessage::decodeHeader()
{
  using namespace std; // For strncat and atoi.
  char header[HEADER_LENGTH + 1] = "";
  strncat(header, data, HEADER_LENGTH);
  bodyLength = atoi(header);
  if (bodyLength > MAX_BODY_LENGTH)
  {
    bodyLength = 0;
    return false;
  }
  return true;
}

void ChatMessage::encodeHeader()
{
  using namespace std; // For sprintf and memcpy.
  char header[HEADER_LENGTH + 1] = "";
  sprintf(header, "%4d", bodyLength);
  memcpy(data, header, HEADER_LENGTH);
}
