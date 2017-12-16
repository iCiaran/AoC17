#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>

std::vector<std::string> split(const std::string& s) {
    std::istringstream iss{s};
    std::string token;
    std::vector<std::string> tokens;

    while(std::getline(iss, token, ','))
    {
        tokens.push_back(token);
    }

    return tokens;
}

std::string spin(const std::string& in, int n)
{
    auto x = in.size();
    auto a = in.substr(0, x - n);
    auto b = in.substr(x - n, std::string::npos);
    return b + a;
}

std::string exchange(const std::string& in, int a, int b)
{
    std::string s = in;

    auto t = s[a];
    s[a] = s[b];
    s[b] = t;
    
    return s;
}

std::string partner(const std::string& in, char a, char b)
{
    std::string s = in;
    auto pa = s.find_first_of(a);
    auto pb = s.find_first_of(b);
    
    s[pa] = b;
    s[pb] = a;

    return s;
}

std::string do_loop(std::vector<std::string> input, std::string s)
{
    for(const auto& i : input)
    {
        if(i[0] == 's')
        {
            s = spin(s, stoi(i.substr(1, i.size())));
        }
        else if(i[0] == 'x')
        {
            auto d = i.find_first_of('/');
            s = exchange(s, stoi(i.substr(1,d-1)), stoi(i.substr(d+1, std::string::npos)));
        }
        else
        {
           s = partner(s, i[1], i[3]); 
        }
    }
    return s; 
}

int main()
{
    std::ifstream file ("../input.txt");
    std::vector<std::string> input;
    std::string line;
    
    std::getline(file, line);
    
    input = split(line);
    
    std::map<std::string, int> history;

    std::string s = "abcdefghijklmnop";
    int count = 0;
    int cycle = 0;
    
    while(count < 1000000000)
    {
        history.insert({s, count});
        count++;
        s = do_loop(input, s);
      
        if(history.count(s))
        {
            cycle = count - history[s];
            break;
        }
    }
    
    int n = 1000000000 % cycle;
    
    for(int i = 0; i < n; ++i)
    {
        s = do_loop(input, s);
    }

    std::cout << s << '\n';
}

