#include "include/pokerGame/context/HandContext.h"

namespace pokerGame {
namespace context {

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
