#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <numeric>

std::vector<int> split(const std::string& s) {
    std::istringstream iss{s};
    std::vector<int> tokens;
    std::string token;

    while(std::getline(iss, token, ','))
    {
        tokens.push_back(stoi(token));
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

void print(std::vector<int>& list)
{
    for(const auto& i : list)
    {
        std::cout << i << " ";
    }
    std::cout << '\n';
}

int main()
{
    std::ifstream file ("../input.txt");
    std::vector<std::string> input;
    std::string line;
 
    std::getline(file, line);
    
    std::vector<int> lengths = split(line);

    std::vector<int> list(256);
    std::iota(list.begin(), list.end(), 0);
    int index = 0, skip = 0, size = list.size();

    for(const auto& length : lengths)
    {
        reverse(list, index, length);
        index += (length + skip) % size;
        skip++;
    }

    std::cout << list[0] << " * " << list[1] << " = " << list[0] * list[1] << '\n';
}
