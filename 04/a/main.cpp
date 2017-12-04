#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_set>

bool test_passphrase(std::string passphrase)
{
    std::stringstream ss(passphrase);
    std::string buf;
    std::unordered_set<std::string> set;

    while(ss >> buf)
    {
        auto i = set.insert(buf);
        if(!i.second) return false;
    }

    return true;
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

    int total = 0;

    for(const auto& passphrase : input){
        if(test_passphrase(passphrase)) total++;
    }
    
    std::cout << total << '\n';
}

