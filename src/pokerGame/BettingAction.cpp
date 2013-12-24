#include "pokerGame/BettingAction.h"

namespace pokerGame {

BettingAction::BettingAction(BettingContext currentContext, Decision decisionMade) : bettingContext(currentContext), decision(decisionMade)
{
}

bool BettingAction::hasSameBettingContext(BettingContext bettingContext) const {
    return this->bettingContext ==bettingContext;
}

}
