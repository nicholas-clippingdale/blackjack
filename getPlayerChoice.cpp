#include <iostream>

#include "Strategy.h"

char getPlayerChoice()
{
	char choice{ 'a' }; // Garbage value
	std::cout << "Would you like to (h)it or (s)tand? ";
	while (choice != 'h' || 's')
	{
		std::cin >> choice;
	}

	return choice;
}
