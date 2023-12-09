#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "almanac.h"

using std::vector;
using std::string;

void parseAlmanac(vector<string> &puzzle, Almanac &almanac);
vector<unsigned long> expandSeeds(Almanac& almanac);
unsigned long convertSourceToDestination(const vector<vector<unsigned long>>& legend, const unsigned long* source);
bool isCharNum(const char &input);

int main()
{
	std::ifstream puzzleFile;
	string line;
	vector<string> puzzleInput;
	Almanac almanac;
	vector<unsigned long> seeds;
	unsigned long soilNum = 0;
	unsigned long fertilizerNum = 0;
	unsigned long waterNum = 0;
	unsigned long lightNum = 0;
	unsigned long temperatureNum = 0;
	unsigned long humidityNum = 0;
	unsigned long locationNum = 0;
	unsigned long lowestLocationNum = 0;

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

	parseAlmanac(puzzleInput, almanac);
	seeds = expandSeeds(almanac);

	for (int i = 0; i < seeds.size(); ++i)
	{
		soilNum = convertSourceToDestination(almanac.seed_to_soil, &seeds[i]);
		fertilizerNum = convertSourceToDestination(almanac.soil_to_fertilizer, &soilNum);
		waterNum = convertSourceToDestination(almanac.fertilizer_to_water, &fertilizerNum);
		lightNum = convertSourceToDestination(almanac.water_to_light, &waterNum);
		temperatureNum = convertSourceToDestination(almanac.light_to_temperature, &lightNum);
		humidityNum = convertSourceToDestination(almanac.temperature_to_humidity, &temperatureNum);
		locationNum = convertSourceToDestination(almanac.humidity_to_location, &humidityNum);
		
		if (i == 0) lowestLocationNum = locationNum; //Setting the lowest number for the first time around.
		if (lowestLocationNum > locationNum) lowestLocationNum = locationNum;

		std::cout << "Location number for seed " << almanac.seed_data[i] << " is " << locationNum << "\n";
	}
	std::cout << "The lowest location number for this almanac is " << lowestLocationNum << '\n';

	return 0;
}

