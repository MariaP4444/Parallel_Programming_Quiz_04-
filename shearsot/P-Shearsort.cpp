#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <sys/time.h>
#include <cmath>
#include <omp.h>

using namespace std;

// Function to merge two halves of a sorted vector.
void mergeArrays(vector<int>& arr, int left, int mid, int right){
    int len1 = mid - left + 1;
    int len2 = right - mid;
    vector<int> leftPart(len1), rightPart(len2);

    for(int i = 0; i < len1; i++){
        leftPart[i] = arr[left + i];
    }

    for(int j = 0; j < len2; j++){
        rightPart[j] = arr[mid + 1 + j];
    }

    int leftIndex = 0, rightIndex = 0, mergedIndex = left;

    while(leftIndex < len1 && rightIndex < len2){
        if(leftPart[leftIndex] <= rightPart[rightIndex]){
            arr[mergedIndex] = leftPart[leftIndex];
            leftIndex++;
        } else{
            arr[mergedIndex] = rightPart[rightIndex];
            rightIndex++;
        }
        mergedIndex++;
    }

    while(leftIndex < len1){
        arr[mergedIndex] = leftPart[leftIndex];
        leftIndex++;
        mergedIndex++;
    }

    while(rightIndex < len2){
        arr[mergedIndex] = rightPart[rightIndex];
        rightIndex++;
        mergedIndex++;
    }
}

// MergeSort algorithm to sort a vector.
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + ((right - left) >> 1);
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        mergeArrays(arr, left, mid, right);
    }
}

// Sorts a row of the matrix in ascending or descending order.
void sortMatrixRow(vector<vector<int>>& matrix, int rowIndex, bool ascending){
    int size = matrix.size();
    mergeSort(matrix[rowIndex], 0, size - 1);
    if(!ascending){
        reverse(matrix[rowIndex].begin(), matrix[rowIndex].end());
    }
}

// Sorts a column of the matrix in ascending order.
void sortMatrixColumn(vector<vector<int>>& matrix, int colIndex){
    int size = matrix.size();
    vector<int> tempColumn(size);
    for (int i = 0; i < size; i++) {
        tempColumn[i] = matrix[i][colIndex];
    }

    mergeSort(tempColumn, 0, size - 1);
    for (int i = 0; i < size; i++) {
        matrix[i][colIndex] = tempColumn[i];
    }
}

// Parallelized ShearSort algorithm.
void shearSortParallel(vector<vector<int>>& matrix){
    int size = matrix.size();
    int step = log2(size) + 1;
    for (int i = 0; i < step; i++) {
        #pragma omp parallel for
        for(int row = 0; row < size; row++){
            sortMatrixRow(matrix, row, row % 2 == 0);
        }

        #pragma omp parallel for
        for(int col = 0; col < size; col++){
            sortMatrixColumn(matrix, col);
        }
    }
}

// Prints the matrix to the console.
void displayMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int value : row) {
            cout << value << " \t";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to measure execution time.
double step(){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}

int main(){
    srand(time(0));
    int matrixSize;
    cout << "Enter the matrix size (n x n): ";
    cin >> matrixSize;

    vector<vector<int>> matrix(matrixSize, vector<int>(matrixSize));

    // Fill the matrix with random values.
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrix[i][j] = rand() % 100;
        }
    }

    cout << "\nOriginal matrix:\n";
    displayMatrix(matrix);
    
    double startTime = step();
    shearSortParallel(matrix);
    double endTime = step();
    
    cout << "Sorted matrix with ShearSort:\n";
    displayMatrix(matrix);
    printf("Execution time: %f\n", endTime - startTime);

    return 0;
}

