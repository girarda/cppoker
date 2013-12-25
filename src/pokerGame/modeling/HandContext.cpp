#include "include/pokerGame/modeling/HandContext.h"

namespace pokerGame {
namespace modeling {

HandContext::HandContext(const ActionContext &actionCtx, double handEvaluatedStrength) : actionContext(actionCtx), handStrength(handEvaluatedStrength) {
}

double HandContext::getHandStrength() const {
    return handStrength;
}

bool HandContext::hasSameActionContext(const ActionContext &actionContext) const {
    return this->actionContext == actionContext;
}

}
}
