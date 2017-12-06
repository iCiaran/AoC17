#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <algorithm>

std::vector<int> split(const std::string& s) {
    std::istringstream iss{s};
    return std::vector<int>{std::istream_iterator<int>{iss}, {}};
}

std::string v_to_string(std::vector<int> input)
{
    std::stringstream result;
    std::copy(input.begin(), input.end(), std::ostream_iterator<int>(result, " "));
    return result.str();
}

std::vector<int> cycle(std::vector<int> input, int len)
{
    auto max = max_element(input.begin(), input.end());
    int value = *max;
    int pos = max - input.begin();

    input[pos] = 0;

    for(int j = 1; j <= value; ++j)
    {
        input[(pos + j)%len]++;
    }

    return input;
}

int main()
{
    std::ifstream file ("../input.txt");
    std::string line;
    std::getline(file, line);
    std::vector<int> input = split(line);

    std::unordered_map<std::string, int> past_states;
    int count = 0;
    
    int len = input.size();
    auto i = past_states.insert({v_to_string(input), count});
    
    while(i.second)
    {
        count++;
        input = cycle(input, len);
        i = past_states.insert({v_to_string(input), count}); 
    }

    std::string repeat = v_to_string(input);
    
    std::cout << count-past_states[repeat] << '\n';
}

