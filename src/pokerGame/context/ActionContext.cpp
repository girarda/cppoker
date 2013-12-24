#include "pokerGame/context/ActionContext.h"

namespace pokerGame {
namespace context {

ActionContext::ActionContext(BettingContext currentContext, Decision decisionMade) : bettingContext(currentContext), decision(decisionMade)
{
}

bool ActionContext::operator==(const ActionContext& other) const {
    return this->bettingContext == other.bettingContext && this->decision.choice == other.decision.choice;
}

}
}
