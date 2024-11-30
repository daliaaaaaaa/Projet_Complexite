#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Heap.h"

// Échanger deux éléments
void echangerMin(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction pour entasser en Min-Heap
void entasserMin(int arr[], int n, int i)
{
    int plusPetit = i;
    int gauche = 2 * i + 1;
    int droite = 2 * i + 2;

    if (gauche < n && arr[gauche] < arr[plusPetit])
        plusPetit = gauche;

    if (droite < n && arr[droite] < arr[plusPetit])
        plusPetit = droite;

    if (plusPetit != i)
    {
        echangerMin(&arr[i], &arr[plusPetit]);
        entasserMin(arr, n, plusPetit);
    }
}

// Construire un Min-Heap
void construireTasMin(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        entasserMin(arr, n, i);
}

// Afficher le tableau
void afficherTableauMin(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

// Rechercher un élément dans le tas
int rechercherElementMin(int arr[], int n, int element)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == element)
            return i;
    }
    return -1; // Élément non trouvé
}

void insererElementMIN(int arr[], int *n, int element)
{
    arr[*n] = element;
    (*n)++;
    int i = *n - 1;

    // Maintenir la propriété du tas
    while (i > 0 && arr[(i - 1) / 2] > arr[i])
    {
        echangerMin(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
// Supprimer la racine (le plus petit élément) du Min-Heap
void supprimerMin(int arr[], int *n)
{
    if (*n <= 0)
        return;
    if (*n == 1)
    {
        (*n)--;
        return;
    }
    arr[0] = arr[*n - 1];
    (*n)--;
    entasserMin(arr, *n, 0);
}

// Mesurer la complexité des opérations
void mesurerComplexiteMIN()
{
    int tailles[] = {100, 500, 1000, 5000, 10000, 20000, 50000, 100000, 200000, 500000};
    int nbTailles = sizeof(tailles) / sizeof(tailles[0]);

    FILE *fichier = fopen("../Experimentation/complexite_temps_Min_Heap.csv", "w");
    if (fichier == NULL)
    {
        printf("Erreur lors de la creation du fichier.\n");
        return;
    }

    // Écrire les en-têtes du fichier CSV
    fprintf(fichier, "Taille,Temps Insertion,Temps Recherche,Temps Suppression\n");

    printf("Mesure de la complexite (resultats enregistres dans 'complexite_temps_Min_Heap.csv'):\n");

    for (int t = 0; t < nbTailles; t++)
    {
        int taille = tailles[t];
        int *arr = (int *)malloc(taille * sizeof(int));
        int n = 0;

        printf("\nTaille: %d\n", taille);

        // Mesurer le temps d'insertion
        clock_t debut = clock();
        for (int i = 0; i < taille; i++)
        {
            insererElementMIN(arr, &n, rand() % 1000);
        }
        clock_t fin = clock();
        double tempsInsertion = ((double)(fin - debut)) / CLOCKS_PER_SEC;
        printf("Temps d'insertion pour taille %d: %f secondes\n", taille, tempsInsertion);

        // Mesurer le temps de recherche
        debut = clock();
        for (int i = 0; i < taille; i++)
        {
            rechercherElementMin(arr, n, rand() % 1000);
        }
        fin = clock();
        double tempsRecherche = ((double)(fin - debut)) / CLOCKS_PER_SEC;
        printf("Temps de recherche pour taille %d: %f secondes\n", taille, tempsRecherche);

        // Mesurer le temps de suppression
        debut = clock();
        for (int i = 0; i < taille; i++)
        {
            supprimerMin(arr, &n);
        }
        fin = clock();
        double tempsSuppression = ((double)(fin - debut)) / CLOCKS_PER_SEC;
        printf("Temps de suppression pour taille %d: %f secondes\n", taille, tempsSuppression);

        // Écrire les résultats dans le fichier CSV
        fprintf(fichier, "%d,%f,%f,%f\n", taille, tempsInsertion, tempsRecherche, tempsSuppression);

        free(arr);
    }

    fclose(fichier);
    printf("\nLes donnees de complexite temporelle ont ete enregistrees dans 'complexite_temps_Min_Heap.csv'.\n");
}

// Opérations sur le Min-Heap
void operationsTASmin()
{
    int choix, cle;
    int arr[100] = {36, 31, 22, 18, 17, 16, 8, 7, 5, 2};
    int n = 10;
    construireTasMin(arr, 10);

    while (1)
    {
        printf("\nOperations sur le TAS (Min-Heap):\n");
        printf("1. Insérer\n");
        printf("2. Supprimer\n");
        printf("3. Rechercher\n");
        printf("4. Afficher le TAS en tant que vecteur\n");
        printf("5. Mesurer le temps\n");
        printf("6. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            printf("Entrez la clé à insérer: ");
            scanf("%d", &cle);
            insererElementMIN(arr, &n, cle);
            break;
        case 2:
            supprimerMin(arr, &n);
            printf("Racine supprimée.\n");
            break;
        case 3:
            printf("Entrez la clé à rechercher: ");
            scanf("%d", &cle);
            int index = rechercherElementMin(arr, n, cle);
            if (index != -1)
                printf("Élément trouvé à l'index %d\n", index);
            else
                printf("Élément non trouvé.\n");
            break;
        case 4:
            afficherTableauMin(arr, n);
            break;
        case 5:
            mesurerComplexiteMIN();
            break;
        case 6:
            return; // quitter
        default:
            printf("Choix invalide. Réessayez.\n");
        }
    }
}
