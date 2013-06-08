#include "gtest/gtest.h"
#include "core/Card.h"

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

TEST(Card, ToStringTwoOfDiamond)
{
    std::string cardString("2D");
    pcore::Card card(2, pcore::DIAMOND);
    ASSERT_EQ(card.toString(), cardString);
}

TEST(Card, ToStringTenOfHeart)
{
    std::string cardString("10H");
    pcore::Card card(10, pcore::HEART);
    ASSERT_EQ(card.toString(), cardString);
}


TEST(Card, ToStringJackOfClub)
{
    std::string cardString("JC");
    pcore::Card card(pcore::JACK, pcore::CLUB);
    ASSERT_EQ(card.toString(), cardString);
}

TEST(Card, ToStringQueenOfSpade)
{
    std::string cardString("QS");
    pcore::Card card(pcore::QUEEN, pcore::SPADE);
    ASSERT_EQ(card.toString(), cardString);
}

TEST(Card, ToStringKingOfSpade)
{
    std::string cardString("KS");
    pcore::Card card(pcore::KING, pcore::SPADE);
    ASSERT_EQ(card.toString(), cardString);
}

TEST(Card, ToStringAceOfSpade)
{
    std::string cardString("AS");
    pcore::Card card(pcore::ACE, pcore::SPADE);
    ASSERT_EQ(card.toString(), cardString);
}
