#include <iostream>
#include <ctime>
#include <omp.h> // Include OpenMP header
using namespace std;

void insert(int*, int);
void fillRandom(int*, int);
void oddEvenSort(int*, int, int);

int main() {
    int* integerArray = nullptr;
    int arraySize, n = 1;

    cout << "Enter the size: ";
    cin >> arraySize;
    cout << "Enter num of process: ";
    cin >> n;

    integerArray = new int[arraySize];
    // insert(integerArray, arraySize);
    fillRandom(integerArray, arraySize);

    double startTime = omp_get_wtime(); // Start time measurement

    oddEvenSort(integerArray, arraySize, n);

    double endTime = omp_get_wtime(); // End time measurement
    double executionTime = endTime - startTime; // Calculate execution time

    cout << "Time taken: " << executionTime << " seconds" << endl;

    delete[] integerArray;

    return 0;
}

void insert(int* integerArray, int arraySize) {
    cout << "Enter " << arraySize << " numbers." << endl;
    for (int i = 0; i < arraySize; i++)
        cin >> integerArray[i];
    cout << "Array filled successfully." << endl;
}

void fillRandom(int* integerArray, int arraySize) {
    for (int i = 0; i < arraySize; i++)
        integerArray[i] = rand() % arraySize;
}

void oddEvenSort(int* integerArray, int arraySize, int n) {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
#pragma omp parallel num_threads(n)
        {
            // A kind of bubble sort for odd elements
#pragma omp for
            for (int i = 1; i < arraySize - 1; i = i + 2) {
                if (integerArray[i] > integerArray[i + 1]) {
                    swap(integerArray[i], integerArray[i + 1]);
                    sorted = false;
                }
            }
            // A kind of bubble sort for even elements
#pragma omp for
            for (int i = 0; i < arraySize - 1; i = i + 2) {
                if (integerArray[i] > integerArray[i + 1]) {
                    swap(integerArray[i], integerArray[i + 1]);
                    sorted = false;
                }
            }
        }
    }
}
