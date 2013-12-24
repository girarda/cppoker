#ifndef HANDCONTEXT_H
#define HANDCONTEXT_H

#include "pokerGame/BettingAction.h"

namespace pokerGame {

class HandContext
{
public:
    HandContext(BettingAction bettingAct, double handEvaluatedStrength);

    double getHandStrength() const;

    bool hasSameBettingContext(BettingContext bettingContext) const;

private:
    BettingAction bettingAction;
    double handStrength;
};

}

#endif
