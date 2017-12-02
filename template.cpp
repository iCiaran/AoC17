#include <iostream>
#include <vector>
#include <fstream>

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

