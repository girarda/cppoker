#ifndef BETTINGACTION_H
#define BETTINGACTION_H

#include "pokerGame/BettingContext.h"
#include "pokerGame/Decision.h"

namespace pokerGame {

class BettingAction
{
public:
    BettingAction(BettingContext currentContext, Decision decisionMade);

    bool operator==(const BettingAction& other) const;

private:
    BettingContext bettingContext;
    Decision decision;
};

}

#endif