void parseAlmanac(vector<string> &puzzle, Almanac &almanac)
{
	bool searchDescription = true;
	string description = "";
	string number = "";
	string s = "seeds";
	string sts = "seed-to-soil map";
	string stf = "soil-to-fertilizer map";
	string ftw = "fertilizer-to-water map";
	string wtl = "water-to-light map";
	string ltt = "light-to-temperature map";
	string tth = "temperature-to-humidity map";
	string htl = "humidity-to-location map";

	for (int i = 0; i < puzzle.size(); ++i)
	{
		if (isCharNum(puzzle[i][0]))
		{
			searchDescription = false;
		}
		else
		{
			searchDescription = true;
			description = "";
		}
		for (int j = 0; j <= puzzle[i].size(); ++j)
		{
			if (!isCharNum(puzzle[i][j]) && searchDescription)
			{
				description.push_back(puzzle[i][j]);
			}
			if (description == s)
			{
				searchDescription = false;
				if (isCharNum(puzzle[i][j]))
				{
					number.push_back(puzzle[i][j]);
				}
				else if (!isCharNum(puzzle[i][j]) && number != "")
				{
					almanac.seed_data.push_back(std::stoul(number));
					number = "";
				}
			}
			if (description == sts)
			{
				searchDescription = false;
				if (isCharNum(puzzle[i][j]))
				{
					number.push_back(puzzle[i][j]);
				}
				else if (!isCharNum(puzzle[i][j]) && number != "")
				{
					almanac.sts.push_back(std::stoul(number));
					number = "";
					if (almanac.sts.size() >= 3)
					{
						almanac.seed_to_soil.push_back(almanac.sts);
						almanac.sts.clear();
					}
				}
			}
			if (description == stf)
			{
				searchDescription = false;
				if (isCharNum(puzzle[i][j]))
				{
					number.push_back(puzzle[i][j]);
				}
				else if (!isCharNum(puzzle[i][j]) && number != "")
				{
					almanac.stf.push_back(std::stoul(number));
					number = "";
					if (almanac.stf.size() >= 3)
					{
						almanac.soil_to_fertilizer.push_back(almanac.stf);
						almanac.stf.clear();
					}
				}
			}
			if (description == ftw)
			{
				searchDescription = false;
				if (isCharNum(puzzle[i][j]))
				{
					number.push_back(puzzle[i][j]);
				}
				else if (!isCharNum(puzzle[i][j]) && number != "")
				{
					almanac.ftw.push_back(std::stoul(number));
					number = "";
					if (almanac.ftw.size() >= 3)
					{
						almanac.fertilizer_to_water.push_back(almanac.ftw);
						almanac.ftw.clear();
					}
				}
			}
			if (description == wtl)
			{
				searchDescription = false;
				if (isCharNum(puzzle[i][j]))
				{
					number.push_back(puzzle[i][j]);
				}
				else if (!isCharNum(puzzle[i][j]) && number != "")
				{
					almanac.wtl.push_back(std::stoul(number));
					number = "";
					if (almanac.wtl.size() >= 3)
					{
						almanac.water_to_light.push_back(almanac.wtl);
						almanac.wtl.clear();
					}
				}
			}
			if (description == ltt)
			{
				searchDescription = false;
				if (isCharNum(puzzle[i][j]))
				{
					number.push_back(puzzle[i][j]);
				}
				else if (!isCharNum(puzzle[i][j]) && number != "")
				{
					almanac.ltt.push_back(std::stoul(number));
					number = "";
					if (almanac.ltt.size() >= 3)
					{
						almanac.light_to_temperature.push_back(almanac.ltt);
						almanac.ltt.clear();
					}
				}
			}
			if (description == tth)
			{
				searchDescription = false;
				if (isCharNum(puzzle[i][j]))
				{
					number.push_back(puzzle[i][j]);
				}
				else if (!isCharNum(puzzle[i][j]) && number != "")
				{
					almanac.tth.push_back(std::stoul(number));
					number = "";
					if (almanac.tth.size() >= 3)
					{
						almanac.temperature_to_humidity.push_back(almanac.tth);
						almanac.tth.clear();
					}
				}
			}
			if (description == htl)
			{
				searchDescription = false;
				if (isCharNum(puzzle[i][j]))
				{
					number.push_back(puzzle[i][j]);
				}
				else if (!isCharNum(puzzle[i][j]) && number != "")
				{
					almanac.htl.push_back(std::stoul(number));
					number = "";
					if (almanac.htl.size() >= 3)
					{
						almanac.humidity_to_location.push_back(almanac.htl);
						almanac.htl.clear();
					}
				}
			}
		}
	}
}

vector<unsigned long> expandSeeds(Almanac &almanac)
{
	vector<unsigned long> seeds;

	for (int i = 1; i < almanac.seed_data.size(); i = i + 2)
	{
		for (int j = 0; j < almanac.seed_data[i] - 1; ++j)
		{
			seeds.push_back(almanac.seed_data[i - 1] + j);
		}
	}

	return seeds;
}

unsigned long getTotalSeedCount(Almanac* almanac)
{
	unsigned long total = 0;

	for (int i = 1; i < almanac->seed_data.size(); i = i + 2)
	{
		total += almanac->seed_data[i];
	}

	return total;
}

unsigned long convertSourceToDestination(const vector<vector<unsigned long>> &legend, const unsigned long* source)
{
	unsigned long destination = 0;
	unsigned long tempSource = 0;
	unsigned long tempDestination = 0;
	unsigned long range = 0;
	bool numIsOutsideRange = false;

	for (int i = 0; i < legend.size(); ++i)
	{

		tempDestination = legend[i][0];
		tempSource = legend[i][1];
		range = legend[i][2];

		if (*source > (tempSource + range) - 1 ||
			*source < tempSource)
		{
			numIsOutsideRange = true;
		}
		else numIsOutsideRange = false;

		if (numIsOutsideRange == false)
		{
			destination = (*source - tempSource) + tempDestination;
			break;
		}

		if (i >= legend.size() - 1 && numIsOutsideRange == true)
		{
			destination = *source;
		}
	}
	return destination;
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
