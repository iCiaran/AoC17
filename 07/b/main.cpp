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

int get_tree_weight(std::map<std::string, node*> nodes, std::string n){
    if(nodes[n]->children.size() == 0)
    {
        return nodes[n]->value;
    }else{
        int total = nodes[n]->value;
        for(const auto& s : nodes[n]->children)
        {
            total += get_tree_weight(nodes, s);
        }
        return total;
    }
}

std::string find_unbalanced_tree(std::map<std::string, node*> nodes, std::string root)
{
    std::map<std::string, int> weights;
    for(const auto& s : nodes[root]->children)
    {
        int w = get_tree_weight(nodes, s);
        weights.insert({s,w});
    }
    
    std::map<int,int> dupes;

    for(const auto& s : nodes[root]->children)
    {
        if(!dupes.insert({weights[s], 1}).second)
            dupes[weights[s]]++;
    }

    int weight;

    for(const auto& i : dupes)
    {
        if(i.second == 1) 
        {
            weight = i.first;
            break;
        }
    }
    
    for(const auto& s : nodes[root]->children)
    {
        if(weights[s] == weight) return s;
    }
    return "0";
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
    
    std::string root = *potentials.begin();
    
    bool flag = false;

    std::string next = root;
    std::string par  = root;    
    while(nodes[next]->children.size() > 0)
    {
        std::string temp = find_unbalanced_tree(nodes, next);
        if(temp == "0") {
            flag = true;
            break;
        } 
        par = next;
        next = temp;
    }

    std::cout << next << '\n';
    std::cout << par << '\n';

    if(flag)
    {
        std::map<std::string, int> weights;
        for(const auto& s : nodes[par]->children)
        {
            int w = get_tree_weight(nodes, s);
            weights.insert({s,w});
            std::cout << s << " - " << w << '\n';
        }
        int i = 0;
        if(weights[next] == weights[nodes[par]->children[i]]) i++;

        int diff = weights[next] - weights[nodes[par]->children[i]];

        int new_weight = nodes[next]->value - diff;

        std::cout << new_weight << '\n';

    }else{
        //TODO: One of children is wrong weight
    }
}

