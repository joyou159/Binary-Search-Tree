#ifndef MY_TREE_H
#define MY_TREE_H

#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <limits.h>
#include <cmath>
template <class T>
struct Node
{
    T data;
    Node *left = nullptr;
    Node *right = nullptr;

    Node(T data) : data(data) {}
};

template <class T>
class MyTree
{
private:
    Node<T> *root; // pointer to the beginning of the tree

protected:                                                     // utility functions which are invoked in the main member functions of the class
    Node<T> *drawTree(std::vector<T> &el, int start, int end); // such function construct a BST of a vector given the starting and ending indcies of the vector, or the sub-vector
    void insertInSubTree(Node<T> *ptr, T key);                 // insert a new key in the BST given the key and the root of the sub-tree
    Node<T> *find(Node<T> *ptr, T key);                        // such function search for specific key in the BST given the value and the root of the subtree, returns pointer such node in the BST
    Node<T> *seperate(Node<T> *ptr, T key);                    // such function seperates the node of given key value from the BST, return pointer to the place where the seperation has occurred
    Node<T> *leftmostLeaf(Node<T> *ptr);                       // such function returns the mostleft node of a BST, it helps in the case of seperating a node of 2 children, and return pointer to the place where the seperation has occurred
    bool compare(Node<T> *ptr);                                // such function makes sure that the given tree, is BST by passing the root of such subtree.
    bool isSubtreeGreater(Node<T> *ptr, T key);                // such function makes sure that any key in the given subtree is greater than the given key
    bool isSubtreeLesser(Node<T> *ptr, T key);                 // such function makes sure that any key in the given subtree is lesser than the given key
    int height(Node<T> *ptr);                                  // such function return the height of given subtree
    void inorder(Node<T> *ptr, std::vector<T> &vect);          // such function traverses the BST recursively in inorder manner, and stores its keys in referenced vector.
    void preorder(Node<T> *ptr, std::vector<T> &vect);         // such funtion traverses the BST recursively in preorder manner, and store its keys in referenced vector.
    void postorder(Node<T> *ptr, std::vector<T> &vect);        // such funtion traverses the BST recursively in postorder manner, and store its keys in referenced vector.
    std::vector<T> inorderPouring(Node<T> *ptr);               // such function traverses the BST iteratively in inorder manner, return its keys stored in vector using one stack.
    std::vector<T> postorderPouring(Node<T> *ptr);             // such function traverses the BST iteratively in postorder manner, return its keys stored in vector using 2 stack.
    std::vector<T> preorderPouring(Node<T> *ptr);              // such function traverses the BST iteratively in preorder manner, return its keys stored in vector using one stack.
    std::vector<Node<T> *> PostorderClear(Node<T> *ptr);       // like the postorderPouring function, but instead of returning vector of keys, its returns vector of pointers.
    int treeSize(Node<T> *ptr);                                // return the size of Binary Search subtree
    std::vector<T> levelOrder(Node<T> *ptr);                   // such function traverses the BST iteratively in breadth order manner, return its keys stored in vector using one queue

public:
    MyTree(Node<T> *ptr = nullptr) : root(ptr) {} // default constructor
    MyTree(std::vector<T> elements)               // vector-based constructor
    {
        sort(elements.begin(), elements.end()); // sorting the entries of the vector to comply with the properties of the BST
        root = drawTree(elements, 0, elements.size() - 1);
    }

    void insert(T key)
    {
        insertInSubTree(root, key);
    }

    void insert(const Node<T> node)
    {
        insertInSubTree(root, node->data);
    }

    const Node<T> *search(T key)
    {
        return find(root, key);
    }

    const Node<T> *delete_node(T key)
    {
        return seperate(root, key);
    }

    const Node<T> *delete_node(const Node<T> node)
    {
        return seperate(root, node->data);
    }

    bool isBST()
    {
        return compare(root);
    }

    std::vector<T> inorder_rec()
    {
        std::vector<T> inorder_Vect;
        inorder(root, inorder_Vect);
        return inorder_Vect;
    }

    std::vector<T> preorder_rec()
    {
        std::vector<T> preorder_Vect;
        preorder(root, preorder_Vect);
        return preorder_Vect;
    }

