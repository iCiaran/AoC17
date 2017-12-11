#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>
#include <algorithm>
#include <cmath>

std::vector<std::string> split(const std::string& s) {
    std::istringstream iss{s};
    std::vector<std::string> tokens;
    std::string token;

    while(std::getline(iss, token, ','))
    {
        tokens.push_back(token);
    }

    return tokens;
}

int get_distance(int x, int y, int z)
{
    std::vector<int> temp = {abs(0-x), abs(0-y), abs(0-z)};
    return *std::max_element(temp.begin(), temp.end());
}

int main()
{
    std::ifstream file ("../input.txt");
    std::vector<std::string> input;
    std::string line;
    
    std::getline(file, line);

    std::vector<std::string> dirs = split(line);
   
    int x{0}, y{0}, z{0};

    std::map<std::string, std::vector<int>> trans;
    trans.insert({"n",  {0,1,-1}});
    trans.insert({"s",  {0,-1,1}});
    trans.insert({"ne", {1,0,-1}});
    trans.insert({"nw", {-1,1,0}});
    trans.insert({"se", {1,-1,0}});
    trans.insert({"sw", {-1,0,1}});
   
    for(const auto& d : dirs)
    {
        x += trans[d][0];
        y += trans[d][1];
        z += trans[d][2];
    }

    int distance = get_distance(x, y, z);

    std::cout << distance << '\n';
}

