#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "card.h"

int getTotalScratchCardPoints(const std::vector<std::string>& scratchCards);
void parseNumbers(const std::string& card, std::vector<int>* winningNums, std::vector<int>* elfNums);
bool isCharNum(const char& input);
int calculatePointValue(int currentPoints);
void createCardObjects(const std::vector<std::string>& scratchCards, std::vector<Card>& cards);
int calculateTotalScratchCards(std::vector<Card>& cards);

int main()
{
	std::ifstream puzzleFile;
	std::string line;
	std::vector<std::string> puzzleInput;
	std::vector<Card> cards;

	puzzleFile.open("puzzle_input.txt");
	if (puzzleFile.is_open())
	{
		while (std::getline(puzzleFile, line))
		{
			puzzleInput.push_back(line);
		}
		puzzleFile.close();
	}
	else std::cout << "Unable to open file.\n";

	std::cout << "The total scratch card points is " << getTotalScratchCardPoints(puzzleInput) << '\n';
	createCardObjects(puzzleInput, cards);
	std::cout << "The total number of scratch cards is " << calculateTotalScratchCards(cards) << '\n';

	return 0;
}

void createCardObjects(const std::vector<std::string>& scratchCards, std::vector<Card> &cards)
{
	int id = 0;
	std::vector<int> winningNumbers;
	std::vector<int> elfNumbers;

	for (int i = 0; i < scratchCards.size(); ++i)
	{
		++id;
		parseNumbers(scratchCards[i], &winningNumbers, &elfNumbers);
		Card temp(id, 1, winningNumbers, elfNumbers);
		cards.push_back(temp);
		winningNumbers.clear();
		elfNumbers.clear();
	}
}

int calculateTotalScratchCards(std::vector<Card>& cards)
{
	int totalNumOfCards = 0;
	int id = 0;
	std::vector<int> winningNumbers;
	std::vector<int> elfNumbers;
	std::vector<int> idToAdd;

	for (int i = 0; i < cards.size(); ++i)
	{
		/*Finding the IDs of the cards that will have more than one copy.*/
		id++;
		int tempID = id;
		for (int j = 0; j < cards[i].getWinningNumbers().size(); ++j)
		{
			winningNumbers = cards[i].getWinningNumbers();
			elfNumbers = cards[i].getPlayerNumbers();
			for (int k = 0; k < cards[i].getPlayerNumbers().size(); ++k)
			{
				if (winningNumbers[j] == elfNumbers[k])
				{
					if (i < cards.size())
					{
						idToAdd.push_back(cards[tempID].getID());
						tempID++;
					}
				}
			}
			winningNumbers.clear();
			elfNumbers.clear();
		}

		/*Adding quantity to the cards that will have more than one copy.*/
		int copiesOfCard = cards[i].getQuantity();
		int index = 0;
		while (copiesOfCard > 0)
		{
			if (idToAdd.empty()) break;
			for (index = 0; index <= idToAdd.size() - 1; ++index)
			{
				cards[idToAdd[index] - 1].addToQuantity(1);
			}
			copiesOfCard--;
		}
		idToAdd.clear();
		tempID = 0;
	}
	for (int i = 0; i < cards.size(); ++i)
	{
		totalNumOfCards += cards[i].getQuantity();
	}

	return totalNumOfCards;
}

int getTotalScratchCardPoints(const std::vector<std::string> &scratchCards)
{
	int cardPoints = 0;
	int totalPoints = 0;
	std::vector<int> winningNumbers;
	std::vector<int> elfNumbers;

	for (int i = 0; i < scratchCards.size(); ++i)
	{
		parseNumbers(scratchCards[i], &winningNumbers, &elfNumbers);

		for (int j = 0; j < winningNumbers.size(); ++j)
		{
			for (int k = 0; k < elfNumbers.size(); ++k)
			{
				if (winningNumbers[j] == elfNumbers[k])
				{
					cardPoints = calculatePointValue(cardPoints);
				}
			}
		}
		totalPoints += cardPoints;
		cardPoints = 0;
		winningNumbers.clear();
		elfNumbers.clear();
	}
	return totalPoints;
}

void parseNumbers(const std::string &card, std::vector<int> *winningNums, std::vector<int> *elfNums)
{
	bool searchingForWinningNumbers = false;
	bool searchingForElfNumbers = false;
	std::string number = "";

	for (int i = 0; i < card.size(); ++i)
	{
		if (card[i] == ':') searchingForWinningNumbers = true;
		if (card[i] == '|')
		{
			searchingForWinningNumbers = false;
			searchingForElfNumbers = true;
		}

		if (isCharNum(card[i]) && searchingForWinningNumbers)
		{
			number.push_back(card[i]);

			if (i >= card.size())
			{
				winningNums->push_back(std::stoi(number));
				number = "";
			}

			if (card[i + 1] == ' ')
			{
				winningNums->push_back(std::stoi(number));
				number = "";
			}
		}

		if (isCharNum(card[i]) && searchingForElfNumbers)
		{
			number.push_back(card[i]);

			if (i >= card.size() - 1)
			{
				elfNums->push_back(std::stoi(number));
				number = "";
			}

			if (card[i + 1] == ' ')
			{
				elfNums->push_back(std::stoi(number));
				number = "";
			}
		}
	}
}

bool isCharNum(const char& input)
{
	if (input == '0' || input == '1' || input == '2' ||
		input == '3' || input == '4' || input == '5' ||
		input == '6' || input == '7' || input == '8' ||
		input == '9')
	{
		return true;
	}
	else return false;
}

int calculatePointValue(int currentPoints)
{
	if (currentPoints < 1) return 1;
	else return currentPoints * 2;
}