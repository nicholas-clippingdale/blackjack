#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>

#include "Deck.h"

int Deck::getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

void Deck::swapCard(Card &a, Card &b)
{
	Card temp = a;
	a = b;
	b = temp;
}

Deck::Deck(int numDecks)
	: m_numDecks(numDecks)
{
	assert(numDecks >= 0 &&
           "numDecks must be a non-negative integer");
    
    m_cardIndex = 0;
    m_numCardsLeft = 52 * numDecks;
    m_runningCount = 0;
    m_trueCount = 0;

	int index{ 0 };
	m_deck.resize(52 * numDecks);
	for (int deck = 0; deck < numDecks; ++deck)
		for (int suit = 0; suit < Card::MAX_SUITS; ++suit)
			// Start at one to not include the ace twice
            // Default to including aces valued at eleven
			for (int rank = 1; rank < Card::MAX_RANKS; ++rank)
			{
				m_deck[index++] =
					Card(Card::CardRank(rank), Card::CardSuit(suit));
			}
}

void Deck::shuffleDeck()
{
	for (int index = 0; index < 52 * m_numDecks; ++index)
	{
		int swapIndex = getRandomNumber(0, static_cast<int>(m_deck.size()) - 1);
		swapCard(m_deck[index], m_deck[swapIndex]);
	}
    
	m_cardIndex = 0;
	m_runningCount = 0;
	m_trueCount = 0;
}

const Card& Deck::dealCard()
{
	assert(m_cardIndex < 52 * m_numDecks &&
		"dealCard() is trying to access an index outside of the deck");
	
    --m_numCardsLeft;
    
	switch (m_deck[m_cardIndex].getCardValue())
	{
        case 2:		++m_runningCount;   break;
        case 3:		++m_runningCount;   break;
        case 4:		++m_runningCount;   break;
        case 5:		++m_runningCount;   break;
        case 6:		++m_runningCount;   break;
        case 10:	--m_runningCount;   break;
        case 11:	--m_runningCount;   break;
        default:	break;
	}
    
    // Check if a single-deck game is being played
    // If it is, the true count is taken to be the running count
    if (m_numDecks == 1)
        m_trueCount = m_runningCount;
    else
    {
        double decksLeft{ static_cast<double>(m_numDecks) -
            (static_cast<double>(m_cardIndex) / 52.0) };
        double trueCount{ static_cast<double>(m_runningCount) / decksLeft };
        m_trueCount = static_cast<int>(trueCount);
    }

	return m_deck[m_cardIndex++];
}

std::ostream& operator<<(std::ostream &out, const Deck &deck)
{
    for (const auto &card : deck.m_deck)
    {
        out << card << ' ';
    }
    
    return out;
}
