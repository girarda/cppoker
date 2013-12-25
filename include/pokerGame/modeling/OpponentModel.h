#ifndef OPPONENTMODEL_H
#define OPPONENTMODEL_H

#include "pokerGame/modeling/HandContext.h"
#include "pokerGame/modeling/ActionContext.h"
#include <vector>

namespace pokerGame {
namespace modeling {

class OpponentModel {
public:
    OpponentModel(modeling::ActionContext actionContext, std::vector<modeling::HandContext> handContexts);

    int getNumberOfOccurrences() const;
    double getHandStrengthAverage() const;
    double getHandStrengthDeviation() const;

    bool operator==(const OpponentModel& other) const;

private:
    int numberOfOccurrences;
    double handStrengthAverage;
    double handStrengthDeviation;
};

}
}

#endif
