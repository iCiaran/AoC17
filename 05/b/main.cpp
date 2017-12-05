#include <iostream>
#include <vector>
#include <fstream>

int main()
{
    std::ifstream file ("../input.txt");
    std::vector<int> input;
    std::string line;
    
    while(std::getline(file, line))
    {
        input.push_back(stoi(line));
    }
    
    int jumps = 0;
    int current = 0;
    int next;

    while (current >= 0 && current < input.size())
    {
        next = current + input[current];

        if(input[current] >= 3)
        {
            input[current]--;
        }else{
            input[current]++;
        }

        current = next;
        jumps++;
    }
    
    std::cout << jumps << '\n';
}

