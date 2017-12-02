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
    bool found;

    for(int i = 0; i<input.size(); ++i)
    {
        std::stringstream ss(input[i]);
        std::string buf;
        std::vector<int> nums;

        while(ss >> buf)
        {
            nums.push_back(std::stoi(buf));
        }

        found = false;

        for(const auto& x : nums)
        {
            for(const auto& y : nums)
            {
                if(x != y && x > y && x % y == 0)
                {
                    checksum += (x/y);
                    found = true;
                    break;
                }
            }
            if(found) break;
        }
    }

    std::cout << checksum << '\n';
}

