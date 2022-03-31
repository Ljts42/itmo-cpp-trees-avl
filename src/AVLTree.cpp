#include "AVLTree.h"

bool AVLTree::contains(int value) const
{
    return search(value, root);
}

bool AVLTree::search(int value, Node * node) const
{
    if (!node) {
        return false;
    }
    if (value < node->value) {
        return search(value, node->left);
    }
    if (value > node->value) {
        return search(value, node->right);
    }
    return true;
}

std::size_t AVLTree::getHeight(Node * node) const
{
    if (!node) {
        return 0;
    }
    return node->height;
}

void AVLTree::recalcHeight(Node * node)
{
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

AVLTree::Node * AVLTree::rotateLeft(Node * node)
{
    Node * tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    recalcHeight(node);
    recalcHeight(tmp);
    return tmp;
}

AVLTree::Node * AVLTree::rotateRight(Node * node)
{
    Node * tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    recalcHeight(node);
    recalcHeight(tmp);
    return tmp;
}

AVLTree::Node * AVLTree::balance(Node * node)
{
    if (!node) {
        return nullptr;
    }
    recalcHeight(node);

    if (getHeight(node->left) >= getHeight(node->right) + 2) {
        if (getHeight(node->left->right) > getHeight(node->left->left)) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (getHeight(node->right) >= getHeight(node->left) + 2) {
        if (getHeight(node->right->left) > getHeight(node->right->right)) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}

bool AVLTree::insert(int value)
{
    return insert(value, root);
}

bool AVLTree::insert(int value, Node *& node)
{
    if (!node) {
        node = new Node(value);
        treeSize++;
    }
    else if (value < node->value && insert(value, node->left)) {
        node->left = balance(node->left);
    }
    else if (value > node->value && insert(value, node->right)) {
        node->right = balance(node->right);
    }
    else {
        return false;
    }
    return true;
}

bool AVLTree::remove(int value)
{
    if (root && remove(value, root)) {
        treeSize--;
        return true;
    }
    return false;
}

bool AVLTree::remove(int value, Node *& node)
{
    if (!node) {
        return false;
    }

    if (value == node->value) {
        if (!node->right) {
            node = node->left;
            return true;
        }

        Node * tmp;
        for (tmp = node->right; tmp->left; tmp = tmp->left)
            ;

        node->value = tmp->value;
        remove(node->value, node->right);
        node = balance(node);
    }
    else if (value < node->value && remove(value, node->left)) {
        node->left = balance(node->left);
    }
    else if (value > node->value && remove(value, node->right)) {
        node->right = balance(node->right);
    }
    else {
        return false;
    }
    return true;
}

std::size_t AVLTree::size() const
{
    return treeSize;
}

bool AVLTree::empty() const
{
    return size() == 0;
}

std::vector<int> AVLTree::values() const
{
    std::vector<int> result;
    values(result, root);
    return result;
}

void AVLTree::values(std::vector<int> & result, Node * node) const
{
    if (!node) {
        return;
    }

    values(result, node->left);
    result.push_back(node->value);
    values(result, node->right);
}

AVLTree::~AVLTree()
{
    clear(root);
}

void AVLTree::clear(Node * node)
{
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}