#include <string>
#include <iostream>

int myHash(std::string & key, int tableSize) {
    int hashVal = 0;

    std::cout << "Key Length " << key.length() << '\n';
    for (int i = 0; i < key.length(); i++) {
        hashVal = 37 * hashVal + key[i];
    }

    hashVal %= tableSize;
    if (hashVal < 0) {
        hashVal += tableSize;
    }
    return hashVal;
}

int main () {
    std::string input = "Hen";
    std::cout << "Value: " << myHash(input, 211) << '\n';
}
