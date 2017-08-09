#include <iostream>
#include <vector>
#include <cassert>

#include "Card.h"
#include "Deck.h"
#include "Hand.h"

#include "Strategy.h"
#include "playBlackjack.h"

std::vector<Hand> doSplit(Deck &deck, Hand &playerHand, Hand &dealerHand,
                         bool takeDoubleDown, bool resplitAces, bool doubleDownAfterSplit)
{
	assert(deck.getNumDecks() > 0 &&
           "doSplit() requires at least one deck in play");
	assert(playerHand.getNumCards() == 2 &&
           "doSlpit() requires the player's hand to have two cards");
	assert((dealerHand.getNumCards() == 1 || dealerHand.getNumCards() == 2) &&
		"doSurrender() requires one or two cards in the dealer's hand");
	
    // The first split has been taken: Declare the split vector
    std::vector<Hand> split{ Hand(std::vector<Card> { playerHand[0] }),
        Hand(std::vector<Card> { playerHand[1] }) };
    
    // Play the first hand of the first split
    split[0] += deck.dealCard();
    // Check for another pair and for another split
    if (split[0][0] == split[0][1] && checkSplit(split[0], dealerHand) == true &&
        ((split[0][0].getCardValue() == 11 && resplitAces == true) || split[0][0].getCardValue() != 11))
    {
        split.push_back( Hand(std::vector<Card> { split[0][1] }) );
        split[0] = Hand(std::vector<Card> { split[0][0] });
        
        // Play the first hand of the second split
        split[0] += deck.dealCard();
        // Check if a double down is wanted
        if (takeDoubleDown == true && doubleDownAfterSplit == true &&
            checkDoubleDown(split[0], dealerHand) == true)
            split[0].doDoubleDown(deck.dealCard());
        else // Regular play
            split[0] = playHand(deck, split[0], dealerHand);
        
        // Play the second hand of the second split
        split[2] += deck.dealCard();
        // Check if a double down is wanted
        if (takeDoubleDown == true && doubleDownAfterSplit == true &&
            checkDoubleDown(split[2], dealerHand) == true)
            split[2].doDoubleDown(deck.dealCard());
        else // Regular play
            split[2] = playHand(deck, split[2], dealerHand);
    }
    else // A second split of the first hand was not possible or wanted
    {
        // Check if a double down is wanted
        if (takeDoubleDown == true && doubleDownAfterSplit == true &&
            checkDoubleDown(split[0], dealerHand) == true)
            split[0].doDoubleDown(deck.dealCard());
        else // Regular play
            split[0] = playHand(deck, split[0], dealerHand);
    }
    
    // Play the second hand of the first split
    split[1] += deck.dealCard();
    // Check for another pair and for another split
    if (split[1][0] == split[1][1] && checkSplit(split[1], dealerHand) == true &&
        ((split[1][0].getCardValue() == 11 && resplitAces == true) || split[1][0].getCardValue() != 11))
    {
        split.push_back( Hand(std::vector<Card> { split[1][1] }) );
        split[1] = Hand(std::vector<Card> { split[1][0] });
        
        // Play the first hand of the second split
        split[1] += deck.dealCard();
        // Check if a double down is wanted
        if (takeDoubleDown == true && doubleDownAfterSplit == true &&
            checkDoubleDown(split[1], dealerHand) == true)
            split[1].doDoubleDown(deck.dealCard());
        else // Regular play
            split[1] = playHand(deck, split[1], dealerHand);
        
        // Play the second hand of the second split
        unsigned long lastSplitIndex{ split.size() - 1 };
        split[lastSplitIndex] += deck.dealCard();
        // Check if a double down is wanted
        if (takeDoubleDown == true && doubleDownAfterSplit == true &&
            checkDoubleDown(split[lastSplitIndex], dealerHand) == true)
            split[lastSplitIndex].doDoubleDown(deck.dealCard());
        else // Regular play
            split[lastSplitIndex] = playHand(deck, split[lastSplitIndex], dealerHand);
    }
    else // A second split of the first hand was not possible or wanted
    {
        // Check if a double down is wanted
        if (takeDoubleDown == true && doubleDownAfterSplit == true &&
            checkDoubleDown(split[1], dealerHand) == true)
            split[1].doDoubleDown(deck.dealCard());
        else // Regular play
            split[1] = playHand(deck, split[1], dealerHand);
    }
    
    return split;
}
