#include <iostream>
#include <cassert>

int numberOfOnes(int number, int ones = 0);

int main() {
    assert(0 == numberOfOnes(0));
    assert(1 == numberOfOnes(1));
    assert(1 == numberOfOnes(2));
    assert(2 == numberOfOnes(3));
    assert(1 == numberOfOnes(4));
    assert(2 == numberOfOnes(5));
    assert(2 == numberOfOnes(6));
    assert(3 == numberOfOnes(7));
    assert(1 == numberOfOnes(8));
    assert(2 == numberOfOnes(9));
    assert(2 == numberOfOnes(10));
    assert(3 == numberOfOnes(11));
    assert(2 == numberOfOnes(12));
    assert(3 == numberOfOnes(13));
    assert(3 == numberOfOnes(14));
    assert(4 == numberOfOnes(15));
    assert(1 == numberOfOnes(16));

    std::cout << "All tests have passed!" << std::endl;
}

int numberOfOnes(int number, int ones) {
    if (number == 0) {
        return ones;
    } else {
        return numberOfOnes(number & (number - 1), ones + 1);
    }
}