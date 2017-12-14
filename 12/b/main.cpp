#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>
#include <set>

std::vector<std::string> split(const std::string& s) {
    std::istringstream iss{s};
    return std::vector<std::string>{std::istream_iterator<std::string>{iss}, {}};
}

std::map<int, std::vector<int>> parse_input(const std::vector<std::string> i){
    std::map<int, std::vector<int>> m;
    for(const auto& line : i)
    {
        auto s = split(line);
        std::vector<int> val;

        int key = std::stoi(s[0]);
        for(int i = 2; i < s.size(); ++i)
        {
            std::string temp = s[i];
            if(temp.back() == ',') temp.pop_back();
            int x = std::stoi(temp);
            val.push_back(x);
            
            if(!m.insert({x,{key}}).second)
            {
                m[x].push_back(key);
            }   
        }
    }
    return m;
}

std::set<int> find_single_group(int start, std::map<int, std::vector<int>>& con, std::set<int>& not_visited)
{
    std::set<int> visited;
    std::vector<int> stack{start};

    int current;

    while(stack.size() > 0)
    {
        current = stack.back();
        stack.pop_back();
        visited.insert(current);
        not_visited.erase(current);

        for(const auto& i : con[current])
        {
            if(!visited.count(i)) stack.push_back(i);
        }
    }
    return visited;
}

std::vector<std::set<int>> find_groups(std::map<int, std::vector<int>>& con)
{
    int start = 0;
    std::vector<std::set<int>> groups;
    std::set<int> not_visited;

    for(int i = 0; i < 2000; ++i)
    {
        not_visited.insert(i);
    }

    while(not_visited.size() > 0)
    {
        groups.push_back(find_single_group(start, con, not_visited));
        start = *not_visited.begin();
    }

    return groups;
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
    
    auto con = parse_input(input);
    auto groups = find_groups(con);
    std::cout << groups.size() << '\n';
}

