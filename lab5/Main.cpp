#include <vector>
#include <iostream>
#include <algorithm>
#include <random>
#include "BinaryHeap.h"
#include <time.h>
#include <iomanip>

using namespace std;

typedef float (*heapBuilder)(const vector<int> &);

void printHeap(const vector<int> &container, const string &type, heapBuilder build) {
    cout << type << " Times : " << setw(8) << build(container)  << " | ";
    cout << setw(8) << build(container) << " | ";
    cout << setw(8) << build(container) << " | ";
    cout << setw(8) << build(container) << " | ";
    cout << setw(8) << build(container) << "\n";
}

void printContainer(const string &containerDescription, const vector<int> &container) {
    cout << containerDescription << " container elements : [ ";
    string separator = "";
    for (auto element : container) {
        cout << separator << element;
        separator = ", ";
    }
    cout << " ]\n";
}

float insertIntoHeap(const vector<int> &container) {
    clock_t sortedTime;
    sortedTime = clock();
    BinaryHeap<int> heap;
    for (auto element : container) {
        heap.insert(element);
    }

    int min;
    heap.deleteMin(min);
    sortedTime = clock() - sortedTime;
    return min * sortedTime;
}

void insertAllIntoHeap(const vector<int> &sorted, const vector<int> &reversed, const vector<int> &shuffled) {
    cout << "****** INSERT INTO HEAP TIMES ******\n";
    printHeap(sorted, "sorted  ", insertIntoHeap);
    printHeap(shuffled, "shuffled", insertIntoHeap);
    printHeap(reversed, "reversed", insertIntoHeap);
    cout << "--------------------------------------------------\n";
}

float buildHeap(const vector<int> &container) {
    clock_t sortedTime;
    sortedTime = clock();
    BinaryHeap<int> heap(container);
    int min;
    heap.deleteMin(min);
    sortedTime = clock() - sortedTime;
    return min * ((float) sortedTime);
}

void buildAllHeaps(const vector<int> &sorted, const vector<int> &reversed, const vector<int> &shuffled) {
    cout << "****** BUILD HEAP TIMES ******\n";
    printHeap(sorted, "sorted  ", buildHeap);
    printHeap(shuffled, "shuffled", buildHeap);
    printHeap(reversed, "reversed", buildHeap);
}

int main() {
    int numberOfElements = 0;
    cout << "Insert the number of elements you want to add to the heap: ";
    cin >> numberOfElements;
    cout << '\n';
    vector<int> sortedElements;
    vector<int> reverseElements;
    vector<int> shuffledNumbers;
    for (int i = 0; i < numberOfElements; i++) {
        sortedElements.push_back(i + 1);
        shuffledNumbers.push_back(i + 1);
        reverseElements.push_back(numberOfElements - i);
    }

    shuffle(shuffledNumbers.begin(), shuffledNumbers.end(), std::default_random_engine());

    insertAllIntoHeap(sortedElements, reverseElements, shuffledNumbers);
    buildAllHeaps(sortedElements, reverseElements, shuffledNumbers);
}
