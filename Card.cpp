#include <iostream>

#include "Card.h"

Card::Card(CardRank rank, CardSuit suit)
	: m_rank(rank), m_suit(suit)
{

}

int Card::getCardValue() const
{
	switch (m_rank)
	{
        case RANK_1:        return 1;
        case RANK_2:		return 2;
        case RANK_3:		return 3;
        case RANK_4:		return 4;
        case RANK_5:		return 5;
        case RANK_6:		return 6;
        case RANK_7:		return 7;
        case RANK_8:		return 8;
        case RANK_9:		return 9;
        case RANK_10:		return 10;
        case RANK_JACK:		return 10;
        case RANK_QUEEN:	return 10;
        case RANK_KING:		return 10;
        case RANK_ACE:		return 11;
        default:            std::cerr <<
            "\ngetCardValue() received a card without a rank\n";
            return 0;
	}
}

char Card::getCardSuit() const
{
	switch (m_suit)
	{
        case SUIT_CLUB:     return 'C';
        case SUIT_DIAMOND:  return 'D';
        case SUIT_HEART:    return 'H';
        case SUIT_SPADE:    return 'S';
        default:            std::cerr <<
            "\ngetCardSuit() received a card without a suit\n";
            return '!';
	}
}

std::ostream& operator<<(std::ostream &out, const Card &card)
{
    out << card.getCardValue() << card.getCardSuit();
    return out;
}

bool operator==(const Card &card1, const Card &card2)
{
    return card1.getCardValue() == card2.getCardValue();
}

bool operator!=(const Card &card1, const Card &card2)
{
    return !(card1 == card2);
}
