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
        data.push_back((rand() % 100) + 1); 
    }
    return data;
}

// Binary Search Algorithm
int searchBinary(const vector<int>& list, int value) {
    int low = 0, high = list.size() - 1, result = -1;
    while (low <= high) {
        int middle = low + ((high - low) >> 1); 
        if (list[middle] == value) {
            result = middle;
            break;
        } else if (list[middle] < value) {
            low = middle + 1;
        } else {
            high = middle - 1;
        }
    }
    return result;
}

// Measure execution time
double step() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}

int main() {
    srand(time(0));
    int length = 20; 
    //int valueToFind = (rand() % 100) + 1;

    double startTime = step();
    vector<int> sortedList = createRandomList(length);
    sort(sortedList.begin(), sortedList.end());
    
    // Choose a random value from the sorted list to search
    int valueToFind = sortedList[rand() % length];
    
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

