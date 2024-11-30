#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

void mergeS(int array[], int leftIndex, int middleIndex, int rightIndex)
{
    int leftArraySize = middleIndex - leftIndex + 1;
    int rightArraySize = rightIndex - middleIndex;

    // Create temp arrays
    int leftArray[leftArraySize], rightArray[rightArraySize];

    // Copy data to temporary arrays
    for (int leftPos = 0; leftPos < leftArraySize; leftPos++)
        leftArray[leftPos] = array[leftIndex + leftPos];
    for (int rightPos = 0; rightPos < rightArraySize; rightPos++)
        rightArray[rightPos] = array[middleIndex + 1 + rightPos];

    // mergeS the temp arrays back into array[leftIndex..rightIndex]
    int leftPos = 0;
    int rightPos = 0;
    int mergePos = leftIndex;

    while (leftPos < leftArraySize && rightPos < rightArraySize)
    {
        if (leftArray[leftPos] <= rightArray[rightPos])
        {
            array[mergePos] = leftArray[leftPos];
            leftPos++;
        }
        else
        {
            array[mergePos] = rightArray[rightPos];
            rightPos++;
        }
        mergePos++;
    }

    // Copy remaining elements of leftArray[] if any
    while (leftPos < leftArraySize)
    {
        array[mergePos] = leftArray[leftPos];
        leftPos++;
        mergePos++;
    }

    // Copy remaining elements of rightArray[] if any
    while (rightPos < rightArraySize)
    {
        array[mergePos] = rightArray[rightPos];
        rightPos++;
        mergePos++;
    }
}

void mergeSort(int array[], int leftIndex, int rightIndex)
{
    if (leftIndex < rightIndex)
    {
        int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;

        mergeSort(array, leftIndex, middleIndex);
        mergeSort(array, middleIndex + 1, rightIndex);

        mergeS(array, leftIndex, middleIndex, rightIndex);
    }
}

// Fonction pour écrire les résultats dans un fichier CSV
void ecrireDansCSVMerge(const char *nomFichier, const int tailles[], const double temps[], int nbTests)
{
    FILE *fichier = fopen(nomFichier, "w");
    if (fichier == NULL)
    {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    fprintf(fichier, "Taille,Temps de Tri (s)\n");
    for (int i = 0; i < nbTests; i++)
    {
        fprintf(fichier, "%d,%.6f\n", tailles[i], temps[i]);
    }

    fclose(fichier);
}
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to display the menu and get the user's choice
int displayMenu()
{
    int choice;
    printf("Menu:\n");
    printf("1. Exécuter le tri par fusion avec une taille de tableau spécifiée\n");
    printf("2. Tester le tri par fusion avec différentes tailles de tableau et générer un fichier CSV\n");
    printf("3. Retour au menu\n");
    printf("Entrez votre choix: ");
    scanf("%d", &choice);
    return choice;
}

// Function to execute merge sort with a specified array size
void executeMergeSort(int taille)
{
    int *arr = (int *)malloc(taille * sizeof(int));
    if (arr == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        return;
    }

    srand(time(0));
    for (int i = 0; i < taille; i++)
    {
        arr[i] = rand() % 100;
    }

    printf("Tableau initial: \n");
    printArray(arr, taille);

    mergeSort(arr, 0, taille - 1);

    printf("Tableau trié: \n");
    printArray(arr, taille);

    free(arr);
}

// Function to test merge sort with different array sizes and generate CSV file
void testMergeSortAndGenerateCSV()
{
    const int taillesTests[] = {1000, 5000, 10000, 50000, 100000};
    const int nbTests = sizeof(taillesTests) / sizeof(taillesTests[0]);
    double tempsTri[nbTests];

    // Perform sorting tests for each size
    for (int i = 0; i < nbTests; i++)
    {
        int taille = taillesTests[i];
        int *tableau = (int *)malloc(taille * sizeof(int));
        if (tableau == NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }

        // Initialize the array with random values
        for (int j = 0; j < taille; j++)
        {
            tableau[j] = rand() % 10000;
        }

        // Perform merge sort
        LARGE_INTEGER frequency, start, end;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);

        mergeSort(tableau, 0, taille - 1);

        QueryPerformanceCounter(&end);
        tempsTri[i] = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart;
        free(tableau);
    }

    // Generate CSV file
    ecrireDansCSVMerge("merge_sort_results.csv", taillesTests, tempsTri, nbTests);
}

void TriParFusion()
{
    int choice;
    while (choice != 3)
    {
        choice = displayMenu();
        switch (choice)
        {
        case 1:
        {
            int taille;
            printf("Enter the size of the array: ");
            scanf("%d", &taille);
            executeMergeSort(taille);
            break;
        }
        case 2:
            testMergeSortAndGenerateCSV();
            break;
        case 3:
            printf("Retour au menu des tri ");

            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    }
}
