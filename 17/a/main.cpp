#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <memory>

struct node 
{
    int data;
    std::shared_ptr<node> next;
};

std::shared_ptr<node> add_node(std::shared_ptr<node> current, int data)
{
    std::shared_ptr<struct node> n = std::make_shared<node>();
    n -> data = data;
    n -> next = current -> next;
    current -> next = n;
    return n;
}

int main()
{
    std::ifstream file ("../input.txt");
    std::string line;
    std::getline(file, line);
    int jump = stoi(line);

    std::shared_ptr<node> current = std::make_shared<node>();
    current -> data = 0;
    current -> next = current;

    for(int i = 1; i <= 2017; ++i)
    {
        for(int j = 0; j < jump; ++j)
        {
            current = current -> next;
        }

        current = add_node(current, i);
    }

    std::cout << current -> next -> data << '\n';

}

