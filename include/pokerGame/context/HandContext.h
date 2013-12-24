#ifndef HANDCONTEXT_H
#define HANDCONTEXT_H

#include "pokerGame/context/ActionContext.h"

namespace pokerGame {
namespace context {

class HandContext
{
public:
    HandContext(const ActionContext &actionCtx, double handEvaluatedStrength);

    double getHandStrength() const;

    bool hasSameActionContext(const ActionContext &actionContext) const;

private:
    ActionContext actionContext;
    double handStrength;
};

}
}

#endif
