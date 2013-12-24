#include "pokerGame/BettingAction.h"

namespace pokerGame {

BettingAction::BettingAction(BettingContext currentContext, Decision decisionMade) : bettingContext(currentContext), decision(decisionMade)
{
}

bool BettingAction::operator==(const BettingAction& other) const {
    return this->bettingContext == other.bettingContext && this->decision.choice == other.decision.choice;
}


}
