/**
    The Deck class constructs a vector containing cards
    It can be composed of any positive integer multiple of standard
        52-card decks
    As cards are dealt, the vector remains the same, an index integer
        keeps track of which is the top card
    
    m_cardIndex is the vector index of the next card, it indicates
        which card will be dealt next
    m_numDecks is the number of 52-card decks the object is composed of
    m_runningCount and m_trueCount are values required for the Hi/Lo
        card counting system
 
    The constructor defaults to an object made up of no decks
 
    getRandomNumber() and swapCard() are used to shuffle the deck
 
    Nicholas Clippingdale
    Version 1.0
    28th July 2017
 */

#pragma once

#include <vector>

#include "Card.h"

class Deck
{
private:
	std::vector<Card> m_deck;
	int m_cardIndex;
    int m_numCardsLeft;
	int m_numDecks;
	int m_runningCount;
	int m_trueCount;

	static int getRandomNumber(int min, int max);
	static void swapCard(Card &a, Card &b);

public:
	Deck(int numDecks = 0);

	void shuffleDeck();
	const Card& dealCard();
    
    int getNumDecks() const { return m_numDecks; };
    int getIndex() const { return m_cardIndex; };
    int getRunningCount() const { return m_runningCount; };
    int getTrueCount() const { return m_trueCount; };
    int getNumCardsLeft() const { return m_numCardsLeft; };
    
    friend std::ostream& operator<<(std::ostream &out, const Deck &deck);
};
