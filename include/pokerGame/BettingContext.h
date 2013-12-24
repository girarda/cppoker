#ifndef BETTINGCONTEXT_H
#define BETTINGCONTEXT_H

#include "BettingRoundType.h"

namespace pokerGame {

enum Quantity {FEW, MANY};

class BettingContext {
public:
    BettingContext(BettingRoundType curentBettingRoundType, int nbOfRaises, int nbOfPlayers);

    int getNumberOfRaises() const;
    int getNumberOfPlayers() const;

    bool operator==(const BettingContext& other) const;

private:
    BettingRoundType bettingRoundType;
    int numberOfRaises;
    int numberOfPlayers;
};

}

#endif
