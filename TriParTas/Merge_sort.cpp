#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <chrono>
#include <windows.h>

using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void printArray(const vector<int>& arr) {
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

void writeCSV(const string& filename, const vector<int>& sizes, const vector<double>& times) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Unable to open file " << filename << endl;
        return;
    }

    file << "Size,Sort Time (s)\n";
    for (size_t i = 0; i < sizes.size(); i++) {
        file << sizes[i] << "," << times[i] << "\n";
    }

    file.close();
}

int displayMenu() {
    int choice;
    cout << "Menu:\n";
    cout << "1. Execute merge sort with a specified array size\n";
    cout << "2. Test merge sort with different array sizes and generate CSV file\n";
    cout << "Enter your choice: ";
    cin >> choice;
    return choice;
}

void executeMergeSort(int size) {
    vector<int> arr(size);

    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    cout << "Initial array: \n";
    printArray(arr);

    mergeSort(arr, 0, size - 1);

    cout << "Sorted array: \n";
    printArray(arr);
}

void testMergeSortAndGenerateCSV() {
    vector<int> sizes = {1000, 5000, 10000, 50000, 100000};
    vector<double> times(sizes.size());

    for (size_t i = 0; i < sizes.size(); i++) {
        int size = sizes[i];
        vector<int> arr(size);

        srand(time(0));
        for (int j = 0; j < size; j++) {
            arr[j] = rand() % 10000;
        }

        LARGE_INTEGER frequency, start, end;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

        mergeSort(arr, 0, size - 1);

        QueryPerformanceCounter(&end);
        times[i] = static_cast<double>(end.QuadPart - start.QuadPart) / frequency.QuadPart;
    }

    writeCSV("merge_sort_results2.csv", sizes, times);
}

int main() {
    int choice;
    while (true) {
        choice = displayMenu();
        switch (choice) {
            case 1: {
                int size;
                cout << "Enter the size of the array: ";
                cin >> size;
                executeMergeSort(size);
                break;
            }
            case 2:
                testMergeSortAndGenerateCSV();
                break;
            default:
                cout << "Invalid choice\n";
                break;
        }
    }
    return 0;
}