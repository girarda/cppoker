#ifndef BETTINGACTION_H
#define BETTINGACTION_H

#include "pokerGame/BettingContext.h"
#include "pokerGame/Decision.h"

namespace pokerGame {

class BettingAction
{
public:
    BettingAction(BettingContext currentContext, Decision decisionMade);

    bool hasSameBettingContext(BettingContext bettingContext) const;

private:
    BettingContext bettingContext;
    Decision decision;
};

}

#endif
