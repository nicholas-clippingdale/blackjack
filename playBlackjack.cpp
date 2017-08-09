#include <cassert>

#include "Deck.h"
#include "Hand.h"

#include "Strategy.h"
#include "playBlackjack.h"

double playBlackjack(Deck &deck)
{
	assert(deck.getNumDecks() > 0 &&
           "There must be at least one deck in play");
	assert(deck.getNumCardsLeft() > 20 &&
		"There are less than twenty cards left in the shoe: decrease deck penetration");

	// Set the strategy guidlines
	bool takeSurrender{ false }; // Should the player ever surrender a hand?
	bool takeSplit{ true }; // Should the player ever split?
	bool takeDoubleDown{ true }; // Should the player ever double down?
	bool takeInsurance{ true }; // Should the player ever take insurance?
								// Note: This includes even money

	// Set the rules for each hand
	bool dealerHitSoft17{ false }; // Does the dealer hit a soft seventeen?
	bool doubleDownAfterSplit{ true }; // Can the player double down after a split?
	bool resplitAces{ true }; // Can the player split aces for a second time?
	bool peek{ true }; // Does the dealer deal themself two cards?
	bool lateSurrender{ false }; // Can the player only surrender after the dealer peeks?
								// Note: lateSurrender can only be true if peek is true.

	if (lateSurrender == true)
		assert(peek == true && "lateSurrender can only be true if peek is true");
		
	// Declare the player's and dealer's hands
	Hand playerHand, dealerHand;

	// Deal the first hands
	if (peek == true)
	{
		playerHand += deck.dealCard();
		dealerHand += deck.dealCard();
		playerHand += deck.dealCard();
		dealerHand += deck.dealCard();
	}
	else
	{
		playerHand += deck.dealCard();
		dealerHand += deck.dealCard();
		playerHand += deck.dealCard();
	}
	
	// Check for an early surrender
	if (takeSurrender == true && lateSurrender == false)
	{
		if (checkSurrender(playerHand, dealerHand, dealerHitSoft17) == true)
            return -0.5; // The player surrendered - return surrender
	}

	// The dealer peeks to check for a blackjack
	if (peek == true)
	{
		double peekOutcome = doPeek(deck, playerHand, dealerHand, takeInsurance);
		if (peekOutcome < 9.9)
            return peekOutcome; // The hand was resolved on the peek - return the outcome

		// Check for a late surrender
		if (takeSurrender == true && lateSurrender == true)
		{
			if (checkSurrender(playerHand, dealerHand, dealerHitSoft17) == true)
                return -0.5; // The player surrendered - return surrender
		}
	}
	// Peek is not true - The player checks for a blackjack
	else if (playerHand.checkBlackjack() == true)
	{
		dealerHand += deck.dealCard();
		if (dealerHand.checkBlackjack() == true)
            return 0.0; // Both the player and the dealer have a blackjack - return tie
		else
            return 1.5; // Only the player has a blackjack - return blackjack win
	}
	
	// Check for a split
	if (takeSplit == true && playerHand[0].getCardValue() == playerHand[1].getCardValue() &&
        checkSplit(playerHand, dealerHand) == true)
	{
		return checkSplitOutcome( doSplit(deck, playerHand, dealerHand, takeDoubleDown,
                                          resplitAces, doubleDownAfterSplit),
                                  deck, dealerHand, dealerHitSoft17 );
	}

	// Check for a double down
	if (takeDoubleDown == true && checkDoubleDown(playerHand, dealerHand) == true)
	{
		// Perform the double down
		playerHand.doDoubleDown(deck.dealCard());
		// Check if the player busted
		if (playerHand.getHandValue() > 21)
		{
			if (dealerHand.getInsurance() == true)
                return -2.5; // Player busted - return double down loss and insurance bet loss
			else
                return -2.0; // Player busted - return double down loss
		}
	}
    
    // A regular hand is played
    return regularPlay(deck, playerHand, dealerHand, dealerHitSoft17);
}
