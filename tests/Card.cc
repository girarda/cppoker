#include "gtest/gtest.h"
#include "src/core/Card.h"

TEST(Card, ConstructorRankTooLowError)
{
   ASSERT_DEATH(pcore::Card(1,pcore::SPADE), ""); 
}

TEST(Card, ConstructorRankTooHighError)
{
   ASSERT_DEATH(pcore::Card(15,pcore::SPADE), ""); 
}

TEST(Card, ConstructorSuitTooLowError)
{
   ASSERT_DEATH(pcore::Card(pcore::ACE,-1), ""); 
}

TEST(Card, ConstructorSuitTooHighError)
{
   ASSERT_DEATH(pcore::Card(pcore::ACE,-1), ""); 
}

TEST(Card, ConstructorLowestValues)
{
    pcore::Card lowCard(2, pcore::DIAMOND);
    ASSERT_EQ(lowCard.getRank(), 2);
    ASSERT_EQ(lowCard.getSuit(), pcore::DIAMOND);
}

TEST(Card, ConstructorHighestValues)
{
    pcore::Card highCard(pcore::ACE, pcore::SPADE);
    ASSERT_EQ(highCard.getRank(), pcore::ACE);
    ASSERT_EQ(highCard.getSuit(), pcore::SPADE);
}
