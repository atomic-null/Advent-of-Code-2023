#include "card.h"

Card::Card(int id, int quantity, std::vector<int> winningNumbers, std::vector<int> playerNumbers)
{
	_id = id;
	_quantity = quantity;
	_winningNumbers = winningNumbers;
	_playerNumbers = playerNumbers;
}

void Card::addToQuantity(int number)
{
	_quantity += number;
}