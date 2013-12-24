#ifndef BETTINGCONTEXT_H
#define BETTINGCONTEXT_H

#include "BettingRoundType.h"

namespace pokerGame {

enum Quantity {FEW, MANY};

class BettingContext {
public:
    BettingContext(BettingRoundType curentBettingRoundType, int nbOfRaises, int nbOfPlayers);

    Quantity getNumberOfRaises() const;
    Quantity getNumberOfPlayers() const;

    bool operator==(const BettingContext& other) const;

private:
    BettingRoundType bettingRoundType;
    Quantity numberOfRaises;
    Quantity numberOfPlayers;

    Quantity valueFor(int number);
};

}

#endif
