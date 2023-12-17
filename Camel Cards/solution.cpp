#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using std::vector;
using std::string;
using std::map;

void parsePuzzle(vector<string>& puzzle, map<string, int>* bets);
bool isCharNum(const char& input);

int main()
{
	std::ifstream puzzleFile;
	string line;
	vector<string> puzzleInput;
	map<string, int> hand_bids;

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

	parsePuzzle(puzzleInput, &hand_bids);

	return 0;
}

void parsePuzzle(vector<string>& puzzle, map<string, int>* bets)
{
	string hand = "";
	string bid = "";
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
				bets->emplace(hand, std::stoi(bid));
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