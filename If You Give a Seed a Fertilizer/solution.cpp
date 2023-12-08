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
unsigned long convertSeedToSoil(const Almanac* almanac, int* index);
unsigned long convertSoilToFertilizer(const Almanac* almanac, int* index, const unsigned long* soilNum);
unsigned long convertFertilizerToWater(const Almanac* almanac, int* index, const unsigned long* fertilizer);
unsigned long convertWaterToLight(const Almanac* almanac, int* index, const unsigned long* water);
unsigned long convertLightToTemperature(const Almanac* almanac, int* index, const unsigned long* light);
unsigned long convertTemperatureToHumidity(const Almanac* almanac, int* index, const unsigned long* temperature);
unsigned long convertHumidityToLocation(const Almanac* almanac, int* index, const unsigned long* humidity);
bool isCharNum(const char &input);
unsigned long findMappedTarget(const unsigned long* target, const unsigned long* destination, const unsigned long* source, const unsigned long* range);
unsigned long binarySearch(const unsigned long* target, const unsigned long* start, const unsigned long* end);

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
		soilNum = convertSeedToSoil(&almanac, &i);
		fertilizerNum = convertSoilToFertilizer(&almanac, &i, &soilNum);
		waterNum = convertFertilizerToWater(&almanac, &i, &fertilizerNum);
		lightNum = convertWaterToLight(&almanac, &i, &waterNum);
		temperatureNum = convertLightToTemperature(&almanac, &i, &lightNum);
		humidityNum = convertTemperatureToHumidity(&almanac, &i, &temperatureNum);
		locationNum = convertHumidityToLocation(&almanac, &i, &humidityNum);
		
		if (i == 0) lowestLocationNum = locationNum; //Setting the lowest number for the first time around.
		if (lowestLocationNum > locationNum) lowestLocationNum = locationNum;

		std::cout << "Location number for seed " << almanac.seeds[i] << " is " << locationNum << "\n";
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


unsigned long convertSeedToSoil(const Almanac *almanac, int *index)
{
	unsigned long soil = 0;
	unsigned long seedNum = 0;
	unsigned long source = 0;
	unsigned long destination = 0;
	unsigned long range = 0;
	bool numIsOutsideRange = false;
    
	for (int i = 0; i < almanac->seed_to_soil.size(); ++i)
	{
		seedNum = almanac->seeds[*index];
		destination = almanac->seed_to_soil[i][0];
		source = almanac->seed_to_soil[i][1];
		range = almanac->seed_to_soil[i][2];

		if (seedNum > (source + range) - 1 ||
			seedNum < source)
		{
			numIsOutsideRange = true;
		}
		else numIsOutsideRange = false;

		if (numIsOutsideRange == false)
		{
			soil = (seedNum - source) + destination;
			break;
		}
		
		if (i >= almanac->seed_to_soil.size() - 1 && numIsOutsideRange == true)
		{
			soil = seedNum;
		}
	}

	return soil;
}

unsigned long convertSoilToFertilizer(const Almanac* almanac, int* index, const unsigned long* soilNum)
{
	unsigned long fertilizer = 0;
	unsigned long source = 0;
	unsigned long destination = 0;
	unsigned long range = 0;
	bool numIsOutsideRange = false;

	for (int i = 0; i < almanac->soil_to_fertilizer.size(); ++i)
	{
		destination = almanac->soil_to_fertilizer[i][0];
		source = almanac->soil_to_fertilizer[i][1];
		range = almanac->soil_to_fertilizer[i][2];

		if (*soilNum > (source + range) - 1 ||
			*soilNum < source)
		{
			numIsOutsideRange = true;
		}
		else numIsOutsideRange = false;

		if (numIsOutsideRange == false)
		{
			fertilizer = (*soilNum - source) + destination;
			break;
		}

		if (i >= almanac->soil_to_fertilizer.size() - 1 && numIsOutsideRange == true)
		{
			fertilizer = *soilNum;
		}
	}
	return fertilizer;
}

unsigned long convertFertilizerToWater(const Almanac* almanac, int* index, const unsigned long* fertilizerNum)
{
	unsigned long water = 0;
	unsigned long source = 0;
	unsigned long destination = 0;
	unsigned long range = 0;
	bool numIsOutsideRange = false;

	for (int i = 0; i < almanac->fertilizer_to_water.size(); ++i)
	{
		destination = almanac->fertilizer_to_water[i][0];
		source = almanac->fertilizer_to_water[i][1];
		range = almanac->fertilizer_to_water[i][2];

		if (*fertilizerNum > (source + range) - 1 ||
			*fertilizerNum < source)
		{
			numIsOutsideRange = true;
		}
		else numIsOutsideRange = false;

		if (numIsOutsideRange == false)
		{
			water = (*fertilizerNum - source) + destination;
			break;
		}

		if (i >= almanac->fertilizer_to_water.size() - 1 && numIsOutsideRange == true)
		{
			water = *fertilizerNum;
		}
	}
	return water;
}

