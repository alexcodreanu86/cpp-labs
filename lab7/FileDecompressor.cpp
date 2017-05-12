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

void FileDecompressor::decompress() {
    map<char, vector<bool> > pathsFromFile;

    size_t numberOfBits;
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


void FileDecompressor::buildTreeFromPaths(const map<char, vector<bool>> &pathsFromFile, const Tree &tree) {
    for (auto path : pathsFromFile) {
        TreeNode * lastNode = tree.root;
        for (auto bit : path.second) {
            if (bit) {
                if (lastNode->rightNode == nullptr)
                    lastNode->rightNode = new TreeNode;
                lastNode = lastNode->rightNode;
            } else {
                if (lastNode->leftNode == nullptr)
                    lastNode->leftNode = new TreeNode;
                lastNode = lastNode->leftNode;
            }
        }
        lastNode->value = path.first;
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

