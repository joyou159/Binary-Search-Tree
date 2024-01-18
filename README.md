# Binary Search Tree (BST) Implementation

## Overview

This C++ implementation of a Binary Search Tree (BST) provides various functionalities such as insertion, deletion, searching, and tree traversal (inorder, preorder, postorder, and level order). It includes methods to check if the tree is a valid BST and retrieve information like size and height.

## Usage

1. Include the `MyTree.h` file in your C++ project.

2. Create an instance of the `MyTree` class, either using the default constructor or providing a vector of elements.

    ```cpp
    // Example 1: Using the default constructor
    MyTree<int> bst;

    // Example 2: Creating a BST from a vector of elements
    std::vector<int> elements = {4, 2, 6, 1, 3, 5, 7};
    MyTree<int> bst(elements);
    ```

3. Perform various operations on the BST, such as insertion, deletion, searching, and traversal.

    ```cpp
    // Example: Inserting a key
    bst.insert(8);

    // Example: Deleting a key
    bst.delete_node(3);

    // Example: Searching for a key
    const Node<int>* result = bst.search(5);
    ```

4. Ensure proper cleanup by calling the `clear` method when done using the BST.

    ```cpp
    // Example: Clearing the BST
    bst.clear();
    ```

## Implementation Details

- The BST is implemented using a template class to allow for different data types.
- The `Node` struct represents a node in the BST, containing data and pointers to the left and right children.
- The implementation includes both recursive and iterative traversal methods.
- The `isBST` method checks if the tree is a valid Binary Search Tree.
- The `get_size` and `get_height` methods provide information about the size and height of the tree.
- The `clear` method deallocates memory used by the nodes.

## Contribution

Contributions are welcome! If you find any issues or have improvements, please open an issue or submit a pull request.

Happy coding! ❤️
