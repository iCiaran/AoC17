#include <iostream>
#include <fstream>
#include <iterator>

int main()
{
    std::ifstream file ("../input.txt");
    std::string line;
    std::getline(file, line);
    int jump = stoi(line);
    int ans, index = 0;

    for(int i = 1; i <= 50000000; ++i)
    {
        index = (index + jump + 1) % i;
        if(!index) ans = i;
    }

    std::cout << ans << '\n';
}

