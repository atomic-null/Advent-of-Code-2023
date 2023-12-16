#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using std::vector;
using std::string;
using std::map;

void parsePuzzle(vector<string>& puzzle, map<int, int>* races);
int chargeBoat(int time);
int distanceTravelled(int speed, int timeRemaining);
bool isCharNum(const char& input);

int main()
{
	std::ifstream puzzleFile;
	string line;
	vector<string> puzzleInput;
	map<int, int> races_TimeDistance;

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

	parsePuzzle(puzzleInput, &races_TimeDistance);

	return 0;
}

int chargeBoat(int time)
{
	int speed = 0;
	speed += time;
	return speed;
}

int distanceTravelled(int speed, int timeRemaining)
{
	return speed * timeRemaining;
}

int getMarginOfError(map<int, int>* races)
{
	int raceTime = 0;
	int recordDistance = 0;
	int boatSpeed = 0;
	int boatTimeRemaining = 0;
	int marginOfError = 0;

	for (auto it = races->begin(); it != races->end(); ++it)
	{
		raceTime= it->first;
		recordDistance = it->second;

		for (int boatTime = 0; boatTime < raceTime; ++boatTime)
		{
			boatSpeed = chargeBoat(boatTime);
			boatTimeRemaining = 
			distanceTravelled(, )
		}
	}

	return 0;
}
void parsePuzzle(vector<string>& puzzle, map<int, int>* races)
{
	string time = "";
	string distance = "";
	vector<int> times;
	vector<int> distances;

	for (int i = 0; i < puzzle.size(); ++i)
	{
		for (int j = 0; j < puzzle[i].size() + 1; ++j)
		{
			if (i == 0 && j >= puzzle[i].size())
			{
				times.push_back(std::stoi(time));
				break;
			}
			if (i == 0 && isCharNum(puzzle[i][j]))
			{
				time.push_back(puzzle[i][j]);
			}
			if (i == 0 && !isCharNum(puzzle[i][j]) && time != "")
			{
				times.push_back(std::stoi(time));
				time = "";
			}

			if (i == 1 && j >= puzzle[i].size())
			{
				distances.push_back(std::stoi(distance));
				break;
			}
			if (i == 1 && isCharNum(puzzle[i][j]))
			{
				distance.push_back(puzzle[i][j]);
			}
			if (i == 1 && !isCharNum(puzzle[i][j]) && distance != "")
			{
				distances.push_back(std::stoi(distance));
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