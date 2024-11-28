#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int array[], int leftIndex, int middleIndex, int rightIndex)
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

    // Merge the temp arrays back into array[leftIndex..rightIndex]
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

        merge(array, leftIndex, middleIndex, rightIndex);
    }
}

// Fonction pour écrire les résultats dans un fichier CSV
void ecrireDansCSV(const char *nomFichier, const int tailles[], const double temps[], int nbTests)
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

int main()
{
    srand(time(NULL)); // Initialiser la graine aléatoire

    const int taillesTests[] = {1000, 5000, 10000, 50000, 100000};
    const int nbTests = sizeof(taillesTests) / sizeof(taillesTests[0]);
    double tempsTri[nbTests];

    // Perform sorting tests for each size
    for (int i = 0; i < nbTests; i++)
    {
        int taille = taillesTests[i];
        int *tableau = (int *)malloc(taille * sizeof(int));

        // Generate random array
        for (int j = 0; j < taille; j++)
        {
            tableau[j] = rand() % 10000;
        }

        // Measure sorting time
        clock_t debut = clock();
        mergeSort(tableau, 0, taille - 1); // or heapSort(tableau, taille)
        clock_t fin = clock();

        tempsTri[i] = (double)(fin - debut) / CLOCKS_PER_SEC;

        free(tableau);
        printf("Test terminé pour taille %d\n", taille);
    }

    // Write results to CSV
    ecrireDansCSV("resultats_merge_sort.csv", taillesTests, tempsTri, nbTests);
    printf("Résultats sauvegardés dans resultats_merge_sort.csv\n");

    return 0;
}