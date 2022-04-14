#pragma once

#include <vector>

class AVLTree
{
public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~AVLTree();

private:
    struct Node
    {
        Node * left = nullptr;
        Node * right = nullptr;
        std::size_t height = 1;
        int value;

        Node() = default;
        Node(int value)
            : value(value)
        {
        }
    };
    using NodePtr = AVLTree::Node *;

    Node * root = nullptr;
    std::size_t treeSize = 0;

    static bool search(int, Node *);

    static std::size_t getHeight(Node *);
    static void recalcHeight(Node *);

    static Node * rotateLeft(Node *);
    static Node * rotateRight(Node *);
    static Node * balance(Node *);

    static bool insert(int, NodePtr &);

    static int findMin(Node *);
    static bool remove(int, NodePtr &);

    static void values(std::vector<int> &, Node *);

    static void clear(Node *);
};
