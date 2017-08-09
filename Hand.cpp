#include <iostream>
#include <vector>
#include <cassert>

#include "Hand.h"

Hand::Hand(std::vector<Card> hand)
	: m_hand(hand)
{
    m_numCards = 0;
    m_handValue = 0;
    for (const auto &card : hand)
    {
        m_handValue += card.getCardValue();
        ++m_numCards;
    }
    
    m_doubledDown = false;
    m_insured = false;
}

bool Hand::checkBlackjack() const
{
	assert(m_numCards == 2 &&
           "checkBlackjack() requires a hand with two cards");

	if (m_handValue == 21)
		return true;
	else
		return false;
}

int Hand::checkAces() const
{
    assert(m_numCards > 0 &&
           "checkAces() requires a hand with at least one card");
    
    for (int index = 0; index < m_numCards; ++index)
    {
        if (m_hand[index].getCardValue() == 11)
            return index;
    }

	return -1;
}

void Hand::changeAce(const int &index)
{
    if (index != -1)
    {
        assert(index >= 0 && index <= m_numCards &&
               "changeAce() requires an index within the number of cards");
        assert(m_hand[index].getCardValue() == 11 &&
               "changeAce() requires a card valued at eleven");
        
        switch (m_hand[index].getCardSuit())
        {
            case 'C':
                m_hand[index] =
                Card{ Card::CardRank::RANK_1, Card::CardSuit::SUIT_CLUB };
                break;
            case 'H':
                m_hand[index] =
                Card{ Card::CardRank::RANK_1, Card::CardSuit::SUIT_HEART };
                break;
            case 'S':
                m_hand[index] =
                Card{ Card::CardRank::RANK_1, Card::CardSuit::SUIT_SPADE };
                break;
            case 'D':
                m_hand[index] =
                Card{ Card::CardRank::RANK_1, Card::CardSuit::SUIT_DIAMOND };
                break;
            default:
                std::cerr << "\nchangeAce() received a card without a suit\n";
                break;
        }
        
        m_handValue -= 10;
    }
}

void Hand::doDoubleDown(const Card &card)
{
    assert(m_numCards == 2 &&
           "doDoubleDown() requires two cards in the player's hand");
    
    m_hand.push_back(card);
    m_handValue += card.getCardValue();
    ++m_numCards;
    m_doubledDown = true;
    
    // Check if the player busted and still has an ace valued at eleven
    // If they do, change the Ace's value to one
    if (m_handValue > 21)
    {
        changeAce(checkAces());
    }
}

void Hand::doInsurance()
{
    assert(m_numCards == 2 &&
           "doInsurance() requires the dealer have two cards");
    
    m_insured = true;
}

const Card& Hand::getDealerTopCard() const
{
    assert((m_numCards == 1 || m_numCards == 2) &&
           "getDealerTopCard() requires a hand of only one or two cards");
    
    if (m_numCards == 1)
        return m_hand[0];
    else
        return m_hand[1];
}

std::ostream& operator<<(std::ostream &out, const Hand&hand)
{
    for (const auto &card : hand.m_hand)
    {
        out << card.getCardValue() << card.getCardSuit() << ' ';
    }
    
    return out;
}

Hand Hand::operator+=(const Card &card)
{
    ++m_numCards;
    m_handValue += card.getCardValue();
    
    this -> m_hand.push_back(card);
    return *this;
}

Card& Hand::operator[](const int index)
{
    assert(index >= 0 && index <= m_numCards &&
           "Hand[] is trying to access an index outside of the hand vector");
    
    return m_hand[index];
}
