#ifndef TRIRAPIDE_H
#define TRIRAPIDE_H

void swap(int *a, int *b);
int partition(int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void printArrayTriRapide(int arr[], int size);
void writeCSV(const char *filename, const int sizes[], const double times[], int numTests);
void executeQuickSort(int size);
void testQuickSortAndGenerateCSV();
int displayMenuTriRapide();
void TriRapide();

#endif // TRIRAPIDE_H