#ifndef LAB7_FILECOMPRESSOR_H
#define LAB7_FILECOMPRESSOR_H


#include <map>
#include <string>
#include <vector>
#include "TreeNode.h"

using namespace std;

class FileCompressor {
    std::string inputFilePath;
    std::string outputFilePath;

public:
    FileCompressor(std::string inputFile, std::string outputFile) :
            inputFilePath(inputFile), outputFilePath(outputFile) {}

    void compress();

private:
    string fileContents(const string &filePath);
    map<char, int> getCharsOccurrances(const string & input);
    Tree *buildTree(map<char, int> &charsOccurrences);
    void buildPaths(TreeNode * node, map<char, string> & paths, string currentPath = "");
    vector<bool> encryptBits(map<char, string> & paths, const string & input);
    void writeToFile(const string & filePath, const map<char, string> & paths, const vector<bool> & bits);
    void writeBitsToFile(ofstream & outFile, const vector<bool> & bits);
};


#endif //LAB7_FILECOMPRESSOR_H
