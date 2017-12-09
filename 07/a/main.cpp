#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>
#include <set>

struct node{
    int value;
    std::vector<std::string> children;
};

std::vector<std::string> split(const std::string& s) {
    std::istringstream iss{s};
    return std::vector<std::string>{std::istream_iterator<std::string>{iss}, {}};
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
    
    std::map<std::string, node*> nodes;
    std::set<std::string> potentials;
    std::set<std::string>::iterator iter;
    for(const auto& i : input)
    {
        std::vector<std::string> line = split(i);
        node* n = new node;
        std::string val = line[1].substr(1,line[1].length()-2);
        n->value = std::stoi(val);

        if(line.size() > 2)
        {
            potentials.insert(line[0]);
            for(int i = 3; i < line.size(); i++)
            {
                std::string temp = line[i];
                while(temp.back() == ' ' || temp.back() == ',')
                {
                    temp.pop_back();
                }

                n->children.push_back(temp);
            }
        }
        nodes.insert({line[0],n});
    }

    for(const auto& i : input)
    {
        std::string temp = split(i)[0];

        for(const auto& s: nodes[temp]->children)
        {
            potentials.erase(s);
        }
    }
    
    for(iter=potentials.begin(); iter!=potentials.end();++iter) {
        std::cout << *iter << '\n';
    }
}

