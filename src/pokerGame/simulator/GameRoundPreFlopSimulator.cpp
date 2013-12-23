#include "include/pokerGame/simulator/GameRoundPreFlopSimulator.h"

namespace pokerGame {
namespace simulator {

GameRoundPreFlopSimulator::GameRoundPreFlopSimulator(Deck *deckToUse, BettingRound* bettingRoundToUse, HoleCardsEquivalence* equivalence) : GameRound(deckToUse, bettingRoundToUse), holeCardsEquivalence(equivalence)
{
}

void GameRoundPreFlopSimulator::distributeHoles() {
    Player* player1 = gameContext->getPlayers()[0];
    gameContext->removePlayer(0);

    std::vector<Card> holeCards = holeCardsEquivalence->equivalenceToCards();
    for (Card c: holeCards) {
        player1->addCardToHole(c);
        deck->removeCard(c);
    }
    distributeOneCard();
    distributeOneCard();
    gameContext->addPlayer(player1);
}

}
}
