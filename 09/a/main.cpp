#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>

std::string remove_not(std::string input)
{
    std::string clean;
    bool skip = false;

    for(const auto& c : input)
    {
        if(!skip)
        {
            if(c == '!')
            {
                skip = true;
            }else{
                clean.push_back(c);
            }
        }else{
            skip = false;
        }
    }
    return clean;
}

bool is_important(char c)
{
    return (c == '{' || c == '}' || c == '<' || c == '>');
}

std::string remove_random(std::string input)
{
    std::string clean;

    for(const auto& c : input)
    {
        if(is_important(c)) clean.push_back(c);
    }
    return clean;
}

std::string remove_garbage(std::string input)
{
    std::string clean;
    bool garbage = false;
    int level = 0;
    
    for(const auto& c : input)
    {
        if(!garbage)
        {
            if(c == '<')
            {
                garbage = true;
            }else{
                clean.push_back(c);
            }
        }else{
            if(c == '>')
            {
                garbage = false;
            }
        }
    }

    return clean;
}

int main()
{
    std::ifstream file ("../input.txt");
    
    std::string input;
    std::getline(file, input);
    
    input = remove_not(input);
    input = remove_random(input);
    input = remove_garbage(input);

    int total = 0;
    int level = 0;

    for(const auto& c : input)
    {
        if(c == '{')
        {
            level++;
            total += level;
        }else{
            level--;
        }
    }

    std::cout << total << '\n';
}

