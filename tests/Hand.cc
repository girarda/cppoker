#include "gtest/gtest.h"
#include "src/core/Hand.h"

class HandTest : public ::testing::Test
{
    protected:
        virtual void SetUp()
        {
        }
        virtual void TearDown()
        {
        }
        
        pcore::Hand h;
};

TEST_F(HandTest, Constructor)
{
    ASSERT_EQ(h.getValue().type, pcore::NO_HAND);
    ASSERT_EQ(h.getCount(), 0);
    for( int i(0) ; i < pcore::HAND_SIZE ; i++ )
    {
        ASSERT_EQ(h.getValue().ranks[i], 0);
    }
}

TEST_F(HandTest, AddOneCardNoHand)
{
    pcore::Card c1(2, pcore::SPADE);
    h.addCard(c1);
    ASSERT_EQ(h.getCount(), 1);
   
    ASSERT_EQ(h.getValue().type, pcore::NO_HAND);
    ASSERT_EQ(h.getValue().ranks[0], 2);
    ASSERT_EQ(h.getValue().ranks[1], 0);
}

TEST_F(HandTest, AddMultipleCardsNoHand)
{
    pcore::Card c1(2, pcore::SPADE);
    pcore::Card c2(pcore::ACE, pcore::SPADE);

    h.addCard(c1);
    h.addCard(c2);

    ASSERT_EQ(h.getCount(), 2);

    ASSERT_EQ(h.getValue().type, pcore::NO_HAND);
    ASSERT_EQ(h.getValue().ranks[0], pcore::ACE);
    ASSERT_EQ(h.getValue().ranks[1], 2);
}

TEST_F(HandTest, AddTooManyCards)
{
    pcore::Card c1(2, pcore::SPADE);
    pcore::Card c2(pcore::ACE, pcore::SPADE);
    pcore::Card c3(4, pcore::DIAMOND);
    pcore::Card c4(7, pcore::DIAMOND);
    pcore::Card c5(8, pcore::CLUB);
    pcore::Card c6(10, pcore::HEART);
    pcore::Card c7(pcore::JACK, pcore::HEART);
    pcore::Card c8(pcore::KING, pcore::CLUB);
    h.addCard(c1);
    h.addCard(c2);
    h.addCard(c3);
    h.addCard(c4);
    h.addCard(c5);
    h.addCard(c6);
    h.addCard(c7);
    ASSERT_DEATH(h.addCard(c8), "");
}

TEST_F(HandTest, Pair)
{
    pcore::Card c1(5, pcore::SPADE);
    pcore::Card c2(5, pcore::HEART);
    h.addCard(c1);
    h.addCard(c2);
    ASSERT_EQ(h.getValue().type, pcore::PAIR);
    ASSERT_EQ(h.getValue().ranks[0], 5);

    pcore::Card c3(3, pcore::SPADE);
    pcore::Card c4(pcore::ACE, pcore::DIAMOND);
    h.addCard(c3);
    h.addCard(c4);
    ASSERT_EQ(h.getValue().type, pcore::PAIR);
    ASSERT_EQ(h.getValue().ranks[0], 5);
    ASSERT_EQ(h.getValue().ranks[1], pcore::ACE);
    ASSERT_EQ(h.getValue().ranks[2], 3);
}
