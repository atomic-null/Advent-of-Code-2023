#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

int getSumOfPartNumbers(std::vector<std::string> schematic);
int getSumOfGearRatios(std::vector<std::string> schematic);
bool isCharNum(const char& input);
bool isCharSymbol(const char& input);
int getGearRatio(const std::vector<int>& gearValues);

int main()
{
	std::ifstream puzzleFile;
	std::string line;
	std::vector<std::string> puzzleInput;

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

	//std::cout << "Sum of part numbers is " << getSumOfPartNumbers(puzzleInput) << '\n';
	std::cout << "Sum of gear ratios is " << getSumOfGearRatios(puzzleInput) << '\n';

	return 0;
}

int getSumOfGearRatios(std::vector<std::string> schematic)
{
	int sum = 0;
	std::string number = "";
	std::vector<int> gearValues;

	for (int i = 0; i < schematic.size(); ++i)
	{
		for (int j = 0; j < schematic[i].size(); ++j)
		{
			if (schematic[i][j] == '*')
			{
				//checking left of the * for a number
				if ((j - 1 != 0) && (isCharNum(schematic[i][j - 1])))
				{
					int k = 1;
					bool searchFlag = true;
					while (searchFlag)
					{
						if (j - k < 0)
						{
							searchFlag = false;
							std::reverse(number.begin(), number.end());
							gearValues.push_back(std::stoi(number));
							number = "";
							break;
						}

						if (!isCharNum(schematic[i][j - k]))
						{
							searchFlag = false;
							std::reverse(number.begin(), number.end());
							gearValues.push_back(std::stoi(number));
							number = "";
							break;
						}

						if (isCharNum(schematic[i][j - k]))
						{
							number.push_back(schematic[i][j - k]);
						}
						++k;
					}
				}

				//checking right of the * for a number
				if ((j != schematic[i].size() - 1) && (isCharNum(schematic[i][j + 1])))
				{
					int k = 1;
					bool searchFlag = true;
					int indexValue = 0;
					while (searchFlag)
					{
						indexValue = j + k;
						if (indexValue == schematic[i].size())
						{
							searchFlag = false;
							gearValues.push_back(std::stoi(number));
							number = "";
							break;
						}

						if (!isCharNum(schematic[i][j + k]))
						{
							searchFlag = false;
							gearValues.push_back(std::stoi(number));
							number = "";
							break;
						}

						if (isCharNum(schematic[i][j + k]))
						{
							number.push_back(schematic[i][j + k]);
						}
						++k;
					}
				}

				//checking above the * for a number
				if (i != 0)
				{
					if (isCharNum(schematic[i - 1][j - 1]) ||
						isCharNum(schematic[i - 1][j]) ||
						isCharNum(schematic[i - 1][j + 1]))
					{
						int k = j - 1;
						bool searchFlag = true;

						while (true)
						{
							if (k > 0 && isCharNum(schematic[i - 1][k])) k--;
							else break;
						}

						while (searchFlag)
						{
							if (k == schematic[i - 1].size())
							{
								searchFlag = false;
								gearValues.push_back(std::stoi(number));
								number = "";
								break;
							}

							if (!isCharNum(schematic[i - 1][k]) && !isCharNum(schematic[i - 1][k + 1]))
							{
								searchFlag = false;
								gearValues.push_back(std::stoi(number));
								number = "";
								break;
							}
							else if (!isCharNum(schematic[i - 1][k]) && isCharNum(schematic[i - 1][k + 1]))
							{
								gearValues.push_back(std::stoi(number));
								number = "";
								++k;
								continue;
							}

							if (isCharNum(schematic[i - 1][k]))
							{
								number.push_back(schematic[i - 1][k]);
							}
							++k;
						}
					}
					sum += getGearRatio(gearValues);
					gearValues.clear();
				}
				}
		}
	}

	return sum;
}

int getSumOfPartNumbers(std::vector<std::string> schematic)
{
	int sum = 0;
	bool isPartNumber = false;
	std::string number = "";

	for (int i = 0; i < schematic.size(); ++i)
	{
		for (int j = 0; j < schematic[i].size(); ++j)
		{
			//find the number in the schematic
			if (isCharNum(schematic[i][j]))
			{
				number.push_back(schematic[i][j]);

				/*Once we have found all of the digits of our number,
				we will then check if there is a touching special symbol.
				If at any point we find a special symbol, we move on to
				find the next number.*/
				if (!isCharNum(schematic[i][j + 1]))
				{
					//checking left of the number for a special character
					if ((j - (number.size() - 1) != 0) && (isCharSymbol(schematic[i][j - number.size()])))
					{
						isPartNumber = true;
						sum += std::stoi(number);
						number = "";
						isPartNumber = false;
						continue;
					}
					//checking right of the number for a special character
					if ((j < schematic[i].size()) && (isCharSymbol(schematic[i][j + 1])))
					{
						isPartNumber = true;
						sum += std::stoi(number);
						number = "";
						isPartNumber = false;
						continue;
					}
					//checking above the number for a special character
					if (i != 0)
					{
						int k = 0;
						bool searchFlag = true;
						int indexVal = j - number.size();
						if (indexVal < 0) k = 0;
						else k = j - number.size();

						while (searchFlag)
						{
							if (isCharSymbol(schematic[i - 1][k]))
							{
								isPartNumber = true;
								sum += std::stoi(number);
								number = "";
								searchFlag = false;
							}
							++k;

							if (k >= schematic[i - 1].size() || (k > j + 1)) searchFlag = false;
						}
						if (isPartNumber)
						{
							isPartNumber = false;
							number = "";
							continue;
						}
					}
					//checking below the number for a special character
					if (i < (schematic.size() - 1))
					{
						int k = 0;
						bool searchFlag = true;
						int indexVal = j - number.size();
						if (indexVal < 0) k = 0;
						else k = j - number.size();

						while (searchFlag)
						{
							if (isCharSymbol(schematic[i + 1][k]))
							{
								isPartNumber = true;
								sum += std::stoi(number);
								number = "";
								searchFlag = false;
							}
							++k;

							if (k >= schematic[i + 1].size() || (k > j + 1)) searchFlag = false;
						}
						if (isPartNumber)
						{
							isPartNumber = false;
							number = "";
							continue;
						}
					}
					if (!isPartNumber) number = "";
				}
			}
		}
		number = "";
		isPartNumber = false;
	}
	return sum;
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

bool isCharSymbol(const char& input)
{
	if (input == '*' || input == '@' || input == '#' || input == '$' ||
		input == '%' || input == '&' || input == '/' || input == '+' ||
		input == '=' || input == '-')
	{
		return true;
	}
	else return false;
}

int getGearRatio(const std::vector<int>& gearValues)
{
	int product = 0;
	for (int i = 0; i < gearValues.size(); ++i)
	{
		if (i == 0)
		{
			product = gearValues[i];
			continue;
		}
		product *= gearValues[i];
	}
	return product;
}