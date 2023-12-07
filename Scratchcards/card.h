#pragma once
#include <vector>

class Card
{
private:
	int _id = 0;
	int _quantity = 0;
	std::vector<int> _winningNumbers;
	std::vector<int> _playerNumbers;

public:
	Card(int id, int quantity, std::vector<int> winningNumbers, std::vector<int> playerNumbers);
	int getID() { return _id; }
	int getQuantity() { return _quantity; }
	std::vector<int> getWinningNumbers() { return _winningNumbers; }
	std::vector<int> getPlayerNumbers() { return _playerNumbers; }
	void setQuantity(int num) { _quantity = num; }
	void addToQuantity(int num);
};
