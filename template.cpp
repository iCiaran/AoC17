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
    
    for(const auto& i : input){
        std::cout << i << '\n';
    }
}

