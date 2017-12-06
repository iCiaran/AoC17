#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <set>

std::vector<int> split(const std::string& s) {
    std::istringstream iss{s};
    return std::vector<int>{std::istream_iterator<int>{iss}, {}};
}

int main()
{
    std::ifstream file ("../input.txt");
    std::string line;
    std::getline(file, line);
    std::vector<int> input = split(line);

    std::set<std::vector<int>> past_states;
    int count = 0;
    
    int len = input.size();
    auto i = past_states.insert(input);
    
    while(i.second)
    {
        auto max = max_element(input.begin(), input.end());
        int value = *max;
        int pos = max - input.begin();
        
        input[pos] = 0;

        for(int j = 1; j <= value; ++j)
        {
            input[(pos + j)%len]++;
        }

        i = past_states.insert(input); 
        count++;
    }

    std::cout << count << '\n';
}

