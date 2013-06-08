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

#include "src/core/Player.h"

namespace pcore
{
    /**
     * \fn Player::Player(IPlayer playerImpl)
     */
    Player::Player(IPlayer *playerImpl): mPlayer(playerImpl), mHand(), mBigBlind(false), mSmallBlind(false), mIsPlaying(false)
    {
    }

    /**
     * \fn void Player::setMoney(Money newValue)
     *
     * \brief Set the money value
     */
    void Player::setMoney(Money newValue)
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

    void Player::start()
    {
        mIsPlaying = true;
    }

    /**
     * \fn void Player::setFold(bool fold)
     *
     * \brief Fold or unfold
     */
    void Player::fold()
    {
        mIsFolded = true;
    }

    void Player::setupForNewTableTurn() {
        mIsFolded = false;
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

    /**
     * \fn Money getPot() const
     *
     * \brief Return the player's pot
     *
     * \return the player's pot
     */
    Money Player::getPot() const
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
        return mIsPlaying;
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
        return mIsFolded;
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

    /**
     * \fn void Player::addToPot(Money m)
     *
     * \brief Add money to the pot
     */
    void Player::addToPot(Money bet)
    {
        Money diffToAdd = bet - mPot;
        mMoney -= diffToAdd;
        mPot += diffToAdd;
    }

    void Player::winMoney(Money gainedMoney)
    {
        mMoney += gainedMoney;
    }

    /**
     * \fn Decision Player::makeDecision()
     *
     * \brief Ask the player to make a decision
     *
     * \return the player's decision
     */
    Decision Player::makeDecision()
    {
        return mPlayer->makeDecision();
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

    /**
     * \fn void Player::seeBigBlind(const Player& player, Money bigblind) const
     *
     * \brief Announce who the big blind is and its value.
     */
    void Player::seeBigBlind(const Player& player, Money bigBlind) const
    {
        mPlayer->seeBigBlind(player.mName, bigBlind);
    }

    /**
     * \fn void Player::seeSmallBlind(const Player& player, Money smallblind) const
     *
     * \brief Announce who the small blind is and its value.
     */
    void Player::seeSmallBlind(const Player& player, Money smallBlind) const
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
        mPlayer->seeMoney();
    }
}
