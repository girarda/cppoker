#include "pokerGame/modeling/ActionContext.h"

namespace pokerGame {
namespace modeling {

ActionContext::ActionContext(const BettingContext &currentContext, const Decision &decisionMade) : bettingContext(currentContext), decision(decisionMade)
{
}

bool ActionContext::operator==(const ActionContext& other) const {
    return this->bettingContext == other.bettingContext && this->decision.choice == other.decision.choice;
}

}
}
