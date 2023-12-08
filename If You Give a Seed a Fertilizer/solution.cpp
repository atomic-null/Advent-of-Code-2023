#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "almanac.h"

using std::vector;
using std::string;

unsigned long convertSeedToSoil(const Almanac *almanac);
unsigned long convertSoilToFertilizer(const unsigned long* soil);
unsigned long convertFertilizerToWater(const unsigned long* fertilizer);
unsigned long convertWaterToLight(const unsigned long* water);
unsigned long convertLightToTemperature(const unsigned long* light);
unsigned long convertTemperatureToHumidity(const unsigned long* temperature);
unsigned long convertHumidityToLocation(const unsigned long* humidity);
void parseAlmanac(vector<string> &puzzle, Almanac &almanac);
bool isCharNum(const char &input);

int main()
{
	std::ifstream puzzleFile;
	string line;
	vector<string> puzzleInput;
	Almanac almanac;
	unsigned long soilNum = 0;
	unsigned long fertilizerNum = 0;
	unsigned long waterNum = 0;
	unsigned long lightNum = 0;
	unsigned long temperatureNum = 0;
	unsigned long humidityNum = 0;
	unsigned long locationNum = 0;
	unsigned long lowestLocationNum = 0;

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

	parseAlmanac(puzzleInput, almanac);

	for (int i = 0; i < almanac.seeds.size(); ++i)
	{
		soilNum = convertSeedToSoil(&almanac);
		fertilizerNum = convertSoilToFertilizer(&soilNum);
		waterNum = convertFertilizerToWater(&fertilizerNum);
		lightNum = convertWaterToLight(&waterNum);
		temperatureNum = convertLightToTemperature(&lightNum);
		humidityNum = convertTemperatureToHumidity(&temperatureNum);
		locationNum = convertHumidityToLocation(&humidityNum);
		
		if (lowestLocationNum > locationNum) lowestLocationNum = locationNum;

		std::cout << "Lowest location number for seed " << almanac.seeds[i] << " is " << lowestLocationNum << "\n";
	}

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
					almanac.seeds.push_back(std::stoul(number));
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


unsigned long convertSeedToSoil(const Almanac *almanac)
{
	unsigned long soil = 0;


	return soil;
}

unsigned long convertSoilToFertilizer(const unsigned long* soil)
{
	unsigned long fertilizer = 0;

	return fertilizer = 0;
}

unsigned long convertFertilizerToWater(const unsigned long* fertilizer)
{
	unsigned long water = 0;

	return water;
}

unsigned long convertWaterToLight(const unsigned long* water)
{
	unsigned long light = 0;

	return light;
}

unsigned long convertLightToTemperature(const unsigned long* light)
{
	unsigned long temperature = 0;

	return temperature;
}

unsigned long convertTemperatureToHumidity(const unsigned long* temperature)
{
	unsigned long humidity = 0;

	return humidity;
}

unsigned long convertHumidityToLocation(const unsigned long* humidity)
{
	unsigned long location = 0;

	return location;
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