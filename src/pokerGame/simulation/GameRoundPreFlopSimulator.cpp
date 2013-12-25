#include "include/pokerGame/simulation/GameRoundPreFlopSimulator.h"

namespace pokerGame {
namespace simulation {

GameRoundPreFlopSimulator::GameRoundPreFlopSimulator(card::Deck *deckToUse, BettingRound* bettingRoundToUse, HoleCardsEquivalence* equivalence) : GameRound(deckToUse, bettingRoundToUse), holeCardsEquivalence(equivalence)
{
}

void GameRoundPreFlopSimulator::distributeHoles() {
    Player* player1 = gameContext->getPlayers()[0];
    gameContext->removePlayer(0);

    std::vector<card::Card> holeCards = holeCardsEquivalence->equivalenceToCards();
    for (card::Card c: holeCards) {
        player1->addCardToHole(c);
        deck->removeCard(c);
    }
    distributeOneCard();
    distributeOneCard();
    gameContext->addPlayer(player1);
}

}
}
