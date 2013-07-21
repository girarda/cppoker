/**-------------------------/// Player.cpp \\\---------------------------
 *
 * <b>Player.cpp</b>
 * @version : 1.0
 * @since : 2012 Dec 23
 *
 * @description :
 *     Implementation of the Player class.
 * @usage :
 *
 * @author : Alexandre Girard | girarda.92@gmail.com
 * @copyright girarda
 * @TODO :
 *
 *--------------------------\\\ Player.cpp ///---------------------------*/

#include "core/Player.h"

namespace pcore
{
    /**
     * \fn Player::Player(IPlayer playerImpl)
     */
    Player::Player(IPlayer *playerImpl): mPlayer(playerImpl), mHand(), mCurrentState(NOT_PLAYING), mMoney(0), mPot(0), mName("")
    {
    }

    void Player::setMoney(float newValue)
    {
        mMoney = newValue;
    }

    /**
     * \fn void Player::setName(std::string name)
     *
     * \brief Set the player's name
     */
    void Player::setName(std::string name)
    {
        mName = name;
    }

    void Player::startPlaying()
    {
        mCurrentState = PLAYING;
    }

    /**
     * \fn void Player::fold(bool fold)
     *
     * \brief Fold or unfold
     */
    void Player::fold()
    {
        mCurrentState =  FOLDED;
    }

    void Player::setupForNewTableTurn() {
        mCurrentState = PLAYING;
        clearPot();
    }

    /**
     * \fn void clearPot()
     *
     * \brief Clears the player's pot
     */
    void Player::clearPot()
    {
        mPot = 0;
    }

    /**
     * \fn Hand Player::getHand() const
     *
     * \brief Return te player's hand
     *
     * \return the player's hand
     */
    bool Player::hasBetterHand(const Player& other) const
    {
        return mHand > other.mHand;
    }

    float Player::getPot() const
    {
        return mPot;
    }

    /**
     * \fn bool Player::isPlaying const
     *
     * \brief Indicates whether the playing is playing or not
     *
     * \return true if the player is playing
     */
    bool Player::isPlaying() const
    {
        return mCurrentState == PLAYING;
    }

    /**
     * \fn bool Player::isFolded() const
     *
     * \brief Indicates whether the player has folded
     *
     * \return true if the player folded
     */
    bool Player::isFolded() const
    {
        return mCurrentState == FOLDED;
    }

    /**
     * \fn void addCard(const Card& card)
     *
     * \brief Add a new card in the player's hand
     */
    void Player::addCard(const Card& card)
    {
        mHand.addCard(card);
    }

    void Player::addToPot(float moneyToAdd)
    {
        mMoney -= moneyToAdd;
        mPot += moneyToAdd;
    }

    void Player::winMoney(float gainedMoney)
    {
        mMoney += gainedMoney;
    }

    Decision Player::makeDecision(float minBet)
    {
        Decision decision;
        bool decisionIsValid = false;
        while(!decisionIsValid)
        {
            decision = mPlayer->makeDecision(minBet);
            if (decision.choice == FOLD)
            {
                fold();
                decisionIsValid = true;
            }
            else 
            {
                float diffToAdd;
                if (decision.choice == CHECK)
                    diffToAdd = minBet - mPot;
                else
                    diffToAdd = decision.bet - mPot;
                if (mMoney >= diffToAdd)
                {
                    addToPot(diffToAdd);
                    decisionIsValid = true;
                }

            }
        }
        return decision;
    }

    /**
     * \fn void Player::seeDealer(std::string dealer) const
     *
     * \brief Announce the dealer 
     */
    void Player::seeDealer(const Player& dealer) const
    {
        mPlayer->seeDealer(dealer.mName);
    }

    void Player::seeBigBlind(const Player& player, float bigBlind) const
    {
        mPlayer->seeBigBlind(player.mName, bigBlind);
    }

    void Player::seeSmallBlind(const Player& player, float smallBlind) const
    {
        mPlayer->seeSmallBlind(player.mName, smallBlind);
    }

    /**
     * \fn void Player::seeWinner(const Player& winner) const
     *
     * \brief Announce the winner
     */
    void Player::seeWinner(const Player& winner) const
    {
        mPlayer->seeWinner(winner.mName);
    }

    /**
     * \fn void Player::seeOpponentCards(const Player& opponent) const
     *
     * \brief Announce the opponent's cards
     */
    void Player::seeOpponentCards(const Player& opponent) const
    {
        mPlayer->seeOpponentCards(opponent.mName, opponent.mHand);
    }

    /**
     * \fn void Player::seeOpponentMoney(const Player& opponent) const
     *
     * \brief Announce the opponent's money
     */
    void Player::seeOpponentMoney(const Player& opponent) const
    {
        mPlayer->seeOpponentMoney(opponent.mName, opponent.mMoney);
    }

    /**
     * \fn void Player::seeCards() const
     *
     * \brief Announce the player's cards
     */
    void Player::seeCards() const
    {
        mPlayer->seeCards(mHand);
    }

    /**
     * \fn void Player::seeMoney() const
     *
     * \brief Announce the player's money
     */
    void Player::seeMoney() const
    {
        mPlayer->seeMoney(mMoney);
    }

    Player::Player(IPlayer *playerImpl, Hand* hand): mPlayer(playerImpl), mHand(*hand), mCurrentState(NOT_PLAYING), mMoney(0), mPot(0), mName("")
    {
    }

    float Player::getMoney() const
    {
        return mMoney;
    }

    void Player::deliver(const std::string& msg)
    {
        mPlayer->deliver(msg);
    }
}
