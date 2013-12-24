#ifndef HANDCONTEXT_H
#define HANDCONTEXT_H

#include "pokerGame/context/ActionContext.h"

namespace pokerGame {
namespace context {

class HandContext
{
public:
    HandContext(ActionContext actionCtx, double handEvaluatedStrength);

    double getHandStrength() const;

    bool hasSameBettingAction(ActionContext actionContext) const;

private:
    ActionContext actionContext;
    double handStrength;
};

}
}

#endif
