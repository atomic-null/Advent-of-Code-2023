#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;

void parsePuzzle(vector<string>& puzzle, vector<vector<string>>* bets);
int getCardRank(string hand);
bool isCharNum(const char& input);

int main()
{
	std::ifstream puzzleFile;
	string line;
	vector<string> puzzleInput;
	vector<vector<string>> hand_bids;

	puzzleFile.open("test_input.txt");
	if (puzzleFile.is_open())
	{
		while (std::getline(puzzleFile, line))
		{
			puzzleInput.push_back(line);
		}
		puzzleFile.close();
	}
	else std::cout << "Unable to open file.\n";

	parsePuzzle(puzzleInput, &hand_bids);

	return 0;
}

void parsePuzzle(vector<string>& puzzle, vector<vector<string>>* bets)
{
	string hand = "";
	string bid = "";
	vector<string> bet;
	bool isHand = true;

	for (int i = 0; i < puzzle.size(); ++i)
	{
		for (int j = 0; j < puzzle[i].size() + 1; ++j)
		{
			if (puzzle[i][j] == ' ')
			{
				isHand = false;
				continue;
			}

			if (j >= puzzle[i].size())
			{
				bet.push_back(hand);
				bet.push_back(bid);
				bet.push_back(std::to_string(getCardRank(hand)));
				hand = "";
				bid = "";
				isHand = true;
				break;
			}

			if (isHand)
			{
				hand.push_back(puzzle[i][j]);
			}

			if (!isHand)
			{
				bid.push_back(puzzle[i][j]);
			}
		}
		bets->push_back(bet);
		bet.clear();
	}	
}

int getCardRank(string hand)
{
	int rank = 0;
	int setIndex = 0;
	int cardCount = 0;
	vector<int> cardNumCounts(5);

	std::cout << hand << '\n';

	std::sort(hand.begin(), hand.end());

	std::cout << hand << '\n';

	for (int i = 0; i < hand.size(); ++i)
	{
		if (i == hand.size() - 1)
		{
			cardCount = cardNumCounts[setIndex];
			cardCount++;
			cardNumCounts[setIndex] = cardCount;
			cardCount = 0;
			continue;
		}

		if (hand[i] == hand[i + 1])
		{
			cardCount = cardNumCounts[setIndex];
			cardCount++;
			cardNumCounts[setIndex] = cardCount;
		}

		if (hand[i] != hand[i + 1])
		{
			cardCount = cardNumCounts[setIndex];
			cardCount++;
			cardNumCounts[setIndex] = cardCount;
			setIndex++;
			cardCount = 0;
		}

	}
	
	if (cardNumCounts[0] == 5)
	{
		rank = 1; //Five of a kind
	}
	else if (cardNumCounts[0] == 4 || cardNumCounts[1] == 4)
	{
		rank = 2; //Four of a kind
	}
	else if ((cardNumCounts[0] == 3 && cardNumCounts[1] == 2) ||
			 (cardNumCounts[0] == 2 && cardNumCounts[1] == 3))
	{
		rank = 3; //Full house
	}
	else if ((cardNumCounts[0] == 3 && cardNumCounts[1] == 1) ||
			 (cardNumCounts[0] == 1 && cardNumCounts[1] == 3) ||
			 (cardNumCounts[1] == 1 && cardNumCounts[2] == 3))
	{
		rank = 4; //Three of a kind
	}
	else if ((cardNumCounts[0] == 2 && cardNumCounts[1] == 2 && cardNumCounts[2] == 1) ||
		     (cardNumCounts[0] == 1 && cardNumCounts[1] == 2 && cardNumCounts[2] == 2) ||
			 (cardNumCounts[0] == 2 && cardNumCounts[1] == 1 && cardNumCounts[2] == 2))
	{
		rank = 5; //Two pair
	}
	else if (cardNumCounts[0] == 2 || cardNumCounts[1] == 2 || 
			 cardNumCounts[2] == 2 || cardNumCounts[3] == 2)
	{
		rank = 6; //One pair
	}
	else
	{
		rank = 7; //High card
	}

	return rank;
}

//create compareHandRank

//create calculateTotalBidValue

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