#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>
#include <cmath>
#include <omp.h>

using namespace std;

void mergeArrays(vector<int>& arr, int left, int mid, int right) {
    int len1 = mid - left + 1;
    int len2 = right - mid;
    vector<int> leftPart(len1), rightPart(len2);

    for (int i = 0; i < len1; i++) {
        leftPart[i] = arr[left + i];
    }
    for (int j = 0; j < len2; j++) {
        rightPart[j] = arr[mid + 1 + j];
    }

    int leftIndex = 0, rightIndex = 0, mergedIndex = left;
    while (leftIndex < len1 && rightIndex < len2) {
        if (leftPart[leftIndex] <= rightPart[rightIndex]) {
            arr[mergedIndex] = leftPart[leftIndex++];
        } else {
            arr[mergedIndex] = rightPart[rightIndex++];
        }
        mergedIndex++;
    }
    while (leftIndex < len1) {
        arr[mergedIndex++] = leftPart[leftIndex++];
    }
    while (rightIndex < len2) {
        arr[mergedIndex++] = rightPart[rightIndex++];
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + ((right - left) >> 1);
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        mergeArrays(arr, left, mid, right);
    }
}

void sortMatrixRow(vector<vector<int>>& matrix, int rowIndex, bool ascending) {
    int size = matrix.size();
    mergeSort(matrix[rowIndex], 0, size - 1);
    if (!ascending) {
        reverse(matrix[rowIndex].begin(), matrix[rowIndex].end());
    }
}

void alternative_shearsort(int n, vector<vector<int>>& M) {
    int repeat = ceil(log2(n)) + 1;
    for (int r = 0; r < repeat; r++) {
        #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            sortMatrixRow(M, i, i % 2 == 0);
        }
        vector<vector<int>> transpose(n, vector<int>(n));
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                transpose[j][i] = M[i][j];
            }
        }
        #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            sortMatrixRow(transpose, i, true);
        }
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                M[i][j] = transpose[j][i];
            }
        }
    }
}

double step() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double)tp.tv_sec + (double)tp.tv_usec * 1e-6);
}

void displayMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << " \t";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    srand(time(0));
    int matrixSize;
    cout << "Enter the matrix size (n x n): ";
    cin >> matrixSize;
    vector<vector<int>> matrix(matrixSize, vector<int>(matrixSize));
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrix[i][j] = rand() % 100;
        }
    }
    cout << "\nOriginal matrix:\n";
    displayMatrix(matrix);
    double startTime = step();
    alternative_shearsort(matrixSize, matrix);
    double endTime = step();
    cout << "Sorted matrix with Alternative ShearSort:\n";
    displayMatrix(matrix);
    printf("Execution time: %f\n", endTime - startTime);
    return 0;
}

