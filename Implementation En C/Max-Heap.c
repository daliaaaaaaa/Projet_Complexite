#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Heap.h"

void echanger(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void entasserMax(int arr[], int n, int i) {
    int plusGrand = i;
    int gauche = 2 * i + 1;
    int droite = 2 * i + 2;

    if (gauche < n && arr[gauche] > arr[plusGrand])
        plusGrand = gauche;

    if (droite < n && arr[droite] > arr[plusGrand])
        plusGrand = droite;

    if (plusGrand != i) {
        echanger(&arr[i], &arr[plusGrand]);
        entasserMax(arr, n, plusGrand);
    }
}

void construireTasMax(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        entasserMax(arr, n, i);
}

void afficherTableau(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int rechercherElement(int arr[], int n, int element) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == element)
            return i;
    }
    return -1; // Element non trouvé
}

void insererElementMax(int arr[], int *n, int element) {
    arr[*n] = element;
    (*n)++;
    int i = *n - 1;

    // Maintenir la propriété du tas
    while (i > 0 && arr[(i - 1) / 2] < arr[i]) {
        echanger(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void supprimerMax(int arr[], int *n) {
    if (*n <= 0)
        return;
    if (*n == 1) {
        (*n)--;
        return;
    }
    arr[0] = arr[*n - 1];
    (*n)--;
    entasserMax(arr, *n, 0);
}

void mesurerComplexiteMAX() {
    int tailles[] = {100, 500, 1000, 5000, 10000, 20000, 50000, 100000, 200000, 500000};
    int nbTailles = sizeof(tailles) / sizeof(tailles[0]);

    FILE *fichier = fopen("../Experimentation/complexite_temps_MAX_HEAP.csv", "w");
    if (fichier == NULL) {
        printf("Erreur lors de la création du fichier.\n");
        return;
    }

    // Écrire les en-têtes du fichier CSV
    fprintf(fichier, "Taille,Temps Insertion,Temps Recherche,Temps Suppression\n");

    printf("Mesure de la complexité (résultats enregistrés dans 'complexite_temps_MAX_HEAP.csv'):\n");

    for (int t = 0; t < nbTailles; t++) {
        int taille = tailles[t];
        int *arr = (int *)malloc(taille * sizeof(int));
        int n = 0;

        printf("\nTaille: %d\n", taille);

        // Mesurer le temps d'insertion
        clock_t debut = clock();
        for (int i = 0; i < taille; i++) {
            insererElementMax(arr, &n, rand() % 1000);
        }
        clock_t fin = clock();
        double tempsInsertion = ((double)(fin - debut)) / CLOCKS_PER_SEC;
        printf("Temps d'insertion pour taille %d: %f secondes\n", taille, tempsInsertion);

        // Mesurer le temps de recherche
        debut = clock();
        for (int i = 0; i < taille; i++) {
            rechercherElement(arr, n, rand() % 1000);
        }
        fin = clock();
        double tempsRecherche = ((double)(fin - debut)) / CLOCKS_PER_SEC;
        printf("Temps de recherche pour taille %d: %f secondes\n", taille, tempsRecherche);

        // Mesurer le temps de suppression
        debut = clock();
        for (int i = 0; i < taille; i++) {
            supprimerMax(arr, &n);
        }
        fin = clock();
        double tempsSuppression = ((double)(fin - debut)) / CLOCKS_PER_SEC;
        printf("Temps de suppression pour taille %d: %f secondes\n", taille, tempsSuppression);

        // Écrire les résultats dans le fichier CSV
        fprintf(fichier, "%d,%f,%f,%f\n", taille, tempsInsertion, tempsRecherche, tempsSuppression);

        free(arr);
    }

    fclose(fichier);
    printf("\nLes donnees de complexite temporelle ont ete enregistrees dans 'complexite_temps_MAX_HEAP.csv'.\n");
}


void operationsTASmax() {
    int choix, cle;
    int arr[100] = {8, 16, 5, 17, 2, 36, 18, 22, 7, 31};
    int n = 10;
    construireTasMax(arr, 10);
    
    int arr1[10] = {36, 31, 22, 18, 17, 16, 8, 7, 5, 2};
    int arr2[10] = {36, 22, 31, 17, 8, 16, 18, 5, 7, 2};

    while (1) {
        printf("\nOperations sur le TAS:\n");
        printf("1. Inserer\n");
        printf("2. Supprimer\n");
        printf("3. Rechercher\n");
        printf("4. Afficher le TAS en tant que vecteur\n");
        printf("5. Mesurer le temps\n");
        printf("6. Quitter\n");
        printf("Entrez votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
        case 1:
            printf("Entrez la cle a inserer: ");
            scanf("%d", &cle);

            clock_t debut1 = clock();
            insererElementMax(arr1, &n, cle);
            clock_t fin1 = clock();
            double tempsPasse1 = (double)(fin1 - debut1) / CLOCKS_PER_SEC;
            printf("Temps pour le pire cas: %f secondes\n", tempsPasse1);

            clock_t debut2 = clock();
            insererElementMax(arr2, &n, cle);
            clock_t fin2 = clock();
            double tempsPasse2 = (double)(fin2 - debut2) / CLOCKS_PER_SEC;
            printf("Temps pour le meilleur cas: %f secondes\n", tempsPasse2);

            break;
        case 2:
            printf("Suppression de la racine pour les pires et meilleurs cas:\n");

            clock_t debut3 = clock();
            supprimerMax(arr1, &n);
            clock_t fin3 = clock();
            double tempsPasse3 = (double)(fin3 - debut3) / CLOCKS_PER_SEC;
            printf("Temps pour le pire cas de suppression (racine): %f secondes\n", tempsPasse3);
            break;
        case 3:
            printf("Entrez la cle a rechercher: ");
            scanf("%d", &cle);
            clock_t debut5 = clock();
            rechercherElement(arr, n, cle);
            clock_t fin5 = clock();
            double tempsPasse5 = (double)(fin5 - debut5) / CLOCKS_PER_SEC;
            printf("Temps : %f secondes\n", tempsPasse5);

            clock_t debut6 = clock();
            rechercherElement(arr, n, cle);
            clock_t fin6 = clock();
            double tempsPasse6 = (double)(fin6 - debut6) / CLOCKS_PER_SEC;
            printf("Temps pour le pire cas: %f secondes\n", tempsPasse6);

            clock_t debut7 = clock();
            rechercherElement(arr, n, cle);
            clock_t fin7 = clock();
            double tempsPasse7 = (double)(fin7 - debut7) / CLOCKS_PER_SEC;
            printf("Temps pour le meilleur cas: %f secondes\n", tempsPasse7);

            break;
        case 4:
            afficherTableau(arr, n);
            break;
        case 5:
            mesurerComplexiteMAX();
            break;
        case 6:
            return; // quitter
        default:
            printf("Choix invalide. Reessayez.\n");
        }
    }
}

int main() {
    operationsTASmax();
}