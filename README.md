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

## Method Descriptions

### `drawTree(std::vector<T>& el, int start, int end)`

Constructs a BST from a sorted vector given the starting and ending indices of the vector or sub-vector.

### `insertInSubTree(Node<T>* ptr, T key)`

Inserts a new key into the BST given the key and the root of the sub-tree.

### `find(Node<T>* ptr, T key)`

Searches for a specific key in the BST given the value and the root of the subtree, returning a pointer to the corresponding node.

### `separate(Node<T>* ptr, T key)`

Separates the node with the given key value from the BST, returning a pointer to the place where the separation has occurred.

### `leftmostLeaf(Node<T>* ptr)`

Returns the leftmost node of a BST, helping in the case of separating a node with two children.

### `compare(Node<T>* ptr)`

Ensures that the given tree is a BST by passing the root of the subtree.

### `isSubtreeGreater(Node<T>* ptr, T key)`

Ensures that any key in the given subtree is greater than the given key.

### `isSubtreeLesser(Node<T>* ptr, T key)`

Ensures that any key in the given subtree is lesser than the given key.

### `height(Node<T>* ptr)`

Returns the height of the given subtree.

### `inorder(Node<T>* ptr, std::vector<T>& vect)`

Traverses the BST recursively in an inorder manner and stores its keys in the referenced vector.

### `preorder(Node<T>* ptr, std::vector<T>& vect)`

Traverses the BST recursively in a preorder manner and stores its keys in the referenced vector.

### `postorder(Node<T>* ptr, std::vector<T>& vect)`

Traverses the BST recursively in a postorder manner and stores its keys in the referenced vector.

### `inorderPouring(Node<T>* ptr)`

Traverses the BST iteratively in an inorder manner and returns its keys stored in a vector using one stack.

### `postorderPouring(Node<T>* ptr)`

Traverses the BST iteratively in a postorder manner and returns its keys stored in a vector using two stacks.

### `preorderPouring(Node<T>* ptr)`

Traverses the BST iteratively in a preorder manner and returns its keys stored in a vector using one stack.

### `PostorderClear(Node<T>* ptr)`

Similar to `postorderPouring` but returns a vector of pointers instead of keys, useful for clearing the tree.

### `treeSize(Node<T>* ptr)`

Returns the size of the Binary Search subtree.

### `levelOrder(Node<T>* ptr)`

Traverses the BST iteratively in breadth order manner and returns its keys stored in a vector using one queue.

## Contribution

Contributions are welcome! If you find any issues or have improvements, please open an issue or submit a pull request.

Happy coding! ❤️
