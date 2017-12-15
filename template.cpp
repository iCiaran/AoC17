#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>

std::vector<int> split(const std::string& s) {
    std::istringstream iss{s};
    return std::vector<int>{std::istream_iterator<int>{iss}, {}};
}

int main()
{
    std::ifstream file ("../input.txt");
    std::vector<std::string> input;
    std::string line;
    
    while(std::getline(file, line))
    {
        input.push_back(line);
    }
   
    for(const auto& i : input)
    {
        std::cout << i << '\n';
    }
}

