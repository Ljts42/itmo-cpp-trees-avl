#pragma once

#include <vector>

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
    Node * root = nullptr;
    std::size_t treeSize = 0;

    bool search(int, Node *) const;

    std::size_t getHeight(Node *) const;
    void recalcHeight(Node *);

    Node * rotateLeft(Node *);
    Node * rotateRight(Node *);
    Node * balance(Node *);

    bool insert(int, Node *&);
    bool remove(int, Node *&);

    void values(std::vector<int> &, Node *) const;

    void clear(Node *);
};
