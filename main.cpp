#include <iostream>
#include "my_tree.h"
using namespace std;

int main(int argc, char **argv)
{
    std::vector<char> input = {'A', 'B', 'C', 'F', 'G'};
    std::vector<char> result = {'A', 'B', 'C', 'E', 'F', 'G'};

    MyTree<char> my_tree = MyTree<char>(input);
    my_tree.insert('E');

    std::cout << my_tree.get_size() << std::endl;
    std::cout << my_tree.get_height() << std::endl;
    std::cout<< my_tree.isBST()<<std::endl;
    my_tree.inorder_rec();
}
