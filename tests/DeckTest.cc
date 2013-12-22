#include "gtest/gtest.h"
#include "pokerGame/Deck.h"

class DeckTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }

    pokerGame::Deck d;
};

TEST_F(DeckTest, burnRemovesOneCardFromTheDeck) {
    d.burn();
    ASSERT_EQ(d.getCount(), pokerGame::DECK_SIZE-1);
}

TEST_F(DeckTest, drawCard) {
    pokerGame::Card newCard(d.draw());
    ASSERT_EQ(newCard.getSuit(), pokerGame::SPADE);
    ASSERT_EQ(newCard.getRank(), pokerGame::ACE);

    pokerGame::Card secondCard(d.draw());
    ASSERT_EQ(secondCard.getSuit(), pokerGame::CLUB);
    ASSERT_EQ(secondCard.getRank(), pokerGame::ACE);
}

TEST_F(DeckTest, drawingACardRemovesTheCardFromTheDeck) {
    d.draw();
    ASSERT_EQ(d.getCount(), 51);
}

TEST_F(DeckTest, shuffle) {
    // No UT present for shuffle
    // For a shuffle test, see src/main.cpp
    // TODO : Add Shuffle UT
    ASSERT_TRUE(true);
}
