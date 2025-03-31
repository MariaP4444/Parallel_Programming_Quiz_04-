#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>
#include <cmath>

using namespace std;

// Generate random numbers
vector<int> createRandomList(int length) {
    vector<int> data;
    for (int i = 0; i < length; i++) {
        data.push_back((rand() % 100) + 1); // Numbers between 1 and 100
    }
    return data;
}

// Binary Search Algorithm
int searchBinary(const vector<int>& list, int value) {
    int low = 0, high = list.size() - 1;
    while (low <= high) {
        int middle = low + ((high - low) >> 1); 
        if (list[middle] == value) {
            return middle; // Return index if found
        } else if (list[middle] < value) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    return -1; // Return -1 if not found
}

// Measure execution time
double step() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}

int main() {
    srand(time(0));
    int length = 20; // Array size
    int valueToFind = (rand() % 100) + 1; // Random number to search

    double startTime = step();
    vector<int> sortedList = createRandomList(length);
    sort(sortedList.begin(), sortedList.end());
    
    cout << "Sorted List: ";
    for (int num : sortedList) cout << num << " ";
    cout << "\nSearching for " << valueToFind << " using Binary Search: ";
    
    int index = searchBinary(sortedList, valueToFind);
    if (index != -1) {
        cout << "Found at index " << index << "\n";
    } else {
        cout << "Not Found\n";
    }

    double endTime = step();
    printf("Execution Time: %f\n", endTime - startTime);

    return 0;
}

