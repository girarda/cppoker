#ifndef BETTINGACTION_H
#define BETTINGACTION_H

#include "pokerGame/context/BettingContext.h"
#include "pokerGame/Decision.h"

namespace pokerGame {
namespace context {

class ActionContext
{
public:
    ActionContext(BettingContext currentContext, Decision decisionMade);

    bool operator==(const ActionContext& other) const;

private:
    BettingContext bettingContext;
    Decision decision;
};

}
}

#endif
