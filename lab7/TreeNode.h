#ifndef LAB7_TREENODE_H
#define LAB7_TREENODE_H


#include <iostream>

class TreeNode {
public:
    int weight;
    char value;
    TreeNode * leftNode;
    TreeNode * rightNode;
    TreeNode() {
        weight = 0;
        leftNode = nullptr;
        rightNode = nullptr;
        char value = 0;
    }

    TreeNode(char v, int w) : value(v), weight(w) {
        leftNode = nullptr;
        rightNode = nullptr;
    }

    TreeNode(TreeNode const & other) {
        weight = other.weight;
        leftNode = other.leftNode;
        rightNode = other.rightNode;
        value = other.value;
    }

    bool operator<(const TreeNode & rhs) const {
        return weight < rhs.weight;
    }
};

class Tree {
public:
    TreeNode * root;
    Tree() {
        root = nullptr;
    }

    Tree(char value, int weight) {
        root = new TreeNode(value, weight);
    }

    void merge(Tree & other) {
        TreeNode * leftChild = root;
        root = new TreeNode();
        root->leftNode = leftChild;
        root->rightNode = other.root;
        root->weight = leftChild->weight + other.root->weight;
        other.root = nullptr;
    }

    int getWeight() const {
        return root == nullptr ? -1 : root->weight;
    }

    ~Tree() {
        if (root != nullptr)
            delete(root);
    }

    bool operator<(const Tree & rhs) const {
        return getWeight() < rhs.getWeight();
    }
};

#endif
