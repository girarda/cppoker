#ifndef BETTINGACTION_H
#define BETTINGACTION_H

#include "pokerGame/modeling/BettingContext.h"
#include "pokerGame/Decision.h"

namespace pokerGame {
namespace modeling {

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
