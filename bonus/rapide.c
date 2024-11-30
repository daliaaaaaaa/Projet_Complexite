#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "fonction.h"
// premiere position du pivot
int partitionner(int tab[], int first, int last, int n)
{

    int pivot = first;
    int i = first;
    int j = last;

    while (i < j)
    {
        while (tab[i] <= tab[pivot] && i < last)
            i++;
        while (tab[j] > tab[pivot] && j > first)
            j--;
        if (i < j)
        {
            permuter(&tab[i], &tab[j]);
            i++;
            j--;
        }
    }

    if (j != first)
        permuter(&tab[pivot], &tab[j]);
    return j;
}

// premiere position du pivot
void triRapide(int tab[], int first, int last, int n)
{
    int i, j;
    if (first < last)
    {
        j = partitionner(tab, first, last, n);
        triRapide(tab, first, j - 1, n);
        printf("La recursivite dans la partie droite du tableau : \n");
        for (i = 1; i <= n; i++)
        {
            printf(" %d | ", tab[i]);
        }
        printf("\n");
        triRapide(tab, j + 1, last, n);
        printf("La recursivite dans la partie gauche du tableau : \n");
        for (i = 1; i <= n; i++)
        {
            printf(" %d | ", tab[i]);
        }
        printf("\n");
    }
}
///////////////////////////////////////////////
// derniere position du pivot
int partitionnerlast(int tab[], int first, int last, int n)
{

    int pivot = last;
    int i = first;
    int j = last;

    while (i < j)
    {
        while (tab[i] <= tab[pivot] && i < last)
            i++;
        while (tab[j] > tab[pivot] && j > first)
            j--;
        if (i < j)
        {
            permuter(&tab[i], &tab[j]);
        }
    }
    if (j != last)
        permuter(&tab[pivot], &tab[j]);
    return j;
}

// derniere position du pivot
void triRapidelast(int tab[], int first, int last, int n)
{
    int i, j;
    if (first < last)
    {
        j = partitionnerlast(tab, first, last, n);
        triRapidelast(tab, first, j - 1, n);
        printf("La recursivite dans la partie droite du tableau : \n");
        for (i = 1; i <= n; i++)
        {
            printf(" %d | ", tab[i]);
        }
        printf("\n");
        triRapidelast(tab, j + 1, last, n);
        printf("La recursivite dans la partie gauche du tableau : \n");
        for (i = 1; i <= n; i++)
        {
            printf(" %d | ", tab[i]);
        }
        printf("\n");
    }
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////
// position aleatoire du pivot
/*int partitionnerrand(int tab[], int first, int last, int n)
{

int pivot = rand()%n;
int i = first;
int j = last;
printf("Le pivot = %d : \n",pivot);
while (i < j)
{
    while(tab[i] <= tab[pivot] && i < last)
    i++;
    while(tab[j] > tab[pivot] && j> first)
    j--;
    if(i < j)
    {
        permuter(&tab[i], &tab[j]);
        i++;
        j--;
    }
}
if (j != pivot)
permuter(&tab[pivot], &tab[j]);

return j;

}*/
////////////////////////////////////////////////////

int partitionn(int tab[], int first, int last)
{
    int pivot = tab[first];
    int i = first - 1, j = last + 1;
    while (1)
    {
        do
        {
            i++;
        } while (tab[i] < pivot);
        do
        {
            j--;
        } while (tab[j] > pivot);
        if (i >= j)
            return j;

        int temp = tab[i];
        tab[i] = tab[j];
        tab[j] = temp;
    }
}

int partitionner_r(int tab[], int first, int last, int n)
{
    srand(time(0));
    int random = first + rand() % (last - first);
    int temp = tab[random];
    tab[random] = tab[first];
    tab[first] = temp;
    return partitionn(tab, first, last);
}

// position aleatoire du pivot
void triRapiderand(int tab[], int first, int last, int n)
{
    int i, j;
    if (first < last)
    {
        j = partitionner_r(tab, first, last, n);
        triRapiderand(tab, first, j - 1, n);
        triRapiderand(tab, j + 1, last, n);
        printf("\n");
    }
}
///////////////////////////////////////////////////////////
int displayMenuTriRapide()
{
    int choice;
    printf("Menu:\n");
    printf("1. Execute tri rapide with a specified array size\n");
    printf("2. Test tri rapide with different array sizes and generate CSV file\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}
void executeTriRapide(int taille)
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
    printArrayR(arr, taille);
    triRapidelast(arr, 0, taille - 1, taille);
    printf("Tableau trié: \n");
    printArrayR(arr, taille);
    free(arr);
}
void testTriRapideAndGenerateCSV()
{
    int tailles[] = {1000, 5000, 10000, 50000, 100000};
    int nbTests = sizeof(tailles) / sizeof(tailles[0]);
    double temps[nbTests];

    for (int i = 0; i < nbTests; i++)
    {
        int taille = tailles[i];
        int *arr = (int *)malloc(taille * sizeof(int));
        if (arr == NULL)
        {
            printf("Erreur d'allocation mémoire\n");
            return;
        }
        srand(time(0));
        for (int j = 0; j < taille; j++)
        {
            arr[j] = rand() % 10000;
        }
        clock_t start = clock();
        triRapidelast(arr, 0, taille - 1, taille);
        clock_t end = clock();
        temps[i] = ((double)(end - start)) / CLOCKS_PER_SEC;
        free(arr);
    }
    ecrireDansCSVR("tri_rapide_results.csv", tailles, temps, nbTests);
}
void ecrireDansCSVR(const char *nomFichier, const int tailles[], const double temps[], int nbTests)
{
    FILE *file = fopen(nomFichier, "w");
    if (file == NULL)
    {
        printf("Erreur d'ouverture du fichier %s\n", nomFichier);
        return;
    }
    fprintf(file, "Taille,Temps de tri (s)\n");
    for (int i = 0; i < nbTests; i++)
    {
        fprintf(file, "%d,%.6f\n", tailles[i], temps[i]);
    }
    fclose(file);
}

void printArrayR(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int main()
{
    int choice;
    while (1)
    {
        choice = displayMenuTriRapide();
        switch (choice)
        {
        case 1:
        {
            int taille;
            printf("Enter the size of the array: ");
            scanf("%d", &taille);
            executeTriRapide(taille);
            break;
        }
        case 2:
            testTriRapideAndGenerateCSV();
            break;
        case 3:
            printf("Exiting...\n");
            return 0;
        default:
            printf("Invalid choice\n");
            break;
        }
    }
    return 0;
}
