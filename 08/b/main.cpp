#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>

std::vector<std::string> split(const std::string& s) {
    std::istringstream iss{s};
    return std::vector<std::string>{std::istream_iterator<std::string>{iss}, {}};
}

int get_value(std::map<std::string, int> registers, std::string key)
{
    return registers[key];
}

int inc(std::map<std::string, int>& registers, std::string key, int n, int max)
{
    registers[key] += n;
    if(registers[key] > max)
    {
        return registers[key];
    }else{
        return max;
    }
}

int dec(std::map<std::string, int>& registers, std::string key, int n, int max)
{
    registers[key] -= n;
    if(registers[key] > max)
    {
        return registers[key];
    }else{
        return max;
    }

}

bool check_condition(std::string condition, int a, int b)
{
    if(condition == "<") return (a < b);
    else if(condition == "<=") return (a<=b);
    else if(condition == ">") return (a>b);
    else if(condition == ">=") return (a>=b);
    else if(condition == "==") return (a==b);
    else if(condition == "!=") return (a!=b);
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

    std::map<std::string, int> registers;
    int max = 0;
    
    for (const auto& s : input)
    {
        auto line = split(s);
        if(check_condition(line[5], get_value(registers, line[4]), stoi(line[6])))
        {
            if(line[1] == "inc") max = inc(registers, line[0], stoi(line[2]), max);
            else max = dec(registers, line[0], stoi(line[2]), max);
        }
        
    }
    
    std::cout << max << '\n';
}

