#include "gtest/gtest.h"
#include "pokerGame/card/Hand.h"
#include <vector>

class HandTest : public ::testing::Test {
protected:
    virtual void SetUp() {

    }
    virtual void TearDown() {
    }

    pokerGame::card::Hand h;
};

TEST_F(HandTest, newHandHasNoCard) {
    ASSERT_EQ(0, h.getSize());
}

TEST_F(HandTest, addingCardToHandIncreasesItsSize) {
    pokerGame::card::Card A_CARD(pokerGame::card::ACE, pokerGame::card::DIAMOND);
    h.addCard(A_CARD);
    ASSERT_EQ(1, h.getSize());
}

TEST_F(HandTest, newHandAsNoHandValue) {
    pokerGame::card::HandValue handValue = h.getHandValue();
    ASSERT_EQ(pokerGame::card::NO_HAND_VALUE.type, handValue.type);
}

TEST_F(HandTest, handValueIsRightHighCardWhenNoHand) {
    pokerGame::card::Card A_CARD(pokerGame::card::ACE, pokerGame::card::DIAMOND);
    pokerGame::card::HandValue highAceHand = {pokerGame::card::HIGH_CARD, {pokerGame::card::ACE, 0, 0, 0, 0}};
    h.addCard(A_CARD);

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(highAceHand.type, handValue.type);
    ASSERT_EQ(highAceHand.ranks[0], handValue.ranks[0]);
}

TEST_F(HandTest, handValueContainsFiveHighestCardsInDescendingOrderWhenHighHand) {
    std::vector<pokerGame::card::Card> descendingOrderCards;

    descendingOrderCards.push_back(pokerGame::card::Card(pokerGame::card::ACE, pokerGame::card::DIAMOND));
    descendingOrderCards.push_back(pokerGame::card::Card(pokerGame::card::KING, pokerGame::card::DIAMOND));
    descendingOrderCards.push_back(pokerGame::card::Card(pokerGame::card::QUEEN, pokerGame::card::SPADE));
    descendingOrderCards.push_back(pokerGame::card::Card(8, pokerGame::card::SPADE));
    descendingOrderCards.push_back(pokerGame::card::Card(6, pokerGame::card::SPADE));

    pokerGame::card::Card secondLowestCard(5, pokerGame::card::HEART);
    pokerGame::card::Card lowestCard(3, pokerGame::card::HEART);

    h.addCard(lowestCard);
    for (int i = 0; i < pokerGame::card::HAND_SIZE; i++) {
        h.addCard(descendingOrderCards[i]);
    }
    h.addCard(secondLowestCard);

    pokerGame::card::HandValue handValue = h.getHandValue();

    for (int i = 0; i < pokerGame::card::HAND_SIZE; i++) {
        ASSERT_EQ(descendingOrderCards[i].getRank(), handValue.ranks[i]);
    }
}

TEST_F(HandTest, handValueIsPairWhenHandContainsPair) {
    int PAIR_RANK = 6;
    h.addCard(pokerGame::card::Card(PAIR_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(PAIR_RANK, pokerGame::card::HEART));

    bool hasPair = h.hasPair();

    ASSERT_TRUE(hasPair);
}

TEST_F(HandTest, handValueIsPairWhenHandContainsTwoPairs) {
    int FIRST_PAIR_RANK = 6;
    int SECOND_PAIR_RANK = 4;h.addCard(pokerGame::card::Card(FIRST_PAIR_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(FIRST_PAIR_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(SECOND_PAIR_RANK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(SECOND_PAIR_RANK, pokerGame::card::HEART));

    bool hasPair = h.hasPair();

    ASSERT_TRUE(hasPair);
}

TEST_F(HandTest, handValueIsPairWhenHandContainsThreeOfAKind) {
    int A_RANK = 5;
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::DIAMOND));

    bool hasPair = h.hasPair();

    ASSERT_TRUE(hasPair);
}

TEST_F(HandTest, handValueIsPairWhenHandContainsFullHouse) {
    int PAIR_RANK = 6;
    int A_RANK = 5;
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::DIAMOND));
    h.addCard(pokerGame::card::Card(PAIR_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(PAIR_RANK, pokerGame::card::HEART));

    bool hasPair = h.hasPair();

    ASSERT_TRUE(hasPair);
}

TEST_F(HandTest, handValueIsPairWhenHandContainsFourOfAKind) {
    int A_RANK = 5;
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::DIAMOND));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::CLUB));

    bool hasPair = h.hasPair();

    ASSERT_TRUE(hasPair);
}

