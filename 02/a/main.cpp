#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

int main()
{
    std::ifstream file ("../input.txt");
    std::vector<std::string> input;
    std::string line;
    
    while(std::getline(file, line))
    {
        input.push_back(line);
    }
    
    int checksum = 0;

    for(int i = 0; i<input.size(); ++i)
    {
        std::stringstream ss(input[i]);
        std::string buf;
        std::vector<int> nums;
        
        while(ss >> buf)
        {
            nums.push_back(std::stoi(buf));
        }

        int small = *std::min_element(nums.begin(), nums.end());
        int big = *std::max_element(nums.begin(), nums.end());
        
        checksum += (big-small);
    }

    std::cout << checksum << '\n';
}

