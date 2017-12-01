#include <iostream>
#include <vector>
#include <fstream>

int main()
{
    std::ifstream file ("../input.txt");
    std::vector<std::string> input;
    std::string s;
    
    while(file>>s)
    {
        input.push_back(s);
    }

    std::string sequence = input[0];
    int total = 0;
    int length = sequence.length();
    int half_length = length/2;
    
    for(int i = 0; i <= length; ++i)
    {
        if(sequence[i] == sequence[(i+half_length)%length])
        {
            total += (sequence[i] - '0');
        }
    }

    std::cout << total << std::endl;
}

