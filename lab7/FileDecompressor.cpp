#include <vector>
#include <map>
#include <fstream>

#include "FileDecompressor.h"

using namespace std;

static char NODES_SEPARATOR = '&';

void readBitsFromFile(ifstream & inFile, int numberOfBits, vector<bool> & bits) {
    while (bits.size() < numberOfBits) {
        char currentChar;
        inFile.get(currentChar);
        for (int x = 0; x < 8; x++) {
            if (bits.size() < numberOfBits) {
                bits.push_back((bool) ((currentChar >> x) & 0x01));
            }
        }
    }
}

void printPaths(map<char, vector<bool>> & paths) {
    for (auto path : paths) {
        cout << "Char: " << path.first << " path: ";
        for (auto bit : path.second) {
            cout << bit;
        }
        cout << '\n';
    }

}

void printTree(TreeNode * node, string currentPath = "") {

    if (node->value > '\0') {
        cout << "After " << node->value << " path " << currentPath << '\n';
    } else {
        printTree(node->leftNode, currentPath + '0');
        printTree(node->rightNode, currentPath + '1');
    }
}

void FileDecompressor::decompress() {
    map<char, vector<bool> > pathsFromFile;

    vector<bool> bits;
    readFromFile(compressedFilePath, pathsFromFile, bits);
    Tree tree(0, 0);
    buildTreeFromPaths(pathsFromFile, tree);

    outputDecodedText(outputFilePath, tree, bits);
}

void FileDecompressor::readFromFile(const string & filePath, map<char, vector<bool>> & paths, vector<bool> & bits) {
    ifstream inFile;
    inFile.open(filePath);
    int numberOfCharacters;
    inFile >> numberOfCharacters;
    char separator;
    inFile.get(separator);
    for(int i = 0; i < numberOfCharacters; i++) {
        parseCharacterPath(paths, inFile);
    }

    int numberOfBits;
    inFile >> numberOfBits;
    inFile.get(separator);
    readBitsFromFile(inFile, numberOfBits, bits);
    inFile.close();
}


void buildPathForTreeNode(TreeNode * node, vector<bool> paths, char value) {
    for (auto bit : paths) {
        if (bit) {
            if (node->rightNode == nullptr)
                node->rightNode = new TreeNode();
            node = node->rightNode;
        } else {
            if (node->leftNode == nullptr)
                node->leftNode = new TreeNode();
            node = node->leftNode;
        }
    }
    node->value = value;
}


void FileDecompressor::buildTreeFromPaths(const map<char, vector<bool>> &pathsFromFile, const Tree &tree) {
    for (auto path : pathsFromFile) {
        buildPathForTreeNode(tree.root, path.second, path.first);
    }
}
void FileDecompressor::outputDecodedText(const string & path, Tree & tree, vector<bool> bits) {
    ofstream outFile;
    outFile.open(path);

    TreeNode * currentNode = tree.root;
    for (auto bit : bits) {
        if (bit)
            currentNode = currentNode->rightNode;
        else
            currentNode = currentNode->leftNode;

        if (currentNode->value != 0) {
            outFile << currentNode->value;
            currentNode = tree.root;
        }
    }

    outFile.close();
}

void FileDecompressor::parseCharacterPath(map<char, vector<bool>> & paths, ifstream & inFile) {
    char character;
    inFile.get(character);
    char separator;
    inFile.get(separator);

    vector<bool> path;
    char currentChar;
    inFile.get(currentChar);
    while (currentChar != NODES_SEPARATOR) {
        path.push_back(currentChar == '1');
        inFile.get(currentChar);
    }

    paths[character] = path;
}

