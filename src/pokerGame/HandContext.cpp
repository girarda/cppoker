#include "include/pokerGame/HandContext.h"

namespace pokerGame {

HandContext::HandContext(BettingAction bettingAct, double handEvaluatedStrength) : bettingAction(bettingAct), handStrength(handEvaluatedStrength) {
}

double HandContext::getHandStrength() const {
    return handStrength;
}

bool HandContext::hasSameBettingContext(BettingContext bettingContext) const {
    return this->bettingAction.hasSameBettingContext(bettingContext);
}

}