    std::vector<T> postorder_rec()
    {
        std::vector<T> postorder_Vect;
        postorder(root, postorder_Vect);
        return postorder_Vect;
    }

    std::vector<T> inorder_it()
    {
        return inorderPouring(root);
    }

    std::vector<T> preorder_it()
    {
        return preorderPouring(root);
    }

    std::vector<T> postorder_it()
    {
        return postorderPouring(root);
    }

    std::vector<T> breadth_traversal()
    {
        return levelOrder(root);
    }

    int get_size()
    {
        return treeSize(root);
    }

    int get_height()
    {
        return height(root) - 1;
    }

    void clear()
    {

        std::vector<Node<T> *> cl;
        cl = PostorderClear(root);
        for (int i = 0; i < cl.size(); i++)
            free(cl[i]);

        root = nullptr;
    }

    ~MyTree()
    {
        std::vector<Node<T> *> cl;
        cl = PostorderClear(root);
        for (int i = 0; i < cl.size(); i++)
        {
            free(cl[i]);
        }
    }
};
template <class T>
Node<T> *MyTree<T>::drawTree(std::vector<T> &el, int start, int end)
{
    if (start > end) // base case
    {
        return NULL;
    }
    int mid = ceil((start + end) / 2.0);       // considering the middle element of the sorted vector the as the root, in case of even number of elements we ceil the value to get an index towards the ened of the vector.
    Node<T> *temp = new Node<T>(el[mid]);      // creating a node and assign its key value with the element of the vector at this mid index
    temp->left = drawTree(el, start, mid - 1); // recursive call to the left subtree with shrinked limits, start and end indices
    temp->right = drawTree(el, mid + 1, end);  // recursive call to the right subtree with shrinked limits, start and end indices
    return temp;
}
template <class T>
void MyTree<T>::insertInSubTree(Node<T> *ptr, T key)
{
    Node<T> *node = new Node<T>(key); // create the node and assign its data with the key value.
    if (!ptr)                         // if the BST is empty, then the inserted element is considered to be the root.
    {
        root = node;
        return;
    }
    // if not we then start to iterate the whole tree searching for the appropriate position for insertion
    Node<T> *pre = nullptr; // previous pointer to retrieve the node, which we are going to insert the new node as its child
    Node<T> *temp = ptr;    // iterative pointer
    while (temp)
    {
        if (temp->data > key) // for left subtree with temp as root
        {
            pre = temp;
            temp = temp->left;
        }
        else if (temp->data < key) // for right subtree with temp as root
        {
            pre = temp;
            temp = temp->right;
        }
    }
    // after reaching the position of insertion, which is one of the children of pre from last loop
    if (pre->data > key) // as left child of pre
    {
        pre->left = node;
    }
    else // as right child of pre
        pre->right = node;
}
template <class T>
Node<T> *MyTree<T>::find(Node<T> *ptr, T key)
{
    if (ptr == nullptr) // base case
    {
        return nullptr;
    }
    if (ptr->data == key) // if the node we are looking for is the root
    {
        return ptr;
    }
    else if (ptr->data > key) // for left subtree of ptr
    {
        return find(ptr->left, key); // recursive call on the left child
    }
    else // for right subtree of ptr
    {
        return find(ptr->right, key); // recursive call on the right child
    }
}
template <class T>
Node<T> *MyTree<T>::seperate(Node<T> *ptr, T key)
{
    if (ptr == nullptr) // base case
    {
        return NULL;
    }

    if (ptr->data > key) // for left subtree for further searching
    {
        ptr->left = seperate(ptr->left, key);
    }
    else if (ptr->data < key) // for right subtree for further searching
    {
        ptr->right = seperate(ptr->right, key);
    }
    else // when the node is found
    {
        if (ptr->left == nullptr && ptr->right == nullptr) // if it has no children
            return NULL;

        else if (ptr->left == nullptr) // if it has right child
        {
            Node<T> *temp = ptr->right;
            delete ptr;
            return temp;
        }
        else if (ptr->right == nullptr) // if it has left child
        {
            Node<T> *temp = ptr->left;
            delete ptr;
            return temp;
        }                                              // if it has two children
        Node<T> *temp = leftmostLeaf(ptr->right);      // get the most left node in the right subtree of the current root
        ptr->data = temp->data;                        // swap key values
        ptr->right = seperate(ptr->right, temp->data); // then seperate the node as an external node
    }
    return ptr; // return the positon at which the removal is done
}
template <class T>
Node<T> *MyTree<T>::leftmostLeaf(Node<T> *ptr)
{
    Node<T> *cur = ptr;
    while (cur->left != nullptr) // iterate until reaching the most left node in the given subtree
        cur = cur->left;
    return cur;
}
template <class T>
bool MyTree<T>::compare(Node<T> *ptr)
{
    if (ptr == nullptr) // base case
    {
        return true;
    }
    if (isSubtreeGreater(ptr->right, ptr->data) && /* making sure that the BST is complying with the properties of the standard BST, and keeping checking this for all the descendents of the given root */
        isSubtreeLesser(ptr->left, ptr->data) &&
        compare(ptr->left) && compare(ptr->right))
        return true;
    else
        return false;
}
template <class T>
bool MyTree<T>::isSubtreeGreater(Node<T> *ptr, T key)
{
    if (ptr == nullptr) // base case
        return true;
    if (ptr->data > key && isSubtreeGreater(ptr->left, key) && isSubtreeGreater(ptr->right, key)) // making sure that all the keys of given subtree are greater than specific value
        return true;
    else
        return false;
}
template <class T>
bool MyTree<T>::isSubtreeLesser(Node<T> *ptr, T key)
{
    if (ptr == nullptr) // base case
        return true;
    if (ptr->data < key && isSubtreeLesser(ptr->left, key) && isSubtreeLesser(ptr->right, key)) // making sure that all the keys of given subtree are lesser than specific value
        return true;
    else
        return false;
}
template <class T>
int MyTree<T>::height(Node<T> *ptr) // return the height of a subtree rooted at ptr, starting counting from 1
{
    if (ptr == NULL) // base case a
    {
        return 0;
    }
    int left_height = height(ptr->left);   // the height of the left subtree
    int right_height = height(ptr->right); // the height of the right subtree

    if (left_height > right_height) // compare the two heights and then pick the highest one and adding 1 for counting the root node
    {
        return (1 + left_height);
    }
    else
    {
        return (1 + right_height);
    }
}
template <class T>
void MyTree<T>::inorder(Node<T> *ptr, std::vector<T> &vect)
{
    if (ptr == nullptr) // base case
        return;

    inorder(ptr->left, vect);  // recursive calling on the left child of ptr
    vect.push_back(ptr->data); // pushing the data in the referenced vector in the following order (left -> parent -> right)
    inorder(ptr->right, vect); // recursive calling on the right child of ptr
}
template <class T>
void MyTree<T>::preorder(Node<T> *ptr, std::vector<T> &vect)
{
    if (ptr == nullptr) // base case
        return;
    vect.push_back(ptr->data);  // pushing the data in the referenced vector in the following order (parent -> left -> right)
    preorder(ptr->left, vect);  // recursive calling on the left child of ptr
    preorder(ptr->right, vect); // recursive calling on the right child of ptr
}
template <class T>
void MyTree<T>::postorder(Node<T> *ptr, std::vector<T> &vect)
{
    if (ptr == nullptr) // base case
        return;
    postorder(ptr->left, vect);  // recursive calling on the left child of ptr
    postorder(ptr->right, vect); // recursive calling of the right child of ptr
    vect.push_back(ptr->data);   // pushing the data in the referenced vector in the following order (left -> right -> parent)
}
template <class T>
std::vector<T> MyTree<T>::postorderPouring(Node<T> *ptr) // pouring signifies that we deal with the stack as a glass in which we are pouring our data out or into it
{
    std::vector<T> postorder_Vect; // the vector to be returned
    if (ptr == nullptr)            // if the BST is empty
    {
        return postorder_Vect; // return the non-initialized vector
    }
    std::stack<Node<T> *> s1, s2;
    Node<T> *temp = ptr;
    s1.push(temp);      // push the root of the BST in s1
    while (!s1.empty()) // as long as s1 is not empty
    {
        temp = s1.top();
        s1.pop();
        s2.push(temp);
        if (temp->left != nullptr)
        {
            s1.push(temp->left);
        }
        if (temp->right != nullptr)
        {
            s1.push(temp->right);
        }
    }
    while (!s2.empty()) // as long as s2 is not empty
    {
        postorder_Vect.push_back((s2.top())->data); // pushing the data in the node pointer
        s2.pop();
    }
    return postorder_Vect; // return data vector
}
template <class T>
std::vector<Node<T> *> MyTree<T>::PostorderClear(Node<T> *ptr) // such function is constructed specifically for clear member function and for the destructor of the class
{
    std::vector<Node<T> *> postorder_Vect; // the vector to be returned
    if (ptr == nullptr)                    // if the BST is empty
    {
        return postorder_Vect; // return non-inizialized vector
    }
    std::stack<Node<T> *> s1, s2;
    Node<T> *temp = ptr;
    s1.push(temp);
    while (!s1.empty()) // as long as s1 is not empty
    {
        temp = s1.top();
        s1.pop();
        s2.push(temp);
        if (temp->left != nullptr)
        {
            s1.push(temp->left); // starting off with the left subtree as its keys are the values which must be pushed fisrt
        }
        if (temp->right != nullptr)
        {
            s1.push(temp->right);
        }
    }
    while (!s2.empty()) // as long as s2 is not empty
    {
        postorder_Vect.push_back(s2.top());
        s2.pop();
    }
    return postorder_Vect; // return a vector of pointers for all the node in the BST
}
template <class T>
std::vector<T> MyTree<T>::preorderPouring(Node<T> *ptr)
{
    std::vector<T> preorder_Vect; // the vector to be returned
    if (ptr == nullptr)           // if the tree is empty
    {
        return preorder_Vect; // return non-initialized vector
    }
    std::stack<Node<T> *> s;
    Node<T> *temp = ptr;
    s.push(temp);
    while (!s.empty()) // as long as the stack is not empty
    {
        temp = s.top();
        s.pop();
        preorder_Vect.push_back(temp->data); // push the data of the node pointer in the vector
        if (temp->right != nullptr)
        {
            s.push(temp->right);
        }
        if (temp->left != nullptr)
        {
            s.push(temp->left);
        }
    }
    return preorder_Vect; // return vector of all key values in the BST
}
template <class T>
std::vector<T> MyTree<T>::inorderPouring(Node<T> *ptr)
{
    std::vector<T> inorder_Vect;
    if (ptr == nullptr) // if the tree is empty
    {
        return inorder_Vect; // return non-initialized vector
    }
    std::stack<Node<T> *> s;
    Node<T> *curr = ptr;
    while (curr != NULL || s.empty() == false)
    {
        // Reach the left most Node of the curr Node
        while (curr != NULL)
        {
            // place pointer to a tree node on  the stack before traversing the node's left subtree
            s.push(curr);
            curr = curr->left;
        }

        // Current must be NULL at this point
        curr = s.top();
        s.pop();
        inorder_Vect.push_back(curr->data);
        curr = curr->right;
    }
    return inorder_Vect; // return vector of all key values in the BST
}
template <class T>
int MyTree<T>::treeSize(Node<T> *ptr)
{
    if (ptr == nullptr) // base case
    {
        return 0;
    }
    int leftSide = treeSize(ptr->left);   // get the size of the left sub tree
    int rightSide = treeSize(ptr->right); // get the size of the right sub tree
    return (leftSide + rightSide + 1);    // add to the summation of them one for the root node
}
template <class T>
std::vector<T> MyTree<T>::levelOrder(Node<T> *ptr)
{
    std::vector<T> level_Vect;
    if (ptr == nullptr) // base case
    {
        return level_Vect; // return non-initializedd vector
    }
    std::queue<Node<T> *> q;
    q.push(ptr);
    while (!q.empty()) // if the q is not empty
    {
        Node<T> *temp = q.front();
        level_Vect.push_back(temp->data);
        q.pop();
        if (temp->left != nullptr)
        {
            q.push(temp->left);
        }
        if (temp->right != nullptr)
        {
            q.push(temp->right);
        }
    }
    return level_Vect; // return vector of all the key values of BST level by level
}
#endif
