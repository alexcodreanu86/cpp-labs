#ifndef LAB7_HASHTABLEGENERATIONTEST_H
#define LAB7_HASHTABLEGENERATIONTEST_H

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <streambuf>

#include "TreeNode.h"
#include "BinaryHeap.h"

using namespace std;

static string NEW_LINE_CODE = "nl";
static string WHITE_SPACE_CODE = "ws";
static char NODES_SEPARATOR = '&';
static char CHAR_PATH_SEPARATOR = '|';

class HashTableGenerationTest {
public:
    static Tree *buildTree(map<char, int> &charsOccurrences) {
        BinaryHeap< Tree * > heap;
        for (auto charWithCount: charsOccurrences) {
            Tree * node = new Tree(charWithCount.first, charWithCount.second);
            heap.insert(node);
        }

        while (heap.getCurrentSize() > 1) {
            Tree * smallest;
            heap.deleteMin(smallest); Tree * secondSmallest;
            heap.deleteMin(secondSmallest);
            smallest->merge(*secondSmallest);
            delete secondSmallest;
            heap.insert(smallest);
        }
        Tree * tree;
        heap.deleteMin(tree);
        return tree;
    }

    static void buildPaths(TreeNode * node, map<char, string> & paths, string currentPath = "") {
        if (node->value > '\0') {
            paths[node->value] = currentPath;
        } else {
            buildPaths(node->leftNode, paths, currentPath + '0');
            buildPaths(node->rightNode, paths, currentPath + '1');
        }
    }

    static void printTree(TreeNode *node, string path = "") {
        if (node->rightNode != nullptr)
            printTree(node->rightNode, path + '1');

        if (node->leftNode != nullptr)
            printTree(node->leftNode, path + '0');

        if (node->value != 0)
            cout << "Node Value: " << node->value << " path: " << path << '\n';
    }

    static vector<bool> encryptBits(map<char, string> & paths, const string & input) {
        vector<bool> bits;
        cout << "PRINTING\n";
        for (auto currentCharacter : input) {
            string path = paths[currentCharacter];
            for(auto pathElement : path) {
                if (pathElement != 0)
                    bits.push_back(pathElement == '1');
            }
        }

        return bits;
    }

    static void writeToFile(const string & filePath, const map<char, string> & paths, const vector<bool> & bits) {
        ofstream outFile;
        outFile.open(filePath);
        outFile << paths.size() << NODES_SEPARATOR;
        for (auto charPath : paths) {
            outFile << charPath.first << CHAR_PATH_SEPARATOR << charPath.second << NODES_SEPARATOR;
        }
        outFile << '\n';
        outFile << bits.size() << '\n';

        writeBitsToFile(outFile, bits);

        outFile.close();
    }

    static void parseCharacterPath(map<char, vector<bool>> & paths, ifstream & inFile) {
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

    static void readFromFile(const string & filePath, map<char, vector<bool>> & paths, vector<bool> & bits) {
        ifstream inFile;
        inFile.open(filePath);
        int numberOfCharacters;
        inFile >> numberOfCharacters;
        char separator;
        inFile >> separator;
        for(int i = 0; i < numberOfCharacters; i++) {
            parseCharacterPath(paths, inFile);
        }

        int numberOfBits;
        inFile >> numberOfBits;
        readBitsFromFile(inFile, numberOfBits, bits);
        inFile.close();
    }

    static void test() {
        encodeInput("in.txt", "encrypted.txt");
        decodeFile("encrypted.txt", "result.txt");
        characterBits('a');
    }

    static void readBitsFromFile(ifstream & inFile, int numberOfBits, vector<bool> & bits) {
        while (bits.size() < numberOfBits) {
            unsigned char currentChar;
            inFile >> currentChar;
            for (int x = 0; x < 8; x++) {
                if (bits.size() < numberOfBits) {
                    bits.push_back((bool) ((currentChar >> x) & 0x01));
                }
            }
        }
    }

    static void writeBitsToFile(ofstream & outFile, const vector<bool> & bits) {

        int currentBit = 0;
        unsigned char buffer;
        for (auto bit: bits) {
            if (bit)
                buffer |= (0x1 << currentBit);
            currentBit++;
            if (currentBit == 8) {
                outFile << buffer;
                currentBit = 0;
                buffer = 0;
            }
        }

        while(currentBit < 8 && currentBit > 0) {
            buffer |= ((1 << currentBit++) & 0x01);
        }
        outFile << buffer;
    }

    static void characterBits(char character) {
        cout << "Character: " << character << ' ';
        cout << "bits: ";
        for (int i = 7; i >= 0; i--) {
            cout << ((character >> i) & 0x01);
        }
        cout << '\n';
    }

    static void decodeFile(const string &encodedFile, const string & outputFile) {
        map<char, vector<bool> > pathsFromFile;

        size_t numberOfBits;
        std::vector<bool> bits;
        readFromFile(encodedFile, pathsFromFile, bits);
        Tree tree(0, 0);
        buildTreeFromPaths(pathsFromFile, tree);

        outputDecodedText(outputFile, tree, bits);

    }

    static void outputDecodedText(const string & path, Tree & tree, vector<bool> bits) {
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

    static void buildTreeFromPaths(const map<char, vector<bool>> &pathsFromFile, const Tree &tree) {
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

    static string fileContents(const string & filePath) {
        ifstream inputFile(filePath);
        string contents((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
        return contents;
    }


private:
    static map<char, int> getCharsOccurrances(string input) {
        map<char, int> charsOccurrences;
        for (auto character : input)
            charsOccurrences[character]++;

        return charsOccurrences;
    }

    static void encodeInput(const string & inputFile, const string &outputFile) {
        string input = fileContents(inputFile);
        map<char, int> charsOccurrences = getCharsOccurrances(input);
        Tree * tree = buildTree(charsOccurrences);
        map<char, string> paths;
        buildPaths(tree->root, paths);
        vector<bool> bits = encryptBits(paths, input);
        writeToFile(outputFile, paths, bits);
    }

};

#endif
