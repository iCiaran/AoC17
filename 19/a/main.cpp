#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <array>


bool in_bounds(int x, int y, int width, int height)
{

    return(x >= 0 && x < width && y >= 0 && y < height);
}

int find_next_direction(const std::array<std::array<int, 2>, 4>& dirs, const std::vector<std::string>& map, int x, int y, int current)
{
    if(map[y][x] == ' ') return -1;
    if(map[y][x] != '+') return current;

    for(int i = 0; i < 4; ++i)
    {
        if(i == (current+2)%4) continue;
        int nextx = x + dirs[i][0];
        int nexty = y + dirs[i][1];
        if(!in_bounds(nextx, nexty, map[0].size(), map.size())) continue;
        if (map[nexty][nextx] != ' ') return i;
    }
    return -1;
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
    
    std::array<std::array<int, 2>, 4> dirs {{{1,0}, {0,1}, {-1,0}, {0,-1}}};
    
    int y = 0, x = input[0].find_first_of('|');
    int dir = 1;
    std::string sequence = "";
    while(dir != -1)
    {
        char c = input[y][x];
        if(c != '|' && c != '-' && c!= '+') sequence.push_back(c);
        x += dirs[dir][0];
        y += dirs[dir][1];
        dir = find_next_direction(dirs, input, x, y, dir);
    }
    std::cout << sequence << '\n';
}

