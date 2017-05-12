#ifndef LAB7_FILEDECOMPRESSOR_H
#define LAB7_FILEDECOMPRESSOR_H


#include <string>
#include "TreeNode.h"

using namespace std;

class FileDecompressor {
    string compressedFilePath;
    string outputFilePath;

public:
    FileDecompressor(string compressed, string output) :
            compressedFilePath(compressed),  outputFilePath(output) {}

    void decompress();

private:
    void readFromFile(const string & filePath, map<char, vector<bool>> & paths, vector<bool> & bits);
    void buildTreeFromPaths(const map<char, vector<bool>> &pathsFromFile, const Tree &tree);
    void outputDecodedText(const string & path, Tree & tree, vector<bool> bits);
    void parseCharacterPath(map<char, vector<bool>> & paths, ifstream & inFile);

};


#endif //LAB7_FILEDECOMPRESSOR_H
