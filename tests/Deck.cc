#include "gtest/gtest.h"
#include "src/core/Deck.h"

class DeckTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
        }
        virtual void TearDown()
        {
        }
        
        pcore::Deck d;
};

TEST_F(DeckTest, Constructor)
{
    ASSERT_EQ(d.getCount(), pcore::DECK_SIZE);
}

TEST_F(DeckTest, Burn)
{
    pcore::Card exCard(pcore::ACE, pcore::CLUB);
    d.burn();
    ASSERT_EQ(d.getCount(), pcore::DECK_SIZE-1);
    pcore::Card aCard(d.draw());
    ASSERT_EQ(aCard.getRank(), exCard.getRank());
    ASSERT_EQ(aCard.getSuit(), exCard.getSuit());
}

TEST_F(DeckTest, BurnAssert)
{
    for( int i(0) ; i < pcore::DECK_SIZE ; i++ )
    {
        d.burn();
    }

    ASSERT_DEATH(d.draw(), "");
}
    
TEST_F(DeckTest, drawCard)
{
    pcore::Card newCard(d.draw());
    ASSERT_EQ(newCard.getSuit(), pcore::SPADE);
    ASSERT_EQ(newCard.getRank(), pcore::ACE);
    ASSERT_EQ(d.getCount(), 51);

    pcore::Card secondCard(d.draw());
    ASSERT_EQ(secondCard.getSuit(), pcore::CLUB);
    ASSERT_EQ(secondCard.getRank(), pcore::ACE);
    ASSERT_EQ(d.getCount(), 50);
}

TEST_F(DeckTest, shuffle)
    // No UT present for shuffle
    // For a shuffle test, see src/main.cpp
    // TODO : Add Shuffle UT
{
    ASSERT_TRUE(true);
}
