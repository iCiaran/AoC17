#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>

std::vector<std::string> split(const std::string& s) {
    std::istringstream iss{s};
    return std::vector<std::string>{std::istream_iterator<std::string>{iss}, {}};
}

int main()
{
    std::ifstream file ("../input.txt");
    std::string line;
    
    std::getline(file, line);
    unsigned long a = stoi(split(line)[4]);
    std::getline(file, line);
    unsigned long b = stoi(split(line)[4]);

    int mul_a = 16807;
    int mul_b = 48271;
    int div = 2147483647;
    int count = 0;

    for(int i=0; i<5000000; ++i)
    {
        do{a = (a * mul_a) % div;} while(a%4);
        do{b = (b * mul_b) % div;} while(b%8);
        if((a & 0xFFFF) == (b & 0xFFFF)) count++;
    }
    std::cout << count << '\n';
}

