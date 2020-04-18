#include <string>
#include <vector>
#include <map>
#include <regex>
/*************************************************************
    The library provides conversions in the range of 1-3999
 ************************************************************/

std::vector<std::pair<const unsigned int, const char*>> romanVector
{
    {1000, "M"}, {900,"CM"}, {500,"D"}, {400, "CD"},
    {100, "C"}, {90, "XC"}, {50, "L"}, {40, "XL"},
    {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"}    
};

std::string toRoman(int value)
{
    if(value <= 0)
        return "non-positive number!";
    if(value > 3999)
        return "to large value!";

    std::string result;
    for(auto const &pair : romanVector)
    {
        while(value >= pair.first)
        {
            result += pair.second;
            value -= pair.first;
        }
    }
    return result;
}

std::regex romanNumerals("^(?=[MDCLXVI])M*(C[MD]|D?C{0,3})(X[CL]|L?X{0,3})(I[XV]|V?I{0,3})$");

void checkRomanInput(const std::string &value)
{
    std::smatch matchingBehavior;
    if(!(std::regex_search(value, matchingBehavior, romanNumerals)))
        throw -1;
}

std::map<const char, const int> romanMap 
{
    {'M', 1000},
    {'D', 500},
    {'C', 100},
    {'L', 50},
    {'X', 10},
    {'V', 5},
    {'I', 1},
};

int fromRoman(const std::string &value)
{
    try
    {
        checkRomanInput(value);
    }
    catch(const int& error)
    {
        return -1;
    }

    int result = 0;
    for(int i=0; i<value.size()-1; ++i)
    {
        if(romanMap[value[i]] < romanMap[value[i+1]])
            result -= romanMap[value[i]];
        else   
            result += romanMap[value[i]];
    }
    result += romanMap[value[value.size()-1]];
    return result;
}
