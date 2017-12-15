#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <set>

std::vector<int> split(const std::string& s) {
    std::vector<int> tokens;
    for(const char& c : s)
    {
        tokens.push_back((int)c);
    }

    return tokens;
}

void reverse(std::vector<int>& list, int index, int length)
{
    int a, b, temp, size = list.size();
    for(int i = 0; i < length/2; i++)
    {
        a = (index + i) % size;
        b = (index + length - i - 1) % size;
        temp = list[a];
        list[a] = list[b];
        list[b] = temp;
    }
}

void round(std::vector<int>& list, std::vector<int>& lengths, int& index, int& skip)
{
    for(const auto& length : lengths)
    {
        reverse(list, index, length);
        index += (length + skip) % 256;
        skip++;
    }
}

std::vector<int> get_dense(std::vector<int>& list)
{
    std::vector<int> dense;

    for(int i = 0; i < 16; ++i)
    {
        int x = 0;
        for(int j = 0; j < 16; ++j)
        {
            x = x ^ list[16*i+j];
        }
        dense.push_back(x);
    }

    return dense;
}

std::vector<int> get_hash(std::string in)
{
    std::vector<int> lengths = split(in);
    std::vector<int> standard{17, 31, 73, 47, 23};
    lengths.insert(lengths.end(), standard.begin(), standard.end());

    std::vector<int> list(256);
    std::iota(list.begin(), list.end(), 0);

    int index = 0, skip = 0;

    for(int i = 0; i < 64; ++i)
    {
        round(list, lengths, index, skip);
    }

    std::vector<int> dense = get_dense(list);
    return dense;
}

std::string get_binary(std::vector<int> dense)
{
    std::ostringstream os;
    for(const auto& i : dense)
    {
        os << std::bitset<8>(i);
    }

    return os.str();
}

bool check_bounds(int x, int y)
{
    return (x >= 0 && y >=0 && x<128 && y<128);
}

std::set<std::array<int, 2>> bfs(int x, int y, 
        const std::vector<std::string>& grid, 
        const std::array<std::array<int, 2>, 4>& dirs)
{
    std::set<std::array<int, 2>> visited;
    std::vector<std::array<int, 2>> stack;
    stack.push_back({x,y});
            
    while(stack.size())
    {
        auto current = stack.back();
        stack.pop_back();
        if(visited.count(current)) continue;
        visited.insert(current);
        for(const auto& d : dirs)
        {
            std::array<int, 2> next {current[0] + d[0], current[1] + d[1]};
            if(check_bounds(next[0],next[1]) && grid[next[0]][next[1]] == '1')
                stack.push_back(next);
        }
    }

    return visited;
}

int main()
{
    std::ifstream file ("../input.txt");
    std::string input;

    std::getline(file, input); 
    input += "-";

    std::string temp, line;
    std::vector<std::string> grid;
    
    for(int i=0; i<128; ++i)
    {
        temp = input + std::to_string(i);
        line = get_binary(get_hash(temp));
        grid.push_back(line);
    }

    int groups = 0;
    std::array<std::array<int, 128>, 128> value;

    for(int y=0; y<128; ++y) 
    {
        for(int x=0; x<128; ++x)
        {
            value[x][y] = 0;
        }
    }

    std::array<std::array<int, 2>,4> dirs = {{{-1,0}, {1,0}, {0,-1}, {0,1}}};

    for(int y = 0; y < 128; ++y)
    {
        for(int x = 0; x < 128; ++x)
        {
            if(grid[x][y] == '0')   continue;
            if(value[x][y])         continue;
            
            auto visited = bfs(x, y, grid, dirs);

            if(visited.size())
            {
                groups++;
                for(const auto& v : visited)
                {
                    value[v[0]][v[1]] = groups;
                }
            }
        }
    }
    
    std::cout << groups << '\n';
}

