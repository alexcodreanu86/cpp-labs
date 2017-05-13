#ifndef LAB7_TREENODE_H
#define LAB7_TREENODE_H


#include <iostream>

class TreeNode {
public:
    int weight;
    char value;
    TreeNode * leftNode;
    TreeNode * rightNode;
    TreeNode() :  leftNode(nullptr), rightNode(nullptr),
                  weight(0), value('\0') { }

    TreeNode(char v, int w) : value(v), weight(w),
                              leftNode(nullptr), rightNode(nullptr) {}

    TreeNode(TreeNode const & other) : leftNode(other.leftNode),
                                       rightNode(other.rightNode),
                                       weight(other.weight),
                                       value(other.value) {}

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
        root = new TreeNode(0, leftChild->weight + other.root->weight);
        root->leftNode = leftChild;
        root->rightNode = other.root;
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
