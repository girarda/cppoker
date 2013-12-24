#include "gtest/gtest.h"
#include "HandStrengthEvaluatorMock.h"
#include "playerInterface/bot/ProbabilisticBettingStrategy.h"
#include "tests/mocks/PreFlopStatisticsMock.h"
#include "pokerGame/context/BettingContext.h"

using ::testing::Return;
using ::testing::_;

class ProbabilisticBettingStrategyTest : public ::testing::Test {
protected:
    std::vector<pokerGame::Card>* hole;
    std::vector<pokerGame::Card>* sharedCards;
    playerInterface::bot::BettingStrategy* probabilisticBettingStrategy;
    test::HandStrengthEvaluatorMock* handEvaluator;
    test::PreFlopStatisticsMock* preFlopStatistics;
    pokerGame::context::BettingContext* bettingContext;

    void initPreFlopHand();
    void initPostFlopHand();

    static const float A_BET;
    static const float ZERO_BET;
    static const float BIG_BLIND;
    static const int NUMBER_OF_RAISES;
    static const int NUMBER_OF_PLAYERS;
    static const double HIGHER_THAN_HIGH_THRESHOLD;
    static const double HIGHER_THAN_LOW_THRESHOLD;
    static const double LOWER_THAN_LOW_THRESHOLD;
    static const pokerGame::BettingRoundType A_BETTING_ROUND_TYPE;

    virtual void SetUp() {
        hole = new std::vector<pokerGame::Card>();
        sharedCards = new std::vector<pokerGame::Card>();
        handEvaluator = new test::HandStrengthEvaluatorMock();
        preFlopStatistics = new test::PreFlopStatisticsMock();
        probabilisticBettingStrategy = new playerInterface::bot::ProbabilisticBettingStrategy(handEvaluator, preFlopStatistics);
        bettingContext = new pokerGame::context::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS);
    }
    virtual void TearDown() {
        delete hole;
        delete sharedCards;
        delete probabilisticBettingStrategy;
        delete handEvaluator;
        delete preFlopStatistics;
        delete bettingContext;
    }
};

const float ProbabilisticBettingStrategyTest::A_BET(10);
const float ProbabilisticBettingStrategyTest::ZERO_BET(0);
const float ProbabilisticBettingStrategyTest::BIG_BLIND(1);
const int ProbabilisticBettingStrategyTest::NUMBER_OF_RAISES(0);
const int ProbabilisticBettingStrategyTest::NUMBER_OF_PLAYERS(2);
const double ProbabilisticBettingStrategyTest::HIGHER_THAN_HIGH_THRESHOLD(0.81);
const double ProbabilisticBettingStrategyTest::HIGHER_THAN_LOW_THRESHOLD(0.41);
const double ProbabilisticBettingStrategyTest::LOWER_THAN_LOW_THRESHOLD(0.39);
const pokerGame::BettingRoundType ProbabilisticBettingStrategyTest::A_BETTING_ROUND_TYPE(pokerGame::PRE_FLOP);

// TODO add tests for preFlop

//TEST_F(ProbabilisticBettingStrategyTest, whenPreFlopIfHandStrengthIsHigherThanHighThresholdThenRaise) {
//    initPreFlopHand();
//    EXPECT_CALL(*preFlopStatistics, load(_));
//    EXPECT_CALL(*preFlopStatistics, getWinningProbability(_, _)).WillOnce(Return(HIGHER_THAN_HIGH_THRESHOLD));
//    pokerGame::Choice choice = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).choice;
//    ASSERT_EQ(pokerGame::RAISE, choice);
//}

//TEST_F(ProbabilisticBettingStrategyTest, whenPreFlopIfHandStrengthIsHigherThanHighThresholdNewBetEqualsSumOfMinBetAndBigBlind) {
//    initPreFlopHand();
//    EXPECT_CALL(*preFlopStatistics, load(_));
//    EXPECT_CALL(*preFlopStatistics, getWinningProbability(_, _)).WillOnce(Return(HIGHER_THAN_HIGH_THRESHOLD));
//    float newBet = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).bet;
//    ASSERT_EQ(A_BET+BIG_BLIND, newBet);
//}

//TEST_F(ProbabilisticBettingStrategyTest, whenPreFlopIfHandStrengthIsHigherThanLowThresholdThenCall) {
//    initPreFlopHand();
//    EXPECT_CALL(*preFlopStatistics, load(_));
//    EXPECT_CALL(*preFlopStatistics, getWinningProbability(_, _)).WillOnce(Return(HIGHER_THAN_LOW_THRESHOLD));
//    pokerGame::Choice choice = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).choice;
//    ASSERT_EQ(pokerGame::CALL, choice);
//}

//TEST_F(ProbabilisticBettingStrategyTest, whenPreFlopIfHandStrengthIsHigherThanLowThresholdNewBetEqualsMinBet) {
//    initPreFlopHand();
//    EXPECT_CALL(*preFlopStatistics, load(_));
//    EXPECT_CALL(*preFlopStatistics, getWinningProbability(_, _)).WillOnce(Return(HIGHER_THAN_LOW_THRESHOLD));
//    float newBet = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).bet;
//    ASSERT_EQ(A_BET, newBet);
//}

