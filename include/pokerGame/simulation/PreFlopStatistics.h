#ifndef SIMULATORPREFLOPSTATISTICS_H
#define SIMULATORPREFLOPSTATISTICS_H

#include "pokerGame/simulation/HoleCardsEquivalence.h"

namespace pokerGame {
namespace simulation {

class PreFlopStatistics
{
public:
    PreFlopStatistics();

    virtual double getWinningProbability(HoleCardsEquivalence* holeCardsEquivalence, int numberOfPlayers);
    virtual void addWinningProbability(HoleCardsEquivalence* holeCardsEquivalence, int numberOfPlayers, double p);

    virtual void load(std::string file);
    virtual void save(std::string file);

private:
    std::map<std::pair<HoleCardsEquivalence*, int>, double> percentageOfWinning;
};

}
}

#endif
