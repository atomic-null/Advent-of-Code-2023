#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using std::vector;
using std::string;
using std::map;

void parsePuzzle(vector<string>& puzzle, map<unsigned long long, unsigned long long>* races);
unsigned long long chargeBoat(unsigned long long time);
unsigned long long distanceTravelled(unsigned long long speed, unsigned long long timeRemaining);
unsigned long long getMarginOfErrorProduct(map<unsigned long long, unsigned long long>* races);
bool isCharNum(const char& input);

int main()
{
	std::ifstream puzzleFile;
	string line;
	vector<string> puzzleInput;
	map<unsigned long long, unsigned long long> races_TimeDistance;
	unsigned long long marginOfError = 0;
	unsigned long long marginOfErrorProduct = 0;

	puzzleFile.open("puzzle_input_p2.txt");
	if (puzzleFile.is_open())
	{
		while (std::getline(puzzleFile, line))
		{
			puzzleInput.push_back(line);
		}
		puzzleFile.close();
	}
	else std::cout << "Unable to open file.\n";

	parsePuzzle(puzzleInput, &races_TimeDistance);

	marginOfErrorProduct = getMarginOfErrorProduct(&races_TimeDistance);

	std::cout << "Margin of error product is " << marginOfErrorProduct << '\n';

	return 0;
}

unsigned long long chargeBoat(unsigned long long time)
{
	unsigned long long speed = 0;
	speed += time;
	return speed;
}

unsigned long long distanceTravelled(unsigned long long speed, unsigned long long timeRemaining)
{
	return speed * timeRemaining;
}

unsigned long long getMarginOfErrorProduct(map<unsigned long long, unsigned long long>* races)
{
	unsigned long long raceTime = 0;
	unsigned long long recordDistance = 0;
	unsigned long long boatSpeed = 0;
	unsigned long long boatTimeRemaining = 0;
	unsigned long long marginOfError = 0;
	unsigned long long marginOfErrorProduct = 0;

	for (auto it = races->begin(); it != races->end(); ++it)
	{
		raceTime= it->first;
		recordDistance = it->second;

		for (int boatTime = 0; boatTime < raceTime; ++boatTime)
		{
			boatSpeed = chargeBoat(boatTime);
			boatTimeRemaining = raceTime - boatSpeed;
			if (distanceTravelled(boatSpeed, boatTimeRemaining) > recordDistance)
			{
				marginOfError++;
			}
		}
		if (marginOfErrorProduct == 0)
		{
			marginOfErrorProduct = marginOfError;
		}
		else marginOfErrorProduct *= marginOfError;
		
		marginOfError = 0;
	}

	return marginOfErrorProduct;
}
void parsePuzzle(vector<string>& puzzle, map<unsigned long long, unsigned long long>* races)
{
	string time = "";
	string distance = "";
	vector<unsigned long long> times;
	vector<unsigned long long> distances;

	for (int i = 0; i < puzzle.size(); ++i)
	{
		for (int j = 0; j < puzzle[i].size() + 1; ++j)
		{
			if (i == 0 && j >= puzzle[i].size())
			{
				times.push_back(std::stoull(time));
				break;
			}
			if (i == 0 && isCharNum(puzzle[i][j]))
			{
				time.push_back(puzzle[i][j]);
			}
			if (i == 0 && !isCharNum(puzzle[i][j]) && time != "")
			{
				times.push_back(std::stoull(time));
				time = "";
			}

			if (i == 1 && j >= puzzle[i].size())
			{
				distances.push_back(std::stoull(distance));
				break;
			}
			if (i == 1 && isCharNum(puzzle[i][j]))
			{
				distance.push_back(puzzle[i][j]);
			}
			if (i == 1 && !isCharNum(puzzle[i][j]) && distance != "")
			{
				distances.push_back(std::stoull(distance));
				distance = "";
			}
		}
	}

	for (int i = 0; i < times.size(); ++i)
	{
		races->emplace(times[i], distances[i]);
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