#ifndef OPPONENTMODEL_H
#define OPPONENTMODEL_H

#include "pokerGame/context/HandContext.h"
#include "pokerGame/context/ActionContext.h"
#include <vector>

namespace pokerGame {

class OpponentModel {
public:
    OpponentModel(context::ActionContext actionContext, std::vector<context::HandContext> handContexts);

    int getNumberOfOccurrences() const;
    double getHandStrengthAverage() const;
    double getHandStrengthDeviation() const;

private:
    int numberOfOccurrences;
    double handStrengthAverage;
    double handStrengthDeviation;
};

}

#endif
