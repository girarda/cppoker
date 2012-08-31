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
    ASSERT_EQ(d.getSize(), pcore::DECK_SIZE_MAX);
}

TEST_F(DeckTest, Burn)
{
   
   for ( int i = 0; i < pcore::DECK_SIZE_MAX; ++i )
   {
       ASSERT_EQ(d.getSize(), pcore::DECK_SIZE_MAX-i);
       d.burn();
   } 

   ASSERT_DEATH(d.burn(), "");
}

TEST_F(DeckTest, drawCard)
{
    pcore::Card newCard(*d.drawCard());
    ASSERT_EQ(newCard.getSuit(), pcore::SPADE);
    ASSERT_EQ(newCard.getRank(), pcore::ACE);
    ASSERT_EQ(d.getSize(), pcore::DECK_SIZE_MAX-1);
}

TEST_F(DeckTest, shuffle)
    // No UT present for shuffle
    // For a shuffle test, see src/main.cpp
    // TODO : Add Shuffle UT
{
    ASSERT_TRUE(true);
}
