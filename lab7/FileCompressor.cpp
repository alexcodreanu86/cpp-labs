#include <map>
#include <fstream>
#include <streambuf>

#include "FileCompressor.h"
#include "TreeNode.h"
#include "BinaryHeap.h"

using namespace std;

static char NODES_SEPARATOR = '&';
static char CHAR_PATH_SEPARATOR = '|';

void FileCompressor::compress() {
    string input = fileContents(inputFilePath);
    map<char, int> charsOccurrences = getCharsOccurrances(input);
    Tree * tree = buildTree(charsOccurrences);
    map<char, string> paths;
    buildPaths(tree->root, paths);
    vector<bool> bits = encryptBits(paths, input);
    writeToFile(outputFilePath, paths, bits);
}

string FileCompressor::fileContents(const string &filePath) {
    ifstream inputFile(filePath);
    string contents((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    return contents;
}

map<char, int> FileCompressor::getCharsOccurrances(const string & input) {
    map<char, int> charsOccurrences;
    for (auto character : input)
        charsOccurrences[character]++;

    return charsOccurrences;
}

Tree * FileCompressor::buildTree(map<char, int> &charsOccurrences) {
    BinaryHeap< Tree * > heap;
    for (auto charWithCount: charsOccurrences) {
        Tree * node = new Tree(charWithCount.first, charWithCount.second);
        heap.insert(node);
    }

    while (heap.getCurrentSize() > 1) {
        Tree * smallest;
        heap.deleteMin(smallest);
        Tree * secondSmallest;
        heap.deleteMin(secondSmallest);

        smallest->merge(*secondSmallest);
        delete secondSmallest;
        heap.insert(smallest);
    }
    Tree * tree;
    heap.deleteMin(tree);
    return tree;
}

void FileCompressor::buildPaths(TreeNode * node, map<char, string> & paths, string currentPath) {
    if (node->value > '\0') {
        paths[node->value] = currentPath;
    } else {
        buildPaths(node->leftNode, paths, currentPath + '0');
        buildPaths(node->rightNode, paths, currentPath + '1');
    }
}

vector<bool> FileCompressor::encryptBits(map<char, string> &paths, const string &input) {
    vector<bool> bits;
    for (auto currentCharacter : input) {
        string path = paths[currentCharacter];
        for(auto pathElement : path) {
            if (pathElement != 0)
                bits.push_back(pathElement == '1');
        }
    }

    return bits;
}

void FileCompressor::writeToFile(const string &filePath, const map<char, string> &paths, const vector<bool> &bits) {
    ofstream outFile;
    outFile.open(filePath);
    outFile << paths.size() << NODES_SEPARATOR;
    for (auto charPath : paths) {
        outFile << charPath.first << CHAR_PATH_SEPARATOR << charPath.second << NODES_SEPARATOR;
    }

    outFile << bits.size() << NODES_SEPARATOR;

    writeBitsToFile(outFile, bits);

    outFile.close();
}

void FileCompressor::writeBitsToFile(ofstream &outFile, const vector<bool> &bits) {
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
