#include "gtest/gtest.h"
#include "tests/mocks/pokerGame/card/HandStrengthEvaluatorMock.h"
#include "playerController/bot/ProbabilisticBettingStrategy.h"
#include "tests/mocks/pokerGame/simulation/PreFlopStatisticsMock.h"
#include "pokerGame/modeling/BettingContext.h"
#include "pokerGame/modeling/OpponentModel.h"

using ::testing::Return;
using ::testing::_;

class ProbabilisticBettingStrategyTest : public ::testing::Test {
protected:
    std::vector<pokerGame::card::Card>* hole;
    std::vector<pokerGame::card::Card>* sharedCards;
    std::vector<pokerGame::modeling::OpponentModel> opponentModels;
    playerController::bot::BettingStrategy* probabilisticBettingStrategy;
    test::HandStrengthEvaluatorMock* handEvaluator;
    test::PreFlopStatisticsMock* preFlopStatistics;
    pokerGame::modeling::BettingContext* bettingContext;

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
        hole = new std::vector<pokerGame::card::Card>();
        sharedCards = new std::vector<pokerGame::card::Card>();
        handEvaluator = new test::HandStrengthEvaluatorMock();
        preFlopStatistics = new test::PreFlopStatisticsMock();
        probabilisticBettingStrategy = new playerController::bot::ProbabilisticBettingStrategy(handEvaluator, preFlopStatistics);
    }
    virtual void TearDown() {
        delete hole;
        delete sharedCards;
        delete probabilisticBettingStrategy;
        delete handEvaluator;
        delete preFlopStatistics;
        if (bettingContext) {
            delete bettingContext;
        }
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

TEST_F(ProbabilisticBettingStrategyTest, whenPreFlopIfHandStrengthIsHigherThanHighThresholdThenRaise) {
    initPreFlopHand();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    EXPECT_CALL(*preFlopStatistics, load(_));
    EXPECT_CALL(*preFlopStatistics, getWinningProbability(_, _)).WillOnce(Return(HIGHER_THAN_HIGH_THRESHOLD));
    pokerGame::Choice choice = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, *bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::RAISE, choice);
}

TEST_F(ProbabilisticBettingStrategyTest, whenPreFlopIfHandStrengthIsHigherThanHighThresholdNewBetEqualsSumOfMinBetAndBigBlind) {
    initPreFlopHand();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    EXPECT_CALL(*preFlopStatistics, load(_));
    EXPECT_CALL(*preFlopStatistics, getWinningProbability(_, _)).WillOnce(Return(HIGHER_THAN_HIGH_THRESHOLD));
    float newBet = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, *bettingContext, opponentModels).bet;
    ASSERT_EQ(A_BET+BIG_BLIND, newBet);
}

TEST_F(ProbabilisticBettingStrategyTest, whenPreFlopIfHandStrengthIsHigherThanLowThresholdThenCall) {
    initPreFlopHand();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    EXPECT_CALL(*preFlopStatistics, load(_));
    EXPECT_CALL(*preFlopStatistics, getWinningProbability(_, _)).WillOnce(Return(HIGHER_THAN_LOW_THRESHOLD));
    pokerGame::Choice choice = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, *bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::CALL, choice);
}

TEST_F(ProbabilisticBettingStrategyTest, whenPreFlopIfHandStrengthIsHigherThanLowThresholdNewBetEqualsMinBet) {
    initPreFlopHand();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    EXPECT_CALL(*preFlopStatistics, load(_));
    EXPECT_CALL(*preFlopStatistics, getWinningProbability(_, _)).WillOnce(Return(HIGHER_THAN_LOW_THRESHOLD));
    float newBet = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, *bettingContext, opponentModels).bet;
    ASSERT_EQ(A_BET, newBet);
}

TEST_F(ProbabilisticBettingStrategyTest, whenPreFlopIfHandStrengthIsLowerThanLowThresholdThenFold) {
    initPreFlopHand();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    EXPECT_CALL(*preFlopStatistics, load(_));
    EXPECT_CALL(*preFlopStatistics, getWinningProbability(_, _)).WillOnce(Return(LOWER_THAN_LOW_THRESHOLD));
    pokerGame::Choice choice = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, *bettingContext, opponentModels).choice;
    ASSERT_EQ(pokerGame::FOLD, choice);
}

TEST_F(ProbabilisticBettingStrategyTest, whenPreFlopIfHandStrengthIsLowerThanLowThresholdNewBetEqualsZero) {
    initPreFlopHand();
    bettingContext = new pokerGame::modeling::BettingContext(A_BETTING_ROUND_TYPE, NUMBER_OF_RAISES, NUMBER_OF_PLAYERS, A_BET, BIG_BLIND);
    EXPECT_CALL(*preFlopStatistics, load(_));
    EXPECT_CALL(*preFlopStatistics, getWinningProbability(_, _)).WillOnce(Return(LOWER_THAN_LOW_THRESHOLD));
    float newBet = probabilisticBettingStrategy->makeDecision(*hole, *sharedCards, *bettingContext, opponentModels).bet;
    ASSERT_EQ(0, newBet);
}

void ProbabilisticBettingStrategyTest::initPreFlopHand() {
    pokerGame::card::Card c1(2, pokerGame::card::SPADE);
    pokerGame::card::Card c2(3, pokerGame::card::HEART);
    hole->push_back(c1);
    hole->push_back(c2);
}

void ProbabilisticBettingStrategyTest::initPostFlopHand() {
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
