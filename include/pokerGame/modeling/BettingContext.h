#ifndef BETTINGCONTEXT_H
#define BETTINGCONTEXT_H

#include "pokerGame/BettingRoundType.h"

namespace pokerGame {
namespace modeling {

class BettingContext {
public:
    BettingContext(const BettingRoundType &curentBettingRoundType, int nbOfRaises, int nbOfPlayers, float currentMinBet, float currentBigBlind);

    bool hasManyRaises() const;
    bool hasManyPlayers() const;

    int getNumberOfRaises() const;
    int getNumberOfPlayers() const;
    BettingRoundType getBettingRoundType() const;

    float getCurrentPot() const;
    float getMinBet() const;
    float getBigBlind() const;

    bool operator==(const BettingContext& other) const;

private:
    BettingRoundType bettingRoundType;
    int numberOfRaises;
    int numberOfPlayers;
    float minBet;
    float bigBlind;

    static const int MANY_THRESHOLD;
};

}
}

#endif
