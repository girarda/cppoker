#ifndef OPPONENTMODEL_H
#define OPPONENTMODEL_H

#include "HandContext.h"
#include "BettingContext.h"
#include <vector>

namespace pokerGame {

class OpponentModel {
public:
    OpponentModel(BettingContext currentContext, std::vector<HandContext> handContexts);

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
