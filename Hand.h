/**
    The hand class constructs a vector containing a number of cards
 
    m_doubledDown is a boolean variable decclaring if this, as the
        player's hand, has been doubled down
    m_Insured is a boolean variable declaring if this, as the dealer's
        hand, has been insured against
 
    The constructor defaults to a hand made up of no cards
 
    checkAces() returns the index of the first Ace valued at eleven
        If it cannot find any, it will return -1
    changeAce() takes an index and changes the value of the corresponding
        Ace from eleven to one
        If an index is passed which does not correspond to an Ace valued
        at eleven, nothing will happen
    doDoubleDown() performs a double down of the player's hand
        This involves dealing one card and doubling the player's stake
    doInsurance() insures the dealer's hand against a blackjack
        This simply involves changing m_insured
 
    getDealerTopCard() returns the second card in the hand if it is a
        peek game and the first and only card if it is a no-peek game
 
    The overloaded += operator adds another card to the vector
    The overloaded [] operator works like any vector and begins its
        indices at zero
 
    Nicholas Clippingdale
    Version 1.0
    28th July 2017
 */

#pragma once

#include <vector>

#include "Card.h"
#include "Deck.h"

class Hand
{
private:
	std::vector<Card> m_hand;
	int m_numCards;
    int m_handValue;
    bool m_doubledDown;
    bool m_insured;

public:
	Hand(std::vector<Card> hand = {});

	bool checkBlackjack() const;
	int checkAces() const;
    void changeAce(const int &index);
    void doDoubleDown(const Card &card);
    void doInsurance();
    
    int getHandValue() const { return m_handValue; };
    int getNumCards() const { return m_numCards; };
    bool getDoubleDown() const { return m_doubledDown; };
    bool getInsurance() const { return m_insured; };
    const Card& getDealerTopCard() const;
    
    friend std::ostream& operator<<(std::ostream &out, const Hand &hand);
    Hand operator+=(const Card &card);
    Card& operator[](const int index);
};
