#include "gtest/gtest.h"
#include "pokerGame/card/Deck.h"

class DeckTest : public ::testing::Test {
protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }

    pokerGame::card::Deck d;
};

TEST_F(DeckTest, burnRemovesOneCardFromTheDeck) {
    d.burn();
    ASSERT_EQ(d.getCount(), pokerGame::card::DECK_SIZE-1);
}

TEST_F(DeckTest, drawCard) {
    pokerGame::card::Card newCard(d.draw());
    ASSERT_EQ(newCard.getSuit(), pokerGame::card::SPADE);
    ASSERT_EQ(newCard.getRank(), pokerGame::card::ACE);

    pokerGame::card::Card secondCard(d.draw());
    ASSERT_EQ(secondCard.getSuit(), pokerGame::card::CLUB);
    ASSERT_EQ(secondCard.getRank(), pokerGame::card::ACE);
}

TEST_F(DeckTest, drawingACardRemovesTheCardFromTheDeck) {
    d.draw();
    ASSERT_EQ(d.getCount(), 51);
}

TEST_F(DeckTest, removeCardRemovesOneCardFromTheDeck) {
    pokerGame::card::Card card(2, pokerGame::card::CLUB);
    d.removeCard(card);
    ASSERT_EQ(d.getCount(), 51);
}

TEST_F(DeckTest, aRemovedCardIsNotPresentInTheDeck) {
    pokerGame::card::Card card(2, pokerGame::card::CLUB);
    d.removeCard(card);
    while (d.getCount() > 0) {
        pokerGame::card::Card c = d.draw();
        ASSERT_FALSE(c == card && card.isSameSuit(c));
    }
}
