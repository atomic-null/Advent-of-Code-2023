#pragma once
#include <vector>

using std::vector;

class Almanac
{
public:
	vector<unsigned long> seed_data;
	vector<unsigned long> sts;
	vector<unsigned long> stf;
	vector<unsigned long> ftw;
	vector<unsigned long> wtl;
	vector<unsigned long> ltt;
	vector<unsigned long> tth;
	vector<unsigned long> htl;
	vector<vector<unsigned long>> seed_to_soil;
	vector<vector<unsigned long>> soil_to_fertilizer;
	vector<vector<unsigned long>> fertilizer_to_water;
	vector<vector<unsigned long>> water_to_light;
	vector<vector<unsigned long>> light_to_temperature;
	vector<vector<unsigned long>> temperature_to_humidity;
	vector<vector<unsigned long>> humidity_to_location;

	Almanac(){}

};