TEST_F(HandTest, hasPairReturnsTrueIfHandContainsAPair) {
    int PAIR_RANK = 6;
    h.addCard(pokerGame::card::Card(PAIR_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(PAIR_RANK, pokerGame::card::HEART));

    pokerGame::card::HandValue pairHandValue = {pokerGame::card::PAIR, {PAIR_RANK,0,0,0,0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(pairHandValue, handValue);
}

TEST_F(HandTest, handValueStoresThreeHighestCardsNotInPairWhenContainPair) {
    int PAIR_RANK = 6;
    h.addCard(pokerGame::card::Card(PAIR_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(PAIR_RANK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(pokerGame::card::ACE, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(pokerGame::card::KING, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(9, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(5, pokerGame::card::HEART));

    pokerGame::card::HandValue pairHandValue = {pokerGame::card::PAIR, {PAIR_RANK,pokerGame::card::ACE,pokerGame::card::KING,9,5}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(pairHandValue, handValue);
}

TEST_F(HandTest, handValueIsTwoPairsWhenHandContainsTwoPairs) {
    int FIRST_PAIR_RANK = 6;
    int SECOND_PAIR_RANK = 4;
    h.addCard(pokerGame::card::Card(FIRST_PAIR_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(FIRST_PAIR_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(SECOND_PAIR_RANK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(SECOND_PAIR_RANK, pokerGame::card::HEART));

    pokerGame::card::HandValue pairHandValue = {pokerGame::card::TWO_PAIRS, {FIRST_PAIR_RANK,SECOND_PAIR_RANK,0,0,0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(pairHandValue, handValue);
}

TEST_F(HandTest, handValueStoresHighestCardNotInPairsWhenContainsTwoPairs) {
    int FIRST_PAIR_RANK = 6;
    int SECOND_PAIR_RANK = 4;
    h.addCard(pokerGame::card::Card(FIRST_PAIR_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(FIRST_PAIR_RANK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(SECOND_PAIR_RANK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(SECOND_PAIR_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(5, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(3, pokerGame::card::SPADE));

    pokerGame::card::HandValue pairHandValue = {pokerGame::card::TWO_PAIRS, {FIRST_PAIR_RANK,SECOND_PAIR_RANK,5,0,0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(pairHandValue, handValue);
}

TEST_F(HandTest, handValueIsThreeOfAKindWhenHandContainsThreeOfAKind) {
    int A_RANK = 8;
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::DIAMOND));

    pokerGame::card::HandValue threeOfAKindHandValue = {pokerGame::card::THREE_OF_A_KIND, {A_RANK, 0, 0, 0, 0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(threeOfAKindHandValue, handValue);
}

TEST_F(HandTest, handValueStoresTwoHighestCardsNotInToaKWhenContainsThreeOfAKind) {
    int A_RANK = 8;
    int HIGHEST_RANK_NOT_IN_TOAK = pokerGame::card::KING;
    int SECOND_HIGHEST_RANK_NOT_IN_TOAK = 10;
    int THIRD_HIGHEST_RANK_NOT_IN_TOAK = 9;
    int RANK_LOWER_THAN_TOAK = 5;
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::DIAMOND));
    h.addCard(pokerGame::card::Card(RANK_LOWER_THAN_TOAK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(THIRD_HIGHEST_RANK_NOT_IN_TOAK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(SECOND_HIGHEST_RANK_NOT_IN_TOAK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(HIGHEST_RANK_NOT_IN_TOAK, pokerGame::card::DIAMOND));

    pokerGame::card::HandValue threeOfAKindHandValue = {pokerGame::card::THREE_OF_A_KIND, {A_RANK, HIGHEST_RANK_NOT_IN_TOAK, SECOND_HIGHEST_RANK_NOT_IN_TOAK, 0, 0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(threeOfAKindHandValue, handValue);
}

TEST_F(HandTest, serieOf4CardsIsNotAStraight) {
    h.addCard(pokerGame::card::Card(10, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(9, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(8, pokerGame::card::DIAMOND));
    h.addCard(pokerGame::card::Card(7, pokerGame::card::SPADE));

    pokerGame::card::HandValue straightValue = {pokerGame::card::STRAIGHT, {10, 0, 0, 0, 0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_FALSE(straightValue == handValue);
}

TEST_F(HandTest, handValueIsStraightWhenHandContainsStraight) {
    h.addCard(pokerGame::card::Card(10, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(9, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(8, pokerGame::card::DIAMOND));
    h.addCard(pokerGame::card::Card(7, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(6, pokerGame::card::SPADE));

    pokerGame::card::HandValue straightValue = {pokerGame::card::STRAIGHT, {10, 0, 0, 0, 0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(straightValue, handValue);
}

TEST_F(HandTest, handValueDoesNotStoreHighCardsNotInStraightWhenContainStraight) {
    h.addCard(pokerGame::card::Card(10, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(9, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(8, pokerGame::card::DIAMOND));
    h.addCard(pokerGame::card::Card(7, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(6, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(pokerGame::card::ACE, pokerGame::card::SPADE));

    pokerGame::card::HandValue straightValue = {pokerGame::card::STRAIGHT, {10, 0, 0, 0, 0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(straightValue,handValue);
}

TEST_F(HandTest, handValueStoresHighestInStraight) {
    h.addCard(pokerGame::card::Card(10, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(9, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(8, pokerGame::card::DIAMOND));
    h.addCard(pokerGame::card::Card(7, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(6, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(pokerGame::card::JACK, pokerGame::card::SPADE));

    pokerGame::card::HandValue straightValue = {pokerGame::card::STRAIGHT, {10, 0, 0, 0, 0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_FALSE(straightValue == handValue);
}

TEST_F(HandTest, FourCardsOfSameSuitIsNotFlush) {
    h.addCard(pokerGame::card::Card(10, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(9, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(8, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(7, pokerGame::card::SPADE));

    pokerGame::card::HandValue flushValue = {pokerGame::card::FLUSH, {10, 9, 8, 7, 0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_FALSE(flushValue == handValue);
}

TEST_F(HandTest, handValueIsFlushWhenHandContainsFlush) {
    h.addCard(pokerGame::card::Card(10, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(9, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(8, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(7, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(4, pokerGame::card::SPADE));

    pokerGame::card::HandValue flushValue = {pokerGame::card::FLUSH, {10, 9, 8, 7, 4}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(flushValue, handValue);
}

TEST_F(HandTest, handValueDoesNotStoreHighCardsNotInFlushWhenContainFlush) {
    h.addCard(pokerGame::card::Card(10, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(9, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(8, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(7, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(4, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(pokerGame::card::ACE, pokerGame::card::HEART));

    pokerGame::card::HandValue flushValue = {pokerGame::card::FLUSH, {10, 9, 8, 7, 4}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(flushValue, handValue);
}

TEST_F(HandTest, handValueFlushTakesHighestOfSameSuit) {
    h.addCard(pokerGame::card::Card(10, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(9, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(8, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(7, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(4, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(pokerGame::card::ACE, pokerGame::card::SPADE));

    pokerGame::card::HandValue flushValue = {pokerGame::card::FLUSH, {pokerGame::card::ACE,10, 9, 8, 7}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(flushValue, handValue);
}

TEST_F(HandTest, handValueIsFullHouseWhenHandContainsFullHouse) {
    h.addCard(pokerGame::card::Card(7, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(7, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(2, pokerGame::card::DIAMOND));
    h.addCard(pokerGame::card::Card(2, pokerGame::card::CLUB));
    h.addCard(pokerGame::card::Card(2, pokerGame::card::HEART));

    pokerGame::card::HandValue fullHouseValue = {pokerGame::card::FULL_HOUSE, {2, 7, 0, 0, 0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(fullHouseValue, handValue);
}

TEST_F(HandTest, handValueIsFourOfAKindWhenHandContainsFourOfAKind) {
    int A_RANK = 8;
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::DIAMOND));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::CLUB));

    pokerGame::card::HandValue fourOfAKindHandValue = {pokerGame::card::FOUR_OF_A_KIND, {A_RANK, 0, 0, 0, 0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(fourOfAKindHandValue, handValue);
}

TEST_F(HandTest, handValueStoresHighestCardsNotInFoaKWhenContainsFoutOfAKind) {
    int A_RANK = 8;
    int HIGHEST_RANK_NOT_IN_TOAK = pokerGame::card::KING;
    int SECOND_HIGHEST_RANK_NOT_IN_TOAK = 10;
    int RANK_LOWER_THAN_TOAK = 5;
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::DIAMOND));
    h.addCard(pokerGame::card::Card(A_RANK, pokerGame::card::CLUB));
    h.addCard(pokerGame::card::Card(RANK_LOWER_THAN_TOAK, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(SECOND_HIGHEST_RANK_NOT_IN_TOAK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(HIGHEST_RANK_NOT_IN_TOAK, pokerGame::card::DIAMOND));

    pokerGame::card::HandValue fourOfAKindHandValue = {pokerGame::card::FOUR_OF_A_KIND, {A_RANK, HIGHEST_RANK_NOT_IN_TOAK, 0, 0, 0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(fourOfAKindHandValue, handValue);
}

TEST_F(HandTest, handValueIsStraightFlushWhenContainsStraightFlush) {
    h.addCard(pokerGame::card::Card(8, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(7, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(6, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(5, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(4, pokerGame::card::SPADE));

    pokerGame::card::HandValue straightFlush = {pokerGame::card::STRAIGHT_FLUSH, {8, 0, 0, 0, 0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_EQ(straightFlush, handValue);
}

TEST_F(HandTest, handValueIsNotStraightFlushIfContainsUnrelatedStraightAndFlush) {
    h.addCard(pokerGame::card::Card(8, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(7, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(6, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(5, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(4, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(pokerGame::card::JACK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(pokerGame::card::QUEEN, pokerGame::card::HEART));

    pokerGame::card::HandValue straightFlush = {pokerGame::card::STRAIGHT_FLUSH, {8, 0, 0, 0, 0}};

    pokerGame::card::HandValue handValue = h.getHandValue();

    ASSERT_FALSE(straightFlush.type ==  handValue.type);
}

TEST_F(HandTest, sumOfPowerReturnsTheSumOfTheCardsRanks) {
    h.addCard(pokerGame::card::Card(8, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(7, pokerGame::card::SPADE));
    h.addCard(pokerGame::card::Card(6, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(3, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(2, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(pokerGame::card::JACK, pokerGame::card::HEART));
    h.addCard(pokerGame::card::Card(pokerGame::card::QUEEN, pokerGame::card::HEART));

    int sumOfPower = h.getSumOfPower();

    ASSERT_EQ(49 , sumOfPower);
}
