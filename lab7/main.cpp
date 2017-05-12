#include <iostream>
#include "FileCompressor.h"
#include "FileDecompressor.h"


int main() {
    FileCompressor compressor("in.txt", "encrypted.txt");
    compressor.compress();
    FileDecompressor decompressor("encrypted.txt", "result.txt");
    decompressor.decompress();
    std::cout << "\033[0;32m√ All tests have passed!!!\n\033[m";
}
