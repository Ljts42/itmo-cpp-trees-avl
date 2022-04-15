#include "AVLTree.h"

bool AVLTree::contains(int value) const
{
    return search(value, root);
}

bool AVLTree::search(int value, Node * node)
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

std::size_t AVLTree::getHeight(Node * node)
{
    return (!node) ? 0 : node->height;
}

void AVLTree::recalcHeight(Node * node)
{
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

AVLTree::Node * AVLTree::rotateLeft(Node * node)
{
    Node * rightChild = node->right;
    node->right = rightChild->left;
    rightChild->left = node;
    recalcHeight(node);
    recalcHeight(rightChild);
    return rightChild;
}

AVLTree::Node * AVLTree::rotateRight(Node * node)
{
    Node * leftChild = node->left;
    node->left = leftChild->right;
    leftChild->right = node;
    recalcHeight(node);
    recalcHeight(leftChild);
    return leftChild;
}

AVLTree::Node * AVLTree::balance(Node * node)
{
    if (!node) {
        return nullptr;
    }
    recalcHeight(node);
    int difference = getHeight(node->left) - getHeight(node->right);
    if (difference == 2) {
        if (getHeight(node->left->right) > getHeight(node->left->left)) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    else if (difference == -2) {
        if (getHeight(node->right->left) > getHeight(node->right->right)) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}

bool AVLTree::insert(int value)
{
    bool result = insert(value, root);
    if (result) {
        treeSize++;
    }
    return result;
}

bool AVLTree::insert(int value, NodePtr & node)
{
    bool result = (node == nullptr);
    if (result) {
        delete node;
        node = new Node(value);
    }
    else if (value < node->value) {
        result = insert(value, node->left);
    }
    else if (value > node->value) {
        result = insert(value, node->right);
    }
    node = balance(node);
    return result;
}

int AVLTree::findMin(Node * node)
{
    while (node->left) {
        node = node->left;
    }
    return node->value;
}

bool AVLTree::remove(int value)
{
    bool result = remove(value, root);
    if (result) {
        treeSize--;
    }
    return result;
}

bool AVLTree::remove(int value, NodePtr & node)
{
    if (!node) {
        return false;
    }

    bool result = (value == node->value);
    if (result) {
        if (!node->right) {
            Node * leftChild = node->left;
            delete node;
            node = leftChild;
            return true;
        }
        node->value = findMin(node->right);
        remove(node->value, node->right);
    }
    else if (value < node->value) {
        result = remove(value, node->left);
    }
    else if (value > node->value) {
        result = remove(value, node->right);
    }
    node = balance(node);
    return result;
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
    result.reserve(size());
    values(result, root);
    return result;
}

void AVLTree::values(std::vector<int> & result, Node * node)
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