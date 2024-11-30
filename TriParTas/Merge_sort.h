#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Function prototypes
void mergeS(int array[], int leftIndex, int middleIndex, int rightIndex);
void mergeSort(int array[], int leftIndex, int rightIndex);
void ecrireDansCSVMerge(const char *nomFichier, const int tailles[], const double temps[], int nbTests);
void printArray(int arr[], int size);
int displayMenu();
void executeMergeSort(int taille);
void testMergeSortAndGenerateCSV();
void TriParFusion();
#endif // MERGE_SORT_H