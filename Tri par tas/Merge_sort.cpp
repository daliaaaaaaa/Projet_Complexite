#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;

// Merge two subarrays
void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> temp(right - left + 1);
    int i = left;
    int j = mid + 1;
    int k = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    
    for (i = 0; i < k; i++) {
        arr[left + i] = temp[i];
    }
}

// Merge sort implementation
void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Write results to CSV file
void writeToCSV(const string& filename, const vector<int>& sizes, const vector<double>& times) {
    ofstream file(filename);
    file << "Taille,Temps de Tri (s)\n";
    for (size_t i = 0; i < sizes.size(); i++) {
        file << sizes[i] << "," << times[i] << "\n";
    }
    file.close();
}

int main() {
    vector<int> testSizes = {1000, 5000, 10000, 50000, 100000};
    vector<double> sortTimes(testSizes.size());
    
    // Random number generation
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9999);
    
    for (size_t i = 0; i < testSizes.size(); i++) {
        vector<int> arr(testSizes[i]);
        
        // Generate random array
        for (int& num : arr) {
            num = dis(gen);
        }
        
        // Measure sorting time
        auto start = chrono::high_resolution_clock::now();
        mergeSort(arr, 0, arr.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        
        chrono::duration<double> duration = end - start;
        sortTimes[i] = duration.count();
        
        cout << "Test completed for size " << testSizes[i] << endl;
    }
    
    writeToCSV("resultats_merge_sort_C++.csv", testSizes, sortTimes);
    cout << "Results saved to resultats_merge_sort_C++" << endl;
    
    return 0;
}