unsigned long convertWaterToLight(const Almanac* almanac, int* index, const unsigned long* waterNum)
{
	unsigned long light = 0;
	unsigned long source = 0;
	unsigned long destination = 0;
	unsigned long range = 0;
	bool numIsOutsideRange = false;

	for (int i = 0; i < almanac->water_to_light.size(); ++i)
	{
		destination = almanac->water_to_light[i][0];
		source = almanac->water_to_light[i][1];
		range = almanac->water_to_light[i][2];

		if (*waterNum > (source + range) - 1 ||
			*waterNum < source)
		{
			numIsOutsideRange = true;
		}
		else numIsOutsideRange = false;

		if (numIsOutsideRange == false)
		{
			light = (*waterNum - source) + destination;
			break;
		}

		if (i >= almanac->water_to_light.size() - 1 && numIsOutsideRange == true)
		{
			light = *waterNum;
		}
	}
	return light;
}

unsigned long convertLightToTemperature(const Almanac* almanac, int* index, const unsigned long* lightNum)
{
	unsigned long temperature = 0;
	unsigned long source = 0;
	unsigned long destination = 0;
	unsigned long range = 0;
	bool numIsOutsideRange = false;

	for (int i = 0; i < almanac->light_to_temperature.size(); ++i)
	{
		destination = almanac->light_to_temperature[i][0];
		source = almanac->light_to_temperature[i][1];
		range = almanac->light_to_temperature[i][2];

		if (*lightNum > (source + range) - 1 ||
			*lightNum < source)
		{
			numIsOutsideRange = true;
		}
		else numIsOutsideRange = false;

		if (numIsOutsideRange == false)
		{
			temperature = (*lightNum - source) + destination;
			break;
		}

		if (i >= almanac->light_to_temperature.size() - 1 && numIsOutsideRange == true)
		{
			temperature = *lightNum;
		}
	}
	return temperature;
}

unsigned long convertTemperatureToHumidity(const Almanac* almanac, int* index, const unsigned long* temperatureNum)
{
	unsigned long humidity = 0;
	unsigned long source = 0;
	unsigned long destination = 0;
	unsigned long range = 0;
	bool numIsOutsideRange = false;

	for (int i = 0; i < almanac->temperature_to_humidity.size(); ++i)
	{
		destination = almanac->temperature_to_humidity[i][0];
		source = almanac->temperature_to_humidity[i][1];
		range = almanac->temperature_to_humidity[i][2];

		if (*temperatureNum > (source + range) - 1 ||
			*temperatureNum < source)
		{
			numIsOutsideRange = true;
		}
		else numIsOutsideRange = false;

		if (numIsOutsideRange == false)
		{
			humidity = (*temperatureNum - source) + destination;
			break;
		}

		if (i >= almanac->temperature_to_humidity.size() - 1 && numIsOutsideRange == true)
		{
			humidity = *temperatureNum;
		}
	}
	return humidity;
}

unsigned long convertHumidityToLocation(const Almanac* almanac, int* index, const unsigned long* humidityNum)
{
	unsigned long location = 0;
	unsigned long source = 0;
	unsigned long destination = 0;
	unsigned long range = 0;
	bool numIsOutsideRange = false;

	for (int i = 0; i < almanac->humidity_to_location.size(); ++i)
	{
		destination = almanac->humidity_to_location[i][0];
		source = almanac->humidity_to_location[i][1];
		range = almanac->humidity_to_location[i][2];

		if (*humidityNum > (source + range) - 1 ||
			*humidityNum < source)
		{
			numIsOutsideRange = true;
		}
		else numIsOutsideRange = false;

		if (numIsOutsideRange == false)
		{
			location = (*humidityNum - source) + destination;
			break;
		}

		if (i >= almanac->humidity_to_location.size() - 1 && numIsOutsideRange == true)
		{
			location = *humidityNum;
		}
	}
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

unsigned long findMappedTarget(const unsigned long *target, const unsigned long *destination, const unsigned long *source, const unsigned long *range)
{
	unsigned long start = *source;
	unsigned long end = *source + *range - 1;
	unsigned long mappedTarget = binarySearch(target, &start, &end);

	return mappedTarget;
}

unsigned long binarySearch(const unsigned long *target,const unsigned long *start, const unsigned long *end)
{
	if (*start > *end)
	{
		return NULL;
	}

	unsigned long middle = (*start + *end) / 2;

	if (middle == *target) return middle;
	if (middle > *target)
	{
		--middle;
		return binarySearch(target, start, &middle);
	}
	if (middle < *target)
	{
		++middle;
		return binarySearch(target, &middle, end);
	}
}