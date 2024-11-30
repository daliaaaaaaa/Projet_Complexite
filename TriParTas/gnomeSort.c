#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gnomeSort.h"

void GnomeSort(int tab[], int n)
{
    int index = 0;
    while (index < n)
    {
        if (index == 0)
            index++;
        if (tab[index] >= tab[index - 1])
            index++;
        else
        {
            int temp = tab[index];
            tab[index] = tab[index - 1];
            tab[index - 1] = temp;
            index--;
        }
    }
}

void AffichageGnome(int tab[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
}

void choixmultipleGnome(int tab[], int n)
{
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        tab[i] = rand() % 1000; // Random numbers between 0 and 999
    }
}

void ecrireDansCSVGnome(const char *nomFichier, const int tailles[], const double temps[], int nbTests)
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

void executeGnomeSort(int taille)
{
    int *tab = malloc(taille * sizeof(int));
    if (tab == NULL)
    {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    choixmultipleGnome(tab, taille);
    printf("Initial array:\n");
    AffichageGnome(tab, taille);
    printf("\n\n");
    clock_t t1 = clock();
    GnomeSort(tab, taille);
    clock_t t2 = clock();
    float delta = (float)(t2 - t1) / CLOCKS_PER_SEC;
    printf("Sorted array:\n");
    AffichageGnome(tab, taille);
    printf("Le temps d'execution = %f secondes pour n = %d\n", delta, taille);
    free(tab);
}

void testGnomeSortAndGenerateCSV()
{
    int tailles[] = {1000, 5000, 10000, 50000, 100000};
    int nbTests = sizeof(tailles) / sizeof(tailles[0]);
    double temps[nbTests];

    for (int i = 0; i < nbTests; i++)
    {
        int taille = tailles[i];
        int *tab = malloc(taille * sizeof(int));
        if (tab == NULL)
        {
            printf("Erreur d'allocation mémoire\n");
            return;
        }
        choixmultipleGnome(tab, taille);
        clock_t t1 = clock();
        GnomeSort(tab, taille);
        clock_t t2 = clock();
        temps[i] = (double)(t2 - t1) / CLOCKS_PER_SEC;
        free(tab);
    }
    ecrireDansCSVGnome("gnome_sort_results.csv", tailles, temps, nbTests);
}

int displayMenuGnomeSort()
{
    int choice;
    printf("Menu:\n");
    printf("1. executer genome avec une taille specifique n \n");
    printf("2. Test Gnome sort with different array sizes and generate CSV file\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

void TriGnome()
{
    int choice;
    while (choice != 3)
    {
        choice = displayMenuGnomeSort();
        switch (choice)
        {
        case 1:
        {
            int taille;
            printf("Enter the size of the array: ");
            scanf("%d", &taille);
            executeGnomeSort(taille);
            break;
        }
        case 2:
            testGnomeSortAndGenerateCSV();
            break;
        case 3:
            printf("Exiting...\n");
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}