#include "gtest/gtest.h"
#include "pokerGame/Hand.h"
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

    pokerGame::Hand h;
};

TEST_F(HandTest, newHandHasNoCard)
{
    ASSERT_EQ(0, h.getSize());
}

TEST_F(HandTest, addingCardToHandIncreasesItsSize)
{
    pokerGame::Card A_CARD(pokerGame::ACE, pokerGame::DIAMOND);
    h.addCard(A_CARD);
    ASSERT_EQ(1, h.getSize());
}

TEST_F(HandTest, newHandAsNoHandValue)
{
    pokerGame::HandValue handValue = h.getHandValue();
    ASSERT_EQ(pokerGame::NO_HAND_VALUE.type, handValue.type);
}

TEST_F(HandTest, handValueIsRightHighCardWhenNoHand)
{
    pokerGame::Card A_CARD(pokerGame::ACE, pokerGame::DIAMOND);
    pokerGame::HandValue highAceHand = {pokerGame::HIGH_CARD, {pokerGame::ACE, 0, 0, 0, 0}};
    h.addCard(A_CARD);

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(highAceHand.type, handValue.type);
    ASSERT_EQ(highAceHand.ranks[0], handValue.ranks[0]);
}

TEST_F(HandTest, handValueContainsFiveHighestCardsInDescendingOrderWhenHighHand)
{
    std::vector<pokerGame::Card> descendingOrderCards;
    
    descendingOrderCards.push_back(pokerGame::Card(pokerGame::ACE, pokerGame::DIAMOND));
    descendingOrderCards.push_back(pokerGame::Card(pokerGame::KING, pokerGame::DIAMOND));
    descendingOrderCards.push_back(pokerGame::Card(pokerGame::QUEEN, pokerGame::SPADE));
    descendingOrderCards.push_back(pokerGame::Card(8, pokerGame::SPADE));
    descendingOrderCards.push_back(pokerGame::Card(6, pokerGame::SPADE));
    
    pokerGame::Card secondLowestCard(5, pokerGame::HEART);
    pokerGame::Card lowestCard(3, pokerGame::HEART);

    h.addCard(lowestCard);
    for (int i = 0; i < pokerGame::HAND_SIZE; i++)
    {
        h.addCard(descendingOrderCards[i]);
    }
    h.addCard(secondLowestCard);

    pokerGame::HandValue handValue = h.getHandValue();

    for (int i = 0; i < pokerGame::HAND_SIZE; i++)
    {
        ASSERT_EQ(descendingOrderCards[i].getRank(), handValue.ranks[i]);
    }
}
TEST_F(HandTest, handValueIsPairWhenHandContainsPair)
{ 
    int PAIR_RANK = 6;
    h.addCard(pokerGame::Card(PAIR_RANK, pokerGame::SPADE));
    h.addCard(pokerGame::Card(PAIR_RANK, pokerGame::HEART));

    pokerGame::HandValue pairHandValue = {pokerGame::PAIR, {PAIR_RANK,0,0,0,0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(pairHandValue, handValue);
}

TEST_F(HandTest, handValueStoresThreeHighestCardsNotInPairWhenContainPair)
{
    int PAIR_RANK = 6;
    h.addCard(pokerGame::Card(PAIR_RANK, pokerGame::SPADE));
    h.addCard(pokerGame::Card(PAIR_RANK, pokerGame::HEART));
    h.addCard(pokerGame::Card(pokerGame::ACE, pokerGame::SPADE));
    h.addCard(pokerGame::Card(pokerGame::KING, pokerGame::SPADE));
    h.addCard(pokerGame::Card(9, pokerGame::HEART));
    h.addCard(pokerGame::Card(5, pokerGame::HEART));

    pokerGame::HandValue pairHandValue = {pokerGame::PAIR, {PAIR_RANK,pokerGame::ACE,pokerGame::KING,9,5}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(pairHandValue, handValue);
}

TEST_F(HandTest, handValueIsTwoPairsWhenHandContainsTwoPairs)
{
    int FIRST_PAIR_RANK = 6;
    int SECOND_PAIR_RANK = 4;
    h.addCard(pokerGame::Card(FIRST_PAIR_RANK, pokerGame::SPADE));
    h.addCard(pokerGame::Card(FIRST_PAIR_RANK, pokerGame::SPADE));
    h.addCard(pokerGame::Card(SECOND_PAIR_RANK, pokerGame::HEART));
    h.addCard(pokerGame::Card(SECOND_PAIR_RANK, pokerGame::HEART));

    pokerGame::HandValue pairHandValue = {pokerGame::TWO_PAIRS, {FIRST_PAIR_RANK,SECOND_PAIR_RANK,0,0,0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(pairHandValue, handValue);
}

TEST_F(HandTest, handValueStoresHighestCardNotInPairsWhenContainsTwoPairs)
{
    int FIRST_PAIR_RANK = 6;
    int SECOND_PAIR_RANK = 4;
    h.addCard(pokerGame::Card(FIRST_PAIR_RANK, pokerGame::SPADE));
    h.addCard(pokerGame::Card(FIRST_PAIR_RANK, pokerGame::HEART));
    h.addCard(pokerGame::Card(SECOND_PAIR_RANK, pokerGame::HEART));
    h.addCard(pokerGame::Card(SECOND_PAIR_RANK, pokerGame::SPADE));
    h.addCard(pokerGame::Card(5, pokerGame::HEART));
    h.addCard(pokerGame::Card(3, pokerGame::SPADE));

    pokerGame::HandValue pairHandValue = {pokerGame::TWO_PAIRS, {FIRST_PAIR_RANK,SECOND_PAIR_RANK,5,0,0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(pairHandValue, handValue);
}

TEST_F(HandTest, handValueIsThreeOfAKindWhenHandContainsThreeOfAKind)
{
    int A_RANK = 8;
    h.addCard(pokerGame::Card(A_RANK, pokerGame::SPADE));
    h.addCard(pokerGame::Card(A_RANK, pokerGame::HEART));
    h.addCard(pokerGame::Card(A_RANK, pokerGame::DIAMOND));

    pokerGame::HandValue threeOfAKindHandValue = {pokerGame::THREE_OF_A_KIND, {A_RANK, 0, 0, 0, 0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(threeOfAKindHandValue, handValue);
}

TEST_F(HandTest, handValueStoresTwoHighestCardsNotInToaKWhenContainsThreeOfAKind)
{
    int A_RANK = 8;
    int HIGHEST_RANK_NOT_IN_TOAK = pokerGame::KING;
    int SECOND_HIGHEST_RANK_NOT_IN_TOAK = 10;
    int THIRD_HIGHEST_RANK_NOT_IN_TOAK = 9;
    int RANK_LOWER_THAN_TOAK = 5;
    h.addCard(pokerGame::Card(A_RANK, pokerGame::SPADE));
    h.addCard(pokerGame::Card(A_RANK, pokerGame::HEART));
    h.addCard(pokerGame::Card(A_RANK, pokerGame::DIAMOND));
    h.addCard(pokerGame::Card(RANK_LOWER_THAN_TOAK, pokerGame::SPADE));
    h.addCard(pokerGame::Card(THIRD_HIGHEST_RANK_NOT_IN_TOAK, pokerGame::SPADE));
    h.addCard(pokerGame::Card(SECOND_HIGHEST_RANK_NOT_IN_TOAK, pokerGame::HEART));
    h.addCard(pokerGame::Card(HIGHEST_RANK_NOT_IN_TOAK, pokerGame::DIAMOND));

    pokerGame::HandValue threeOfAKindHandValue = {pokerGame::THREE_OF_A_KIND, {A_RANK, HIGHEST_RANK_NOT_IN_TOAK, SECOND_HIGHEST_RANK_NOT_IN_TOAK, 0, 0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(threeOfAKindHandValue, handValue);
}

TEST_F(HandTest, serieOf4CardsIsNotAStraight)
{
    h.addCard(pokerGame::Card(10, pokerGame::SPADE));
    h.addCard(pokerGame::Card(9, pokerGame::HEART));
    h.addCard(pokerGame::Card(8, pokerGame::DIAMOND));
    h.addCard(pokerGame::Card(7, pokerGame::SPADE));

    pokerGame::HandValue straightValue = {pokerGame::STRAIGHT, {10, 0, 0, 0, 0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_FALSE(straightValue == handValue);
}

TEST_F(HandTest, handValueIsStraightWhenHandContainsStraight)
{
    h.addCard(pokerGame::Card(10, pokerGame::SPADE));
    h.addCard(pokerGame::Card(9, pokerGame::HEART));
    h.addCard(pokerGame::Card(8, pokerGame::DIAMOND));
    h.addCard(pokerGame::Card(7, pokerGame::SPADE));
    h.addCard(pokerGame::Card(6, pokerGame::SPADE));

    pokerGame::HandValue straightValue = {pokerGame::STRAIGHT, {10, 0, 0, 0, 0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(straightValue, handValue);
}

TEST_F(HandTest, handValueDoesNotStoreHighCardsNotInStraightWhenContainStraight)
{
    h.addCard(pokerGame::Card(10, pokerGame::SPADE));
    h.addCard(pokerGame::Card(9, pokerGame::HEART));
    h.addCard(pokerGame::Card(8, pokerGame::DIAMOND));
    h.addCard(pokerGame::Card(7, pokerGame::SPADE));
    h.addCard(pokerGame::Card(6, pokerGame::SPADE));
    h.addCard(pokerGame::Card(pokerGame::ACE, pokerGame::SPADE));

    pokerGame::HandValue straightValue = {pokerGame::STRAIGHT, {10, 0, 0, 0, 0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(straightValue,handValue);
}

TEST_F(HandTest, handValueStoresHighestInStraight)
{
    h.addCard(pokerGame::Card(10, pokerGame::SPADE));
    h.addCard(pokerGame::Card(9, pokerGame::HEART));
    h.addCard(pokerGame::Card(8, pokerGame::DIAMOND));
    h.addCard(pokerGame::Card(7, pokerGame::SPADE));
    h.addCard(pokerGame::Card(6, pokerGame::SPADE));
    h.addCard(pokerGame::Card(pokerGame::JACK, pokerGame::SPADE));

    pokerGame::HandValue straightValue = {pokerGame::STRAIGHT, {10, 0, 0, 0, 0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_FALSE(straightValue == handValue);
}

TEST_F(HandTest, FourCardsOfSameSuitIsNotFlush)
{
    h.addCard(pokerGame::Card(10, pokerGame::SPADE));
    h.addCard(pokerGame::Card(9, pokerGame::SPADE));
    h.addCard(pokerGame::Card(8, pokerGame::SPADE));
    h.addCard(pokerGame::Card(7, pokerGame::SPADE));

    pokerGame::HandValue flushValue = {pokerGame::FLUSH, {10, 9, 8, 7, 0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_FALSE(flushValue == handValue);
}

TEST_F(HandTest, handValueIsFlushWhenHandContainsFlush)
{
    h.addCard(pokerGame::Card(10, pokerGame::SPADE));
    h.addCard(pokerGame::Card(9, pokerGame::SPADE));
    h.addCard(pokerGame::Card(8, pokerGame::SPADE));
    h.addCard(pokerGame::Card(7, pokerGame::SPADE));
    h.addCard(pokerGame::Card(4, pokerGame::SPADE));

    pokerGame::HandValue flushValue = {pokerGame::FLUSH, {10, 9, 8, 7, 4}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(flushValue, handValue);
}

TEST_F(HandTest, handValueDoesNotStoreHighCardsNotInFlushWhenContainFlush)
{
    h.addCard(pokerGame::Card(10, pokerGame::SPADE));
    h.addCard(pokerGame::Card(9, pokerGame::SPADE));
    h.addCard(pokerGame::Card(8, pokerGame::SPADE));
    h.addCard(pokerGame::Card(7, pokerGame::SPADE));
    h.addCard(pokerGame::Card(4, pokerGame::SPADE));
    h.addCard(pokerGame::Card(pokerGame::ACE, pokerGame::HEART));

    pokerGame::HandValue flushValue = {pokerGame::FLUSH, {10, 9, 8, 7, 4}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(flushValue, handValue);
}

TEST_F(HandTest, handValueFlushTakesHighestOfSameSuit)
{
    h.addCard(pokerGame::Card(10, pokerGame::SPADE));
    h.addCard(pokerGame::Card(9, pokerGame::SPADE));
    h.addCard(pokerGame::Card(8, pokerGame::SPADE));
    h.addCard(pokerGame::Card(7, pokerGame::SPADE));
    h.addCard(pokerGame::Card(4, pokerGame::SPADE));
    h.addCard(pokerGame::Card(pokerGame::ACE, pokerGame::SPADE));

    pokerGame::HandValue flushValue = {pokerGame::FLUSH, {pokerGame::ACE,10, 9, 8, 7}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(flushValue, handValue);
}

TEST_F(HandTest, handValueIsFullHouseWhenHandContainsFullHouse)
{
    h.addCard(pokerGame::Card(7, pokerGame::SPADE));
    h.addCard(pokerGame::Card(7, pokerGame::HEART));
    h.addCard(pokerGame::Card(2, pokerGame::DIAMOND));
    h.addCard(pokerGame::Card(2, pokerGame::CLUB));
    h.addCard(pokerGame::Card(2, pokerGame::HEART));

    pokerGame::HandValue fullHouseValue = {pokerGame::FULL_HOUSE, {2, 7, 0, 0, 0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(fullHouseValue, handValue);
}

TEST_F(HandTest, handValueIsFourOfAKindWhenHandContainsFourOfAKind)
{
    int A_RANK = 8;
    h.addCard(pokerGame::Card(A_RANK, pokerGame::SPADE));
    h.addCard(pokerGame::Card(A_RANK, pokerGame::HEART));
    h.addCard(pokerGame::Card(A_RANK, pokerGame::DIAMOND));
    h.addCard(pokerGame::Card(A_RANK, pokerGame::CLUB));

    pokerGame::HandValue fourOfAKindHandValue = {pokerGame::FOUR_OF_A_KIND, {A_RANK, 0, 0, 0, 0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(fourOfAKindHandValue, handValue);
}

TEST_F(HandTest, handValueStoresHighestCardsNotInFoaKWhenContainsFoutOfAKind)
{
    int A_RANK = 8;
    int HIGHEST_RANK_NOT_IN_TOAK = pokerGame::KING;
    int SECOND_HIGHEST_RANK_NOT_IN_TOAK = 10;
    int RANK_LOWER_THAN_TOAK = 5;
    h.addCard(pokerGame::Card(A_RANK, pokerGame::SPADE));
    h.addCard(pokerGame::Card(A_RANK, pokerGame::HEART));
    h.addCard(pokerGame::Card(A_RANK, pokerGame::DIAMOND));
    h.addCard(pokerGame::Card(A_RANK, pokerGame::CLUB));
    h.addCard(pokerGame::Card(RANK_LOWER_THAN_TOAK, pokerGame::SPADE));
    h.addCard(pokerGame::Card(SECOND_HIGHEST_RANK_NOT_IN_TOAK, pokerGame::HEART));
    h.addCard(pokerGame::Card(HIGHEST_RANK_NOT_IN_TOAK, pokerGame::DIAMOND));

    pokerGame::HandValue fourOfAKindHandValue = {pokerGame::FOUR_OF_A_KIND, {A_RANK, HIGHEST_RANK_NOT_IN_TOAK, 0, 0, 0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(fourOfAKindHandValue, handValue);
}

TEST_F(HandTest, handValueIsStraightFlushWhenContainsStraightFlush)
{
    h.addCard(pokerGame::Card(8, pokerGame::SPADE));
    h.addCard(pokerGame::Card(7, pokerGame::SPADE));
    h.addCard(pokerGame::Card(6, pokerGame::SPADE));
    h.addCard(pokerGame::Card(5, pokerGame::SPADE));
    h.addCard(pokerGame::Card(4, pokerGame::SPADE));

    pokerGame::HandValue straightFlush = {pokerGame::STRAIGHT_FLUSH, {8, 0, 0, 0, 0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_EQ(straightFlush, handValue);
}

TEST_F(HandTest, handValueIsNotStraightFlushIfContainsUnrelatedStraightAndFlush)
{
    h.addCard(pokerGame::Card(8, pokerGame::SPADE));
    h.addCard(pokerGame::Card(7, pokerGame::SPADE));
    h.addCard(pokerGame::Card(6, pokerGame::HEART));
    h.addCard(pokerGame::Card(5, pokerGame::HEART));
    h.addCard(pokerGame::Card(4, pokerGame::HEART));
    h.addCard(pokerGame::Card(pokerGame::JACK, pokerGame::HEART));
    h.addCard(pokerGame::Card(pokerGame::QUEEN, pokerGame::HEART));

    pokerGame::HandValue straightFlush = {pokerGame::STRAIGHT_FLUSH, {8, 0, 0, 0, 0}};

    pokerGame::HandValue handValue = h.getHandValue();

    ASSERT_FALSE(straightFlush.type ==  handValue.type);
}
