#include "gtest/gtest.h"
#include "pokerGame/card/Card.h"

TEST(Card, ConstructorLowestValues) {
    pokerGame::card::Card lowCard(2, pokerGame::card::DIAMOND);
    ASSERT_EQ(lowCard.getRank(), 2);
    ASSERT_EQ(lowCard.getSuit(), pokerGame::card::DIAMOND);
}

TEST(Card, ConstructorHighestValues) {
    pokerGame::card::Card highCard(pokerGame::card::ACE, pokerGame::card::SPADE);
    ASSERT_EQ(highCard.getRank(), pokerGame::card::ACE);
    ASSERT_EQ(highCard.getSuit(), pokerGame::card::SPADE);
}

TEST(Card, ToStringTwoOfDiamond) {
    std::string cardString("2D");
    pokerGame::card::Card card(2, pokerGame::card::DIAMOND);
    ASSERT_EQ(card.toString(), cardString);
}

TEST(Card, ToStringTenOfHeart) {
    std::string cardString("10H");
    pokerGame::card::Card card(10, pokerGame::card::HEART);
    ASSERT_EQ(card.toString(), cardString);
}


TEST(Card, ToStringJackOfClub) {
    std::string cardString("JC");
    pokerGame::card::Card card(pokerGame::card::JACK, pokerGame::card::CLUB);
    ASSERT_EQ(card.toString(), cardString);
}

TEST(Card, ToStringQueenOfSpade) {
    std::string cardString("QS");
    pokerGame::card::Card card(pokerGame::card::QUEEN, pokerGame::card::SPADE);
    ASSERT_EQ(card.toString(), cardString);
}

TEST(Card, ToStringKingOfSpade) {
    std::string cardString("KS");
    pokerGame::card::Card card(pokerGame::card::KING, pokerGame::card::SPADE);
    ASSERT_EQ(card.toString(), cardString);
}

TEST(Card, ToStringAceOfSpade) {
    std::string cardString("AS");
    pokerGame::card::Card card(pokerGame::card::ACE, pokerGame::card::SPADE);
    ASSERT_EQ(card.toString(), cardString);
}

TEST(Card, canGetCardRank) {
    pokerGame::card::Card card(pokerGame::card::ACE, pokerGame::card::SPADE);
    ASSERT_EQ(pokerGame::card::ACE, card.getRank());
}

TEST(Card, canGetCardSuit) {
    pokerGame::card::Card card(pokerGame::card::ACE, pokerGame::card::SPADE);
    ASSERT_EQ(pokerGame::card::SPADE, card.getSuit());
}

TEST(Card, isSameSuitReturnsTrueIfTwoCardsSuitsAreTheSame) {
    pokerGame::card::Card card(pokerGame::card::ACE, pokerGame::card::SPADE);
    pokerGame::card::Card anotherCard(pokerGame::card::KING, pokerGame::card::SPADE);
    bool sameSuit = card.isSameSuit(anotherCard);
    ASSERT_TRUE(sameSuit);
}

TEST(Card, isSameSuitReturnsFalseIfTwoCardsSuitsAreNotTheSame) {
    pokerGame::card::Card card(pokerGame::card::ACE, pokerGame::card::SPADE);
    pokerGame::card::Card anotherCard(pokerGame::card::KING, pokerGame::card::HEART);
    bool sameSuit = card.isSameSuit(anotherCard);
    ASSERT_FALSE(sameSuit);
}

TEST(Card, newCardIsVisible) {
    pokerGame::card::Card card(pokerGame::card::ACE, pokerGame::card::SPADE);
    ASSERT_TRUE(card.isVisible());
}

TEST(Card, cardIsNotVisibleAfterHide) {
    pokerGame::card::Card card(pokerGame::card::ACE, pokerGame::card::SPADE);
    card.hide();
    ASSERT_FALSE(card.isVisible());
}

TEST(Card, cardIsVisibleAfterCallingHideThenShow) {
    pokerGame::card::Card card(pokerGame::card::ACE, pokerGame::card::SPADE);
    card.hide();
    card.show();
    ASSERT_TRUE(card.isVisible());
}