//TEST_F(ProbabilisticBettingStrategyTest, whenPreFlopIfHandStrengthIsLowerThanLowThresholdThenFold) {
//    initPreFlopHand();
//    EXPECT_CALL(*preFlopStatistics, load(_));
//    EXPECT_CALL(*preFlopStatistics, getWinningProbability(_, _)).WillOnce(Return(LOWER_THAN_LOW_THRESHOLD));
//    pokerGame::Choice choice = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).choice;
//    ASSERT_EQ(pokerGame::FOLD, choice);
//}

//TEST_F(ProbabilisticBettingStrategyTest, whenPreFlopIfHandStrengthIsLowerThanLowThresholdNewBetEqualsZero) {
//    initPreFlopHand();
//    EXPECT_CALL(*preFlopStatistics, load(_));
//    EXPECT_CALL(*preFlopStatistics, getWinningProbability(_, _)).WillOnce(Return(LOWER_THAN_LOW_THRESHOLD));
//    float newBet = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).bet;
//    ASSERT_EQ(0, newBet);
//}

//TEST_F(ProbabilisticBettingStrategyTest, whenPostFlopIfHandStrengthIsHigherThanHighThresholdThenRaise) {
//    initPostFlopHand();
//    EXPECT_CALL(*handEvaluator, evaluate(_, _, _)).WillOnce(Return(HIGHER_THAN_HIGH_THRESHOLD));
//    pokerGame::Choice choice = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).choice;
//    ASSERT_EQ(pokerGame::RAISE, choice);
//}

//TEST_F(ProbabilisticBettingStrategyTest, whenPostFlopIfHandStrengthIsHigherThanHighThresholdNewBetEqualsSumOfMinBetAndBigBlind) {
//    initPostFlopHand();
//    EXPECT_CALL(*handEvaluator, evaluate(_, _, _)).WillOnce(Return(HIGHER_THAN_HIGH_THRESHOLD));
//    float newBet = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).bet;
//    ASSERT_EQ(A_BET+BIG_BLIND, newBet);
//}

//TEST_F(ProbabilisticBettingStrategyTest, whenPostFlopIfHandStrengthIsHigherThanLowThresholdThenCall) {
//    initPostFlopHand();
//    EXPECT_CALL(*handEvaluator, evaluate(_, _, _)).WillOnce(Return(HIGHER_THAN_LOW_THRESHOLD));
//    pokerGame::Choice choice = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).choice;
//    ASSERT_EQ(pokerGame::CALL, choice);
//}

//TEST_F(ProbabilisticBettingStrategyTest, whenPostFlopIfHandStrengthIsHigherThanLowThresholdNewBetIsInitialBet) {
//    initPostFlopHand();
//    EXPECT_CALL(*handEvaluator, evaluate(_, _, _)).WillOnce(Return(HIGHER_THAN_LOW_THRESHOLD));
//    float newBet = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).bet;
//    ASSERT_EQ(A_BET, newBet);
//}

//TEST_F(ProbabilisticBettingStrategyTest, whenPostFlopIfHandStrengthIsLowerThanLowThresholdAndMinBetIsZeroThenCall) {
//    initPostFlopHand();
//    EXPECT_CALL(*handEvaluator, evaluate(_, _, _)).WillOnce(Return(LOWER_THAN_LOW_THRESHOLD));
//    pokerGame::Choice choice = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, ZERO_BET, BIG_BLIND, bettingContext).choice;
//    ASSERT_EQ(pokerGame::CALL, choice);
//}

//TEST_F(ProbabilisticBettingStrategyTest, whenPostFlopIfHandStrengthIsLowerThanLowThresholdAndMinBetIsZeroNewBetIsZero) {
//    initPostFlopHand();
//    EXPECT_CALL(*handEvaluator, evaluate(_, _, _)).WillOnce(Return(LOWER_THAN_LOW_THRESHOLD));
//    float newBet = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, ZERO_BET, BIG_BLIND, bettingContext).bet;
//    ASSERT_EQ(0, newBet);
//}

//TEST_F(ProbabilisticBettingStrategyTest, whenPostFlopIfHandStrengthIsLowerThanLowThresholdThenFold) {
//    initPostFlopHand();
//    EXPECT_CALL(*handEvaluator, evaluate(_, _, _)).WillOnce(Return(LOWER_THAN_LOW_THRESHOLD));
//    pokerGame::Choice choice = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).choice;
//    ASSERT_EQ(pokerGame::FOLD, choice);
//}

//TEST_F(ProbabilisticBettingStrategyTest, whenPostFlopIfHandStrengthIsLowerThanLowThresholdNewBetIsZero) {
//    initPostFlopHand();
//    EXPECT_CALL(*handEvaluator, evaluate(_, _, _)).WillOnce(Return(LOWER_THAN_LOW_THRESHOLD));
//    float newBet = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, A_BET, BIG_BLIND, bettingContext).bet;
//    ASSERT_EQ(0, newBet);
//}

void ProbabilisticBettingStrategyTest::initPreFlopHand() {
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c2(3, pokerGame::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
}

void ProbabilisticBettingStrategyTest::initPostFlopHand() {
    pokerGame::Card c1(2, pokerGame::SPADE);
    pokerGame::Card c2(3, pokerGame::HEART);
    pokerGame::Card c3(3, pokerGame::SPADE);
    pokerGame::Card c4(3, pokerGame::CLUB);
    pokerGame::Card c5(6, pokerGame::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
    sharedCards->push_back(c3);
    sharedCards->push_back(c4);
    sharedCards->push_back(c5);
}
