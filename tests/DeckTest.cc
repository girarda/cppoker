#include "gtest/gtest.h"
#include "pokerGame/Deck.h"

class DeckTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
    }
    virtual void TearDown()
    {
    }

    pokerGame::Deck d;
};

TEST_F(DeckTest, Constructor)
{
    ASSERT_EQ(d.getCount(), pokerGame::DECK_SIZE);
}

TEST_F(DeckTest, Burn)
{
    pokerGame::Card exCard(pokerGame::ACE, pokerGame::CLUB);
    d.burn();
    ASSERT_EQ(d.getCount(), pokerGame::DECK_SIZE-1);
    pokerGame::Card aCard(d.draw());
    ASSERT_EQ(aCard.getRank(), exCard.getRank());
    ASSERT_EQ(aCard.getSuit(), exCard.getSuit());
}

TEST_F(DeckTest, BurnAssert)
{
    for( int i(0) ; i < pokerGame::DECK_SIZE ; i++ )
    {
        d.burn();
    }

    ASSERT_DEATH(d.draw(), "");
}

TEST_F(DeckTest, drawCard)
{
    pokerGame::Card newCard(d.draw());
    ASSERT_EQ(newCard.getSuit(), pokerGame::SPADE);
    ASSERT_EQ(newCard.getRank(), pokerGame::ACE);
    ASSERT_EQ(d.getCount(), 51);

    pokerGame::Card secondCard(d.draw());
    ASSERT_EQ(secondCard.getSuit(), pokerGame::CLUB);
    ASSERT_EQ(secondCard.getRank(), pokerGame::ACE);
    ASSERT_EQ(d.getCount(), 50);
}

TEST_F(DeckTest, shuffle)
// No UT present for shuffle
// For a shuffle test, see src/main.cpp
// TODO : Add Shuffle UT
{
    ASSERT_TRUE(true);
}
