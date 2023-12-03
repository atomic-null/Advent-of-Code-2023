#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <regex>

int getSumOfValidGames(const std::vector<std::string>& games, const std::map<std::string, int>& cubeCombos);

int main()
{
	std::ifstream puzzleFile;
	std::string line;
	std::vector<std::string> puzzleInput;
	std::map<std::string, int> gameCubes;

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

	gameCubes["red"] = 12;
	gameCubes["green"] = 13;
	gameCubes["blue"] = 14;

	std::cout << "Sum of valid game IDs: " << getSumOfValidGames(puzzleInput, gameCubes) << '\n';

	return 0;
}

int getSumOfValidGames(const std::vector<std::string>& games, const std::map<std::string, int>& cubeCombos)
{
	int gameID = 0;
	int sum = 0;
	bool isValid = false;
	std::regex findGameID("[[:digit:]]+(?! Game)");
	std::regex findRed("[[:digit:]]+(?= red)");
	std::regex findGreen("[[:digit:]]+(?= green)");
	std::regex findBlue("[[:digit:]]+(?= blue)");
	std::smatch match;
	std::regex_iterator<std::string::const_iterator> end = std::sregex_iterator();
	int validCount = 0;

	for (int i = 0; i < games.size(); i++)
	{
		std::cout << "\nLine Number: " << i + 1 << std::endl;
		//Finding the number of red cubes and then seeing if that number is less than what is in the cubeCombo.
		std::regex_iterator<std::string::const_iterator> it = std::sregex_iterator(games[i].begin(), games[i].end(), findRed);
		for (it; it != end; it++)
		{
			match = *it;
			std::cout << "red num = " << match.str() << '\n';
			if (std::stoi(match.str()) <= cubeCombos.at("red")) isValid = true;
			else
			{
				isValid = false; //If at anytime we find a invalid red value, we stop searching.
				break;
			}
		}
		if (!isValid) continue; //If at anytime we find a invalid game value, we move onto the next game.

		//Finding the number of green cubes and then seeing if that number is less than what is in the cubeCombo.
		it = std::sregex_iterator(games[i].begin(), games[i].end(), findGreen);
		for (it; it != end; it++)
		{
			match = *it;
			std::cout << "green num = " << match.str() << '\n';
			if (std::stoi(match.str()) <= cubeCombos.at("green")) isValid = true;
			else
			{
				isValid = false;
				break; //If at anytime we find a invalid green value, we stop searching.
			}
		}
		if (!isValid) continue; //If at anytime we find a invalid game value, we move onto the next game.

		//Finding the number of blue cubes and then seeing if that number is less than what is in the cubeCombo.
		it = std::sregex_iterator(games[i].begin(), games[i].end(), findBlue);
		for (it; it != end; it++)
		{
			match = *it;
			std::cout << "blue num = " << match.str() << '\n';
			if (std::stoi(match.str()) <= cubeCombos.at("blue")) isValid = true;
			else
			{
				isValid = false;
				break; //If at anytime we find a invalid blue value, we stop searching.
			}
		}
		if (!isValid) continue; //If at anytime we find a invalid game value, we move onto the next game.

		//If the game is indeed valid, then we will find it's game ID.
		if (isValid)
		{
			it = std::sregex_iterator(games[i].begin(), games[i].end(), findGameID);
			for (it; it != end; it++)
			{
				match = *it;
				gameID = std::stoi(match.str());
				std::cout << "gameID = " << gameID << '\n';
				break; //Only the first regex match is desired from this search.
			}
			validCount++;
		}
		sum += gameID;
	}
	std::cout << "Valid count: " << validCount << std::endl;
	return sum;
}