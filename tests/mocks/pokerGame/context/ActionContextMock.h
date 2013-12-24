#ifndef ACTIONCONTEXTMOCK_H_
#define ACTIONCONTEXTMOCK_H_

#include "pokerGame/context/ActionContext.h"
#include "gmock/gmock.h"

namespace tests {

class ActionContextMock : public pokerGame::context::ActionContext {
public:
    MOCK_CONST_METHOD1(operator==, bool(const ActionContext& other));
};

}

#endif
