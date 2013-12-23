#include <fstream>
#include <boost/serialization/map.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/serialization.hpp>
#include "pokerGame/simulator/PreFlopStatistics.h"

namespace pokerGame {
namespace simulator {

PreFlopStatistics::PreFlopStatistics() : percentageOfWinning()
{
}

double PreFlopStatistics::getWinningProbability(HoleCardsEquivalence* holeCardsEquivalence, int numberOfPlayers) {
    return percentageOfWinning[std::pair<HoleCardsEquivalence*, int>(holeCardsEquivalence, numberOfPlayers)];
}

void PreFlopStatistics::addWinningProbability(HoleCardsEquivalence* holeCardsEquivalence, int numberOfPlayers, double p) {
    percentageOfWinning[std::pair<HoleCardsEquivalence*, int>(holeCardsEquivalence, numberOfPlayers)] = p;
}

void PreFlopStatistics::save(std::string file) {
    std::ofstream ofs(file);
    boost::archive::text_oarchive oarch(ofs);
    oarch << percentageOfWinning;
}

void PreFlopStatistics::load(std::string file) {
    std::ifstream ifs(file);
    boost::archive::text_iarchive iarch(ifs);
    iarch >> percentageOfWinning;
}

}
}
