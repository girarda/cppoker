#include "gtest/gtest.h"
#include "tests/mocks/pokerGame/card/HandMock.h"
#include "playerController/bot/SimpleBettingBluffStrategy.h"
#include "pokerGame/modeling/BettingContext.h"
#include "pokerGame/modeling/OpponentModel.h"

using ::testing::Return;

class SimpleBettingBluffStrategyTest : public ::testing::Test {
protected:
    std::vector<pokerGame::card::Card>* hole;
    std::vector<pokerGame::card::Card>* sharedCards;
    playerController::bot::BettingStrategy* simpleBettingBluffStrategy;
    pokerGame::modeling::BettingContext* bettingContext;
    std::vector<pokerGame::modeling::OpponentModel> opponentModels;

    static const float A_BET;
    static const float ZERO_BET;
    static const float BIG_BLIND;
    static const int NUMBER_OF_RAISES;
    static const int NUMBER_OF_PLAYERS;
    static const pokerGame::BettingRoundType A_BETTING_ROUND_TYPE;

    void initPreFlopPair();
    void initPreFlopSumOfPowerHigherThan16();
    void initPreFlopSumOfPowerLowerThan16HigherThan8();
    void initPreFlopSumOfPowerLower8();
    void initPostFlopThreeOfAKind();
    void initPostFlopHighCard();
    void initPostFlopPair();

    virtual void SetUp() {
        simpleBettingBluffStrategy = new playerController::bot::SimpleBettingBluffStrategy();
        hole = new std::vector<pokerGame::card::Card>();
        sharedCards = new std::vector<pokerGame::card::Card>();
    }
    virtual void TearDown() {
        delete hole;
        delete sharedCards;
        delete simpleBettingBluffStrategy;
        delete bettingContext;
    }
};

const float SimpleBettingBluffStrategyTest::A_BET(10);
const float SimpleBettingBluffStrategyTest::ZERO_BET(0);
const float SimpleBettingBluffStrategyTest::BIG_BLIND(1);
const int SimpleBettingBluffStrategyTest::NUMBER_OF_RAISES(0);
const int SimpleBettingBluffStrategyTest::NUMBER_OF_PLAYERS(2);
const pokerGame::BettingRoundType SimpleBettingBluffStrategyTest::A_BETTING_ROUND_TYPE(pokerGame::PRE_FLOP);

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfHandValueIsAPairMakeDecisionReturnsRaise) {
    initPreFlopPair();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards, bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::RAISE, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfHandValueIsAPairNewBetEqualsSumOfMinBetAndBigBlind) {
    initPreFlopPair();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    float newBet = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards, bettingContext, opponentModels).bet;
    ASSERT_EQ(A_BET+BIG_BLIND, newBet);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfSumOfPowerOfHandIsLowerThan9ThenBluffAndRaise) {
    initPreFlopSumOfPowerLower8();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards, bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::RAISE, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfHandValueIsLowerThan9ThenNewBetEqualsSumOfMinBetBigBlind) {
    initPreFlopSumOfPowerLower8();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    float newBet = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards, bettingContext, opponentModels).bet;
    ASSERT_EQ(A_BET+BIG_BLIND, newBet);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfSumOfPowerOfHandIsHigherThan16MakeDecisionReturnsCall) {
    initPreFlopSumOfPowerHigherThan16();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards, bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::CALL, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfSumOfPowerOfHandIsHigherThan16NewBetIsMinBet) {
    initPreFlopSumOfPowerHigherThan16();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    float newBet = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards, bettingContext, opponentModels).bet;
    ASSERT_EQ(A_BET, newBet);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfSumOfPowerOfHandIsLowerThan16MakeDecisionReturnsCall) {
    initPreFlopSumOfPowerLowerThan16HigherThan8();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards,bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::FOLD, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPreFlopIfSumOfPowerOfHandIsLowerThan16NewBetIsZero) {
    initPreFlopSumOfPowerLowerThan16HigherThan8();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, ZERO_BET, BIG_BLIND);
    float newBet = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards,bettingContext, opponentModels).bet;
    ASSERT_EQ(0, newBet);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsHigherOrEqualsToThreeOfAKindMakeDecisionReturnsRaise) {
    initPostFlopThreeOfAKind();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards, bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::RAISE, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsHigherOrEqualsToThreeOfAKindNewBetEqualsSumOfMinBetAndBigBlind) {
    initPostFlopThreeOfAKind();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    float newBet = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards, bettingContext, opponentModels).bet;
    ASSERT_EQ(A_BET+BIG_BLIND, newBet);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsHighCardBluffAndRaise) {
    initPostFlopHighCard();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards,bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::RAISE, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsHighCardAndBetIsNotZeroThenNewBetEqualsSumOfMinBetAndBigBlind) {
    initPostFlopHighCard();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    float newBet = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards, bettingContext, opponentModels).bet;
    ASSERT_EQ(A_BET+BIG_BLIND, newBet);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsLowerThanThreeOfAKindAndBetIsZeroThenCall) {
    initPostFlopPair();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, ZERO_BET, BIG_BLIND);
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards, bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::CALL, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsLowerThanThreeOfAKindAndBetIsZeroThenNewBetIsInitialBet) {
    initPostFlopPair();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, ZERO_BET, BIG_BLIND);
    float newBet = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards, bettingContext, opponentModels).bet;
    ASSERT_EQ(ZERO_BET, newBet);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsLowerThanThreeOfAKindAndBetIsNotZeroThenFold) {
    initPostFlopPair();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    pokerGame::Choice choice = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards, bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::FOLD, choice);
}

