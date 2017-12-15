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

    const int mul_a = 16807;
    const int mul_b = 48271;
    const int div = 2147483647;
    int count = 0;
    long int prod;
    
    for(int i=0; i<5000000; ++i)
    {
        do{
            prod = a * mul_a;
            a = (prod & 0x7fffffff) + (prod >> 31);
            a = a >> 31 ? a - 0x7fffffff : a;
        } while(a&3);
        do{
            prod = b * mul_b;
            b = (prod & 0x7fffffff) + (prod >> 31);
            b = b >> 31 ? b - 0x7fffffff : b;
        } while(b&7);
        if((a & 0xFFFF) == (b & 0xFFFF)) count++;
    }
    std::cout << count << '\n';
}

