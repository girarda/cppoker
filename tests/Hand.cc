#include "gtest/gtest.h"
#include "core/Hand.h"
#include <vector>

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

TEST_F(HandTest, newHandHasNoCard)
{
  ASSERT_EQ(0, h.getSize());
}

TEST_F(HandTest, addingCardToHandIncreasesItsSize)
{
    pcore::Card A_CARD(pcore::ACE, pcore::DIAMOND); 
    h.addCard(A_CARD);
    ASSERT_EQ(1, h.getSize());
}

TEST_F(HandTest, newHandAsNoHandValue)
{
    pcore::HandValue handValue = h.getHandValue();
    ASSERT_EQ(pcore::NO_HAND_VALUE.type, handValue.type);
}

TEST_F(HandTest, handValueIsRightHighCardWhenNoHand)
{
    pcore::Card A_CARD(pcore::ACE, pcore::DIAMOND);
    pcore::HandValue highAceHand = {pcore::HIGH_CARD, {pcore::ACE, 0, 0, 0, 0}};
    h.addCard(A_CARD);

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(highAceHand.type, handValue.type);
    ASSERT_EQ(highAceHand.ranks[0], handValue.ranks[0]);
}

TEST_F(HandTest, handValueContainsFiveHighestCardsInDescendingOrderWhenHighHand)
{
    std::vector<pcore::Card> descendingOrderCards;
    
    descendingOrderCards.push_back(pcore::Card(pcore::ACE, pcore::DIAMOND));
    descendingOrderCards.push_back(pcore::Card(pcore::KING, pcore::DIAMOND));
    descendingOrderCards.push_back(pcore::Card(pcore::QUEEN, pcore::SPADE));
    descendingOrderCards.push_back(pcore::Card(8, pcore::SPADE));
    descendingOrderCards.push_back(pcore::Card(6, pcore::SPADE));
    
    pcore::Card secondLowestCard(5, pcore::HEART);
    pcore::Card lowestCard(3, pcore::HEART);

    h.addCard(lowestCard);
    for (int i = 0; i < pcore::HAND_SIZE; i++)
    {
        h.addCard(descendingOrderCards[i]);
    }
    h.addCard(secondLowestCard);

    pcore::HandValue handValue = h.getHandValue();

    for (int i = 0; i < pcore::HAND_SIZE; i++)
    {
        ASSERT_EQ(descendingOrderCards[i].getRank(), handValue.ranks[i]);
    }
}
TEST_F(HandTest, handValueIsPairWhenHandContainsPair)
{ 
    int PAIR_RANK = 6;
    h.addCard(pcore::Card(PAIR_RANK, pcore::SPADE));
    h.addCard(pcore::Card(PAIR_RANK, pcore::HEART));

    pcore::HandValue pairHandValue = {pcore::PAIR, {PAIR_RANK,0,0,0,0}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(pairHandValue, handValue);
}

TEST_F(HandTest, handValueStoresThreeHighestCardsNotInPairWhenContainPair)
{
    int PAIR_RANK = 6;
    h.addCard(pcore::Card(PAIR_RANK, pcore::SPADE));
    h.addCard(pcore::Card(PAIR_RANK, pcore::HEART));
    h.addCard(pcore::Card(pcore::ACE, pcore::SPADE));
    h.addCard(pcore::Card(pcore::KING, pcore::SPADE));
    h.addCard(pcore::Card(9, pcore::HEART));
    h.addCard(pcore::Card(5, pcore::HEART));

    pcore::HandValue pairHandValue = {pcore::PAIR, {PAIR_RANK,pcore::ACE,pcore::KING,9,5}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(pairHandValue, handValue);
}

TEST_F(HandTest, handValueIsTwoPairsWhenHandContainsTwoPairs)
{
    int FIRST_PAIR_RANK = 6;
    int SECOND_PAIR_RANK = 4; 
    h.addCard(pcore::Card(FIRST_PAIR_RANK, pcore::SPADE));
    h.addCard(pcore::Card(FIRST_PAIR_RANK, pcore::SPADE));
    h.addCard(pcore::Card(SECOND_PAIR_RANK, pcore::HEART));
    h.addCard(pcore::Card(SECOND_PAIR_RANK, pcore::HEART));

    pcore::HandValue pairHandValue = {pcore::TWO_PAIRS, {FIRST_PAIR_RANK,SECOND_PAIR_RANK,0,0,0}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(pairHandValue, handValue);
}

TEST_F(HandTest, handValueStoresHighestCardNotInPairsWhenContainsTwoPairs)
{
    int FIRST_PAIR_RANK = 6;
    int SECOND_PAIR_RANK = 4; 
    h.addCard(pcore::Card(FIRST_PAIR_RANK, pcore::SPADE));
    h.addCard(pcore::Card(FIRST_PAIR_RANK, pcore::HEART));
    h.addCard(pcore::Card(SECOND_PAIR_RANK, pcore::HEART));
    h.addCard(pcore::Card(SECOND_PAIR_RANK, pcore::SPADE));
    h.addCard(pcore::Card(5, pcore::HEART));
    h.addCard(pcore::Card(3, pcore::SPADE));

    pcore::HandValue pairHandValue = {pcore::TWO_PAIRS, {FIRST_PAIR_RANK,SECOND_PAIR_RANK,5,0,0}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(pairHandValue, handValue);
}

TEST_F(HandTest, handValueIsThreeOfAKindWhenHandContainsThreeOfAKind)
{
    int A_RANK = 8;
    h.addCard(pcore::Card(A_RANK, pcore::SPADE));
    h.addCard(pcore::Card(A_RANK, pcore::HEART));
    h.addCard(pcore::Card(A_RANK, pcore::DIAMOND));

    pcore::HandValue threeOfAKindHandValue = {pcore::THREE_OF_A_KIND, {A_RANK, 0, 0, 0, 0}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(threeOfAKindHandValue, handValue);
}

TEST_F(HandTest, handValueStoresTwoHighestCardsNotInToaKWhenContainsThreeOfAKind)
{
    int A_RANK = 8;
    int HIGHEST_RANK_NOT_IN_TOAK = pcore::KING;
    int SECOND_HIGHEST_RANK_NOT_IN_TOAK = 10;
    int THIRD_HIGHEST_RANK_NOT_IN_TOAK = 9;
    int RANK_LOWER_THAN_TOAK = 5;
    h.addCard(pcore::Card(A_RANK, pcore::SPADE));
    h.addCard(pcore::Card(A_RANK, pcore::HEART));
    h.addCard(pcore::Card(A_RANK, pcore::DIAMOND));
    h.addCard(pcore::Card(RANK_LOWER_THAN_TOAK, pcore::SPADE));
    h.addCard(pcore::Card(THIRD_HIGHEST_RANK_NOT_IN_TOAK, pcore::SPADE));
    h.addCard(pcore::Card(SECOND_HIGHEST_RANK_NOT_IN_TOAK, pcore::HEART));
    h.addCard(pcore::Card(HIGHEST_RANK_NOT_IN_TOAK, pcore::DIAMOND));

    pcore::HandValue threeOfAKindHandValue = {pcore::THREE_OF_A_KIND, {A_RANK, HIGHEST_RANK_NOT_IN_TOAK, SECOND_HIGHEST_RANK_NOT_IN_TOAK, 0, 0}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(threeOfAKindHandValue, handValue);
    
}

TEST_F(HandTest, serieOf4CardsIsNotAStraight)
{
    h.addCard(pcore::Card(10, pcore::SPADE));
    h.addCard(pcore::Card(9, pcore::HEART));
    h.addCard(pcore::Card(8, pcore::DIAMOND));
    h.addCard(pcore::Card(7, pcore::SPADE));

    pcore::HandValue straightValue = {pcore::STRAIGHT, {10, 0, 0, 0, 0}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_FALSE(straightValue == handValue);
}

TEST_F(HandTest, handValueIsStraightWhenHandContainsStraight)
{
    h.addCard(pcore::Card(10, pcore::SPADE));
    h.addCard(pcore::Card(9, pcore::HEART));
    h.addCard(pcore::Card(8, pcore::DIAMOND));
    h.addCard(pcore::Card(7, pcore::SPADE));
    h.addCard(pcore::Card(6, pcore::SPADE));

    pcore::HandValue straightValue = {pcore::STRAIGHT, {10, 0, 0, 0, 0}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(straightValue, handValue);
}

TEST_F(HandTest, handValueDoesNotStoreHighCardsNotInStraightWhenContainStraight)
{
    h.addCard(pcore::Card(10, pcore::SPADE));
    h.addCard(pcore::Card(9, pcore::HEART));
    h.addCard(pcore::Card(8, pcore::DIAMOND));
    h.addCard(pcore::Card(7, pcore::SPADE));
    h.addCard(pcore::Card(6, pcore::SPADE));
    h.addCard(pcore::Card(pcore::ACE, pcore::SPADE));

    pcore::HandValue straightValue = {pcore::STRAIGHT, {10, 0, 0, 0, 0}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(straightValue,handValue);
}

TEST_F(HandTest, handValueStoresHighestInStraight)
{
    h.addCard(pcore::Card(10, pcore::SPADE));
    h.addCard(pcore::Card(9, pcore::HEART));
    h.addCard(pcore::Card(8, pcore::DIAMOND));
    h.addCard(pcore::Card(7, pcore::SPADE));
    h.addCard(pcore::Card(6, pcore::SPADE));
    h.addCard(pcore::Card(pcore::JACK, pcore::SPADE));

    pcore::HandValue straightValue = {pcore::STRAIGHT, {10, 0, 0, 0, 0}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_FALSE(straightValue == handValue);
}

TEST_F(HandTest, FourCardsOfSameSuitIsNotFlush)
{
    h.addCard(pcore::Card(10, pcore::SPADE));
    h.addCard(pcore::Card(9, pcore::SPADE));
    h.addCard(pcore::Card(8, pcore::SPADE));
    h.addCard(pcore::Card(7, pcore::SPADE));

    pcore::HandValue flushValue = {pcore::FLUSH, {10, 9, 8, 7, 0}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_FALSE(flushValue == handValue);
}

TEST_F(HandTest, handValueIsFlushWhenHandContainsFlush)
{
    h.addCard(pcore::Card(10, pcore::SPADE));
    h.addCard(pcore::Card(9, pcore::SPADE));
    h.addCard(pcore::Card(8, pcore::SPADE));
    h.addCard(pcore::Card(7, pcore::SPADE));
    h.addCard(pcore::Card(4, pcore::SPADE));

    pcore::HandValue flushValue = {pcore::FLUSH, {10, 9, 8, 7, 4}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(flushValue, handValue);
}

TEST_F(HandTest, handValueDoesNotStoreHighCardsNotInFlushWhenContainFlush)
{
    h.addCard(pcore::Card(10, pcore::SPADE));
    h.addCard(pcore::Card(9, pcore::SPADE));
    h.addCard(pcore::Card(8, pcore::SPADE));
    h.addCard(pcore::Card(7, pcore::SPADE));
    h.addCard(pcore::Card(4, pcore::SPADE));
    h.addCard(pcore::Card(pcore::ACE, pcore::HEART));

    pcore::HandValue flushValue = {pcore::FLUSH, {10, 9, 8, 7, 4}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(flushValue, handValue);
}

TEST_F(HandTest, handValueFlushTakesHighestOfSameSuit)
{
    h.addCard(pcore::Card(10, pcore::SPADE));
    h.addCard(pcore::Card(9, pcore::SPADE));
    h.addCard(pcore::Card(8, pcore::SPADE));
    h.addCard(pcore::Card(7, pcore::SPADE));
    h.addCard(pcore::Card(4, pcore::SPADE));
    h.addCard(pcore::Card(pcore::ACE, pcore::SPADE));

    pcore::HandValue flushValue = {pcore::FLUSH, {pcore::ACE,10, 9, 8, 7}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(flushValue, handValue);
}

TEST_F(HandTest, handValueIsFullHouseWhenHandContainsFullHouse)
{
    h.addCard(pcore::Card(7, pcore::SPADE));
    h.addCard(pcore::Card(7, pcore::HEART));
    h.addCard(pcore::Card(7, pcore::DIAMOND));
    h.addCard(pcore::Card(7, pcore::CLUB));

    pcore::HandValue fullHouseValue = {pcore::FULL_HOUSE, {7, 0, 0, 0, 0}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(fullHouseValue, handValue);
}

TEST_F(HandTest, handValueStoresHighestCardNotInFullHouseWhenContainsFullHouse)
{
    h.addCard(pcore::Card(7, pcore::SPADE));
    h.addCard(pcore::Card(7, pcore::HEART));
    h.addCard(pcore::Card(7, pcore::DIAMOND));
    h.addCard(pcore::Card(7, pcore::CLUB));
    h.addCard(pcore::Card(4, pcore::SPADE));

    pcore::HandValue fullHouseValue = {pcore::FULL_HOUSE, {7, 4, 0, 0, 0}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(fullHouseValue, handValue);
}

TEST_F(HandTest, handValueIsStraightFlushWhenContainsStraightFlush)
{
    h.addCard(pcore::Card(8, pcore::SPADE));
    h.addCard(pcore::Card(7, pcore::SPADE));
    h.addCard(pcore::Card(6, pcore::SPADE));
    h.addCard(pcore::Card(5, pcore::SPADE));
    h.addCard(pcore::Card(4, pcore::SPADE));

    pcore::HandValue straightFlush = {pcore::STRAIGHT_FLUSH, {8, 0, 0, 0, 0}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_EQ(straightFlush, handValue);
}

TEST_F(HandTest, handValueIsNotStraightFlushIfContainsUnrelatedStraightAndFlush)
{
    h.addCard(pcore::Card(8, pcore::SPADE));
    h.addCard(pcore::Card(7, pcore::SPADE));
    h.addCard(pcore::Card(6, pcore::HEART));
    h.addCard(pcore::Card(5, pcore::HEART));
    h.addCard(pcore::Card(4, pcore::HEART));
    h.addCard(pcore::Card(pcore::JACK, pcore::HEART));
    h.addCard(pcore::Card(pcore::QUEEN, pcore::HEART));

    pcore::HandValue straightFlush = {pcore::STRAIGHT_FLUSH, {8, 0, 0, 0, 0}};

    pcore::HandValue handValue = h.getHandValue();

    ASSERT_FALSE(straightFlush.type ==  handValue.type);
}
