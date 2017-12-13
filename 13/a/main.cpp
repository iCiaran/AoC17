#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cmath>
#include <map>

std::vector<std::string> split(const std::string& s) {
    std::istringstream iss{s};
    return std::vector<std::string>{std::istream_iterator<std::string>{iss}, {}};
}

int get_pos(int time, int depth)
{
    depth--;
    return (depth - abs(time % (2*depth) - depth));
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
    
    std::map<int,int> depth;

    for(const auto& s : input)
    {
        auto v = split(s);
        v[0].pop_back();
        depth.insert({stoi(v[0]),stoi(v[1])});
    }

    int sev = 0;
    
    for(int x = 0; x<99; ++x)
    {
        if(depth.count(x))
        {
            if(get_pos(x, depth[x]) == 0) sev += x*depth[x];
        }
    }

    std::cout << sev << '\n';
}

