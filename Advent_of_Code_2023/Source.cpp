#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <iterator>
#include <map>
#include <algorithm>

int calculateRegexResultsSum(const std::vector<std::string>& puzzle, const std::regex& search, const std::regex& searchReverse);

int main()
{
    std::ifstream puzzleFile;
    std::string line;
    std::string lineNum = "";
    int sum = 0;
    std::vector<std::string> puzzleInput;
    std::smatch match;
    std::regex regexSearch("zero|one|two|three|four|five|six|seven|eight|nine|0|1|2|3|4|5|6|7|8|9");
    std::regex regexSearchReverse("orez|eno|owt|eerht|ruof|evif|xis|neves|thgie|enin|0|1|2|3|4|5|6|7|8|9");

    puzzleFile.open("puzzleinput.txt");
    if (puzzleFile.is_open())
    {
        while (std::getline(puzzleFile, line))
        {
            puzzleInput.push_back(line);
        }
        puzzleFile.close();
    }
    else std::cout << "Unable to open file.\n";

    sum += calculateRegexResultsSum(puzzleInput, regexSearch, regexSearchReverse);
    std::cout << "Total Sum: " << sum << '\n';
    return 0;
}

int calculateRegexResultsSum(const std::vector<std::string>& puzzle, const std::regex& search, const std::regex& searchReverse)
{
    std::string lineNum = "";
    std::string reversedString = "";
    int sum = 0;
    std::regex_iterator<std::string::const_iterator> wordsEnd = std::sregex_iterator();
    std::smatch match;

    std::map<std::string, char> textNumValues;
    textNumValues["zero"] = '0';
    textNumValues["one"] = '1';
    textNumValues["two"] = '2';
    textNumValues["three"] = '3';
    textNumValues["four"] = '4';
    textNumValues["five"] = '5';
    textNumValues["six"] = '6';
    textNumValues["seven"] = '7';
    textNumValues["eight"] = '8';
    textNumValues["nine"] = '9';
    textNumValues["orez"] = '0';
    textNumValues["eno"] = '1';
    textNumValues["owt"] = '2';
    textNumValues["eerht"] = '3';
    textNumValues["ruof"] = '4';
    textNumValues["evif"] = '5';
    textNumValues["xis"] = '6';
    textNumValues["neves"] = '7';
    textNumValues["thgie"] = '8';
    textNumValues["enin"] = '9';
    textNumValues["0"] = '0';
    textNumValues["1"] = '1';
    textNumValues["2"] = '2';
    textNumValues["3"] = '3';
    textNumValues["4"] = '4';
    textNumValues["5"] = '5';
    textNumValues["6"] = '6';
    textNumValues["7"] = '7';
    textNumValues["8"] = '8';
    textNumValues["9"] = '9';


    for (int i = 0; i < puzzle.size(); i++)
    {
        std::regex_iterator<std::string::const_iterator> wordsBegin;
        std::cout << "text line = " << i + 1 << '\n';
        wordsBegin = std::sregex_iterator(puzzle[i].begin(), puzzle[i].end(), search);

        for (std::sregex_iterator j = wordsBegin; j != wordsEnd; j++)
        {
            match = *j;
            lineNum.push_back(textNumValues.at(match.str()));
            std::cout << "match.str() " << match.str() << std::endl;
            std::cout << "lineNum: " << lineNum << std::endl;
            break;
        }

        reversedString = puzzle[i];
        std::reverse(reversedString.begin(), reversedString.end());
        wordsBegin = std::sregex_iterator(reversedString.begin(), reversedString.end(), searchReverse);

        for (std::sregex_iterator j = wordsBegin; j != wordsEnd; j++)
        {
            match = *j;
            lineNum.push_back(textNumValues.at(match.str()));
            std::cout << "reverse match.str() " << match.str() << std::endl;
            std::cout << "lineNum: " << lineNum << std::endl;
            break;
        } 

        sum += std::stoi(lineNum);
        std::cout << "lineNum = " << lineNum << '\n';
        std::cout << "sum = " << sum << '\n' << '\n';
        lineNum = "";
    }

    return sum;
}