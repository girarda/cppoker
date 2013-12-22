#include "gtest/gtest.h"
#include "pokerGame/Card.h"

TEST(Card, ConstructorLowestValues) {
    pokerGame::Card lowCard(2, pokerGame::DIAMOND);
    ASSERT_EQ(lowCard.getRank(), 2);
    ASSERT_EQ(lowCard.getSuit(), pokerGame::DIAMOND);
}

TEST(Card, ConstructorHighestValues) {
    pokerGame::Card highCard(pokerGame::ACE, pokerGame::SPADE);
    ASSERT_EQ(highCard.getRank(), pokerGame::ACE);
    ASSERT_EQ(highCard.getSuit(), pokerGame::SPADE);
}

TEST(Card, ToStringTwoOfDiamond) {
    std::string cardString("2D");
    pokerGame::Card card(2, pokerGame::DIAMOND);
    ASSERT_EQ(card.toString(), cardString);
}

TEST(Card, ToStringTenOfHeart) {
    std::string cardString("10H");
    pokerGame::Card card(10, pokerGame::HEART);
    ASSERT_EQ(card.toString(), cardString);
}


TEST(Card, ToStringJackOfClub) {
    std::string cardString("JC");
    pokerGame::Card card(pokerGame::JACK, pokerGame::CLUB);
    ASSERT_EQ(card.toString(), cardString);
}

TEST(Card, ToStringQueenOfSpade) {
    std::string cardString("QS");
    pokerGame::Card card(pokerGame::QUEEN, pokerGame::SPADE);
    ASSERT_EQ(card.toString(), cardString);
}

TEST(Card, ToStringKingOfSpade) {
    std::string cardString("KS");
    pokerGame::Card card(pokerGame::KING, pokerGame::SPADE);
    ASSERT_EQ(card.toString(), cardString);
}

TEST(Card, ToStringAceOfSpade) {
    std::string cardString("AS");
    pokerGame::Card card(pokerGame::ACE, pokerGame::SPADE);
    ASSERT_EQ(card.toString(), cardString);
}