TEST_F(SimpleBettingBluffStrategyTest, whenPostFlopIfHandValueIsLowerThanThreeOfAKindAndBetIsNotZeroThenNewBetIsZero) {
    initPostFlopPair();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    float newBet = simpleBettingBluffStrategy->makeDecision(*hole, *sharedCards, bettingContext, opponentModels).bet;
    ASSERT_EQ(0, newBet);
}

void SimpleBettingBluffStrategyTest::initPreFlopPair() {
    pokerGame::card::Card c1(pokerGame::card::ACE, pokerGame::card::SPADE);
    pokerGame::card::Card c2(pokerGame::card::ACE, pokerGame::card::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
}

void SimpleBettingBluffStrategyTest::initPreFlopSumOfPowerHigherThan16() {
    pokerGame::card::Card c1(pokerGame::card::KING, pokerGame::card::SPADE);
    pokerGame::card::Card c2(pokerGame::card::QUEEN, pokerGame::card::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
}

void SimpleBettingBluffStrategyTest::initPreFlopSumOfPowerLowerThan16HigherThan8() {
    pokerGame::card::Card c1(2, pokerGame::card::SPADE);
    pokerGame::card::Card c2(8, pokerGame::card::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
}

void SimpleBettingBluffStrategyTest::initPreFlopSumOfPowerLower8() {
    pokerGame::card::Card c1(2, pokerGame::card::SPADE);
    pokerGame::card::Card c2(3, pokerGame::card::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
}


void SimpleBettingBluffStrategyTest::initPostFlopThreeOfAKind() {
    pokerGame::card::Card c1(2, pokerGame::card::SPADE);
    pokerGame::card::Card c2(3, pokerGame::card::HEART);
    pokerGame::card::Card c3(3, pokerGame::card::SPADE);
    pokerGame::card::Card c4(3, pokerGame::card::CLUB);
    pokerGame::card::Card c5(6, pokerGame::card::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
    sharedCards->push_back(c3);
    sharedCards->push_back(c4);
    sharedCards->push_back(c5);
}

void SimpleBettingBluffStrategyTest::initPostFlopHighCard() {
    pokerGame::card::Card c1(2, pokerGame::card::SPADE);
    pokerGame::card::Card c3(3, pokerGame::card::HEART);
    pokerGame::card::Card c2(4, pokerGame::card::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
    sharedCards->push_back(c3);
}

void SimpleBettingBluffStrategyTest::initPostFlopPair() {
    pokerGame::card::Card c1(2, pokerGame::card::SPADE);
    pokerGame::card::Card c3(2, pokerGame::card::HEART);
    pokerGame::card::Card c2(4, pokerGame::card::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
    sharedCards->push_back(c3);
}
