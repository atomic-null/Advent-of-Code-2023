#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;

void parsePuzzle(vector<string>& puzzle, vector<vector<string>>* bets);
bool comparePrimaryCardRank(string hand1, string hand2);
bool compareSecondaryCardRank(char first, char second);
void compareHandRank(vector<string>& hand1, vector<string>& hand2);
int calculateTotalBidValue(vector<vector<string>>& hands);

enum Card
{
	one = 1,
	two = 2,
	three = 3,
	four = 4,
	five = 5,
	six = 6,
	seven = 7,
	eight = 8,
	nine = 9,
	T = 10,
	J = 11,
	Q = 12,
	K = 13,
	A = 14
};

int main()
{
	std::ifstream puzzleFile;
	string line;
	vector<string> puzzleInput;
	vector<vector<string>> hand_bids;
	int totalWinnings = 0;

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

	for (int i = 0; i < hand_bids.size() - 1; ++i)
	{
		compareHandRank(hand_bids[i], hand_bids[i + 1]);
	}

	totalWinnings = calculateTotalBidValue(hand_bids);

	std::cout << "Total winnings are " << totalWinnings << '\n';

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
				bet.push_back(std::to_string(i + 1));
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

bool comparePrimaryCardRank(string hand1, string hand2)
{
	int hand1Rank = 0;
	int hand2Rank = 0;
	int setIndex = 0;
	int cardCount = 0;
	bool isFirstGreater = false;
	vector<int> cardNumCounts(5);

	std::sort(hand1.begin(), hand1.end());
	std::sort(hand2.begin(), hand2.end());

	for (int i = 0; i < hand1.size(); ++i)
	{
		if (i == hand1.size() - 1)
		{
			cardCount = cardNumCounts[setIndex];
			cardCount++;
			cardNumCounts[setIndex] = cardCount;
			cardCount = 0;
			continue;
		}

		if (hand1[i] == hand1[i + 1])
		{
			cardCount = cardNumCounts[setIndex];
			cardCount++;
			cardNumCounts[setIndex] = cardCount;
		}

		if (hand1[i] != hand1[i + 1])
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
		hand1Rank = 7; //Five of a kind
	}
	else if (cardNumCounts[0] == 4 || cardNumCounts[1] == 4)
	{
		hand1Rank = 6; //Four of a kind
	}
	else if ((cardNumCounts[0] == 3 && cardNumCounts[1] == 2) ||
			 (cardNumCounts[0] == 2 && cardNumCounts[1] == 3))
	{
		hand1Rank = 5; //Full house
	}
	else if ((cardNumCounts[0] == 3 && cardNumCounts[1] == 1) ||
			 (cardNumCounts[0] == 1 && cardNumCounts[1] == 3) ||
			 (cardNumCounts[1] == 1 && cardNumCounts[2] == 3))
	{
		hand1Rank = 4; //Three of a kind
	}
	else if ((cardNumCounts[0] == 2 && cardNumCounts[1] == 2 && cardNumCounts[2] == 1) ||
		     (cardNumCounts[0] == 1 && cardNumCounts[1] == 2 && cardNumCounts[2] == 2) ||
			 (cardNumCounts[0] == 2 && cardNumCounts[1] == 1 && cardNumCounts[2] == 2))
	{
		hand1Rank = 3; //Two pair
	}
	else if (cardNumCounts[0] == 2 || cardNumCounts[1] == 2 || 
			 cardNumCounts[2] == 2 || cardNumCounts[3] == 2)
	{
		hand1Rank = 2; //One pair
	}
	else
	{
		hand1Rank = 1; //High card
	}
	setIndex = 0;
	cardCount = 0;
	cardNumCounts[0] = 0;
	cardNumCounts[1] = 0;
	cardNumCounts[2] = 0;
	cardNumCounts[3] = 0;
	cardNumCounts[4] = 0;


	for (int i = 0; i < hand2.size(); ++i)
	{
		if (i == hand2.size() - 1)
		{
			cardCount = cardNumCounts[setIndex];
			cardCount++;
			cardNumCounts[setIndex] = cardCount;
			cardCount = 0;
			continue;
		}

		if (hand2[i] == hand2[i + 1])
		{
			cardCount = cardNumCounts[setIndex];
			cardCount++;
			cardNumCounts[setIndex] = cardCount;
		}

		if (hand2[i] != hand2[i + 1])
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
		hand2Rank = 7; //Five of a kind
	}
	else if (cardNumCounts[0] == 4 || cardNumCounts[1] == 4)
	{
		hand2Rank = 6; //Four of a kind
	}
	else if ((cardNumCounts[0] == 3 && cardNumCounts[1] == 2) ||
		(cardNumCounts[0] == 2 && cardNumCounts[1] == 3))
	{
		hand2Rank = 5; //Full house
	}
	else if ((cardNumCounts[0] == 3 && cardNumCounts[1] == 1) ||
		(cardNumCounts[0] == 1 && cardNumCounts[1] == 3) ||
		(cardNumCounts[1] == 1 && cardNumCounts[2] == 3))
	{
		hand2Rank = 4; //Three of a kind
	}
	else if ((cardNumCounts[0] == 2 && cardNumCounts[1] == 2 && cardNumCounts[2] == 1) ||
		(cardNumCounts[0] == 1 && cardNumCounts[1] == 2 && cardNumCounts[2] == 2) ||
		(cardNumCounts[0] == 2 && cardNumCounts[1] == 1 && cardNumCounts[2] == 2))
	{
		hand2Rank = 3; //Two pair
	}
	else if (cardNumCounts[0] == 2 || cardNumCounts[1] == 2 ||
		cardNumCounts[2] == 2 || cardNumCounts[3] == 2)
	{
		hand2Rank = 2; //One pair
	}
	else
	{
		hand2Rank = 1; //High card
	}

	if (hand1Rank > hand2Rank) isFirstGreater = true;
	if (hand1Rank < hand2Rank) isFirstGreater = false;

	return isFirstGreater;
}

bool compareSecondaryCardRank(char first, char second)
{
	bool isFirstGreater = false;
	int firstCard = 0;
	int secondCard = 0;

	switch (first)
	{
		case 'A':
			firstCard = Card::A;
			break;
		case 'K':
			firstCard = Card::K;
			break;
		case 'Q':
			firstCard = Card::Q;
			break;
		case 'J':
			firstCard = Card::J;
			break;
		case 'T':
			firstCard = Card::T;
			break;
		case '9':
			firstCard = Card::nine;
			break;
		case '8':
			firstCard = Card::eight;
			break;
		case '7':
			firstCard = Card::seven;
			break;
		case '6':
			firstCard = Card::six;
			break;
		case '5':
			firstCard = Card::five;
			break;
		case '4':
			firstCard = Card::four;
			break;
		case '3':
			firstCard = Card::three;
			break;
		case '2':
			firstCard = Card::two;
			break;
		case '1':
			firstCard = Card::one;
			break;
		default:
			firstCard = 0;
			break;
	}

	switch (second)
	{
		case 'A':
			secondCard = Card::A;
			break;
		case 'K':
			secondCard = Card::K;
			break;
		case 'Q':
			secondCard = Card::Q;
			break;
		case 'J':
			secondCard = Card::J;
			break;
		case 'T':
			secondCard = Card::T;
			break;
		case '9':
			secondCard = Card::nine;
			break;
		case '8':
			secondCard = Card::eight;
			break;
		case '7':
			secondCard = Card::seven;
			break;
		case '6':
			secondCard = Card::six;
			break;
		case '5':
			secondCard = Card::five;
			break;
		case '4':
			secondCard = Card::four;
			break;
		case '3':
			secondCard = Card::three;
			break;
		case '2':
			secondCard = Card::two;
			break;
		case '1':
			secondCard = Card::one;
			break;
		default:
			secondCard = 0;
			break;
	}

	if (firstCard > secondCard) isFirstGreater = true;
	if (firstCard < secondCard) isFirstGreater = false;

	return isFirstGreater;
}

void compareHandRank(vector<string> &hand1, vector<string> &hand2)
{
	int rankNum = 0;

	if (comparePrimaryCardRank(hand1[0], hand2[0]) && (hand1[2] <= hand2[2]))
	{
		rankNum = std::stoi(hand1[2]);
		rankNum++;
		hand1[2] = std::to_string(rankNum);

		rankNum = std::stoi(hand2[2]);
		rankNum--;
		hand2[2] = std::to_string(rankNum);

		rankNum = 0;
	}
	if (!comparePrimaryCardRank(hand1[0], hand2[0]) && (hand1[2] >= hand2[2]))
	{
		rankNum = std::stoi(hand2[2]);
		rankNum++;
		hand2[2] = std::to_string(rankNum);

		rankNum = std::stoi(hand1[2]);
		rankNum--;
		hand1[2] = std::to_string(rankNum);

		rankNum = 0;
	}

	for (int i = 0; i < hand1[0].size(); ++i)
	{
		if (hand1[2] == hand2[2])
		{
			if (compareSecondaryCardRank(hand1[0][i], hand2[0][i]))
			{
				rankNum = std::stoi(hand1[2]);
				rankNum++;
				hand1[2] = std::to_string(rankNum);

				rankNum = std::stoi(hand2[2]);
				rankNum--;
				hand2[2] = std::to_string(rankNum);

				rankNum = 0;
			}
			else
			{
				rankNum = std::stoi(hand2[2]);
				rankNum++;
				hand2[2] = std::to_string(rankNum);

				rankNum = std::stoi(hand1[2]);
				rankNum--;
				hand1[2] = std::to_string(rankNum);

				rankNum = 0;
			}
		}
	}
}

//create calculateTotalBidValue
int calculateTotalBidValue(vector<vector<string>>& hands)
{
	int totalValue = 0;
	int bid = 0;
	int rank = 0;

	for (int i = 0; i < hands.size(); ++i)
	{
		bid = std::stoi(hands[i][1]);
		rank = std::stoi(hands[i][2]);
		totalValue += (bid * rank);
	}

	return totalValue;
}