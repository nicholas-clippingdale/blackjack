/**
    A card object can take on any form found in the standard
        52-card deck
 
    The constructor defaults to a card with no rank or suit
    
    The overloaded == and != operators only consider cards' rank
 
    Nicholas Clippingdale
    Version 1.0
    28th July 2017
 */

#pragma once

#include <iostream>

class Card
{
public:
	enum CardSuit
	{
		SUIT_CLUB,
		SUIT_DIAMOND,
		SUIT_HEART,
		SUIT_SPADE,
		MAX_SUITS,
		NO_CARD_SUIT
	};

	enum CardRank
	{
		RANK_1,
		RANK_2,
		RANK_3,
		RANK_4,
		RANK_5,
		RANK_6,
		RANK_7,
		RANK_8,
		RANK_9,
		RANK_10,
		RANK_JACK,
		RANK_QUEEN,
		RANK_KING,
		RANK_ACE,
		MAX_RANKS, // Note: This includes ace and one
		NO_CARD_RANK
	};

private:
	CardSuit m_suit;
	CardRank m_rank;

public:
	Card(CardRank rank = NO_CARD_RANK, CardSuit suit = NO_CARD_SUIT);
    
    int getCardValue() const;
    char getCardSuit() const;
    
    friend std::ostream& operator<<(std::ostream &out, const Card &card);
    friend bool operator==(const Card &card1, const Card &card2);
    friend bool operator!=(const Card &card1, const Card &card2);
};
