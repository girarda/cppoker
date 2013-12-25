#include "gtest/gtest.h"
#include "pokerGame/simulation/HoleCardsEquivalence.h"
#include "pokerGame/card/Card.h"

class HoleCardsEquivalenceTest : public ::testing::Test {
protected:
    pokerGame::simulation::HoleCardsEquivalence* holeCardsEquivalence;

    static const int SAME_CARD_RANK;
    static const int DIFFERENT_CARD_RANK_1;
    static const int DIFFERENT_CARD_RANK_2;

    virtual void SetUp() {

    }
    virtual void TearDown() {
        if (holeCardsEquivalence) {
            delete holeCardsEquivalence;
        }
    }
};

const int HoleCardsEquivalenceTest::SAME_CARD_RANK(3);
const int HoleCardsEquivalenceTest::DIFFERENT_CARD_RANK_1(4);
const int HoleCardsEquivalenceTest::DIFFERENT_CARD_RANK_2(5);

TEST_F(HoleCardsEquivalenceTest, ifCardsHaveSameValueThenEquivalenceCardsHaveSameRankButDifferentSuits) {
    holeCardsEquivalence = new pokerGame::simulation::HoleCardsEquivalence(SAME_CARD_RANK, SAME_CARD_RANK);
    std::vector<pokerGame::card::Card> equivalenceCards = holeCardsEquivalence->equivalenceToCards();
    bool ranksAreEqual = (equivalenceCards[0].getRank() == equivalenceCards[1].getRank()) && (equivalenceCards[0].getRank() == SAME_CARD_RANK);
    bool suitsAreEqual = equivalenceCards[0].getSuit() == equivalenceCards[1].getSuit();
    ASSERT_TRUE(ranksAreEqual);
    ASSERT_FALSE(suitsAreEqual);
}

TEST_F(HoleCardsEquivalenceTest, ifCardsHaveDifferentValuesThenEquivalenceCardsHaveDifferentValuesButSameSuit) {
    holeCardsEquivalence = new pokerGame::simulation::HoleCardsEquivalence(DIFFERENT_CARD_RANK_1, DIFFERENT_CARD_RANK_2);
    std::vector<pokerGame::card::Card> equivalenceCards = holeCardsEquivalence->equivalenceToCards();
    bool ranksAreEqual = equivalenceCards[0].getRank() == equivalenceCards[1].getRank();
    bool suitsAreEqual = equivalenceCards[0].getSuit() == equivalenceCards[1].getSuit();
    ASSERT_FALSE(ranksAreEqual);
    ASSERT_TRUE(suitsAreEqual);
}
