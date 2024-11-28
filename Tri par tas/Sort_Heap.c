#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonction pour échanger deux éléments
void echanger(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction pour entasser (heapify) un tableau
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

// Construction initiale du tas avec complexité O(n log n)
void construireTasNLogN(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j > 0) {
            int parent = (j - 1) / 2;
            if (arr[j] > arr[parent]) {
                echanger(&arr[j], &arr[parent]);
                j = parent;
            } else {
                break;
            }
        }
    }
}

// Construction initiale du tas optimisée avec complexité O(n)
void construireTasON(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        entasserMax(arr, n, i);
}

// Tri par tas (Heap Sort)
void triParTas(int arr[], int n, void (*constructionTas)(int[], int)) {
    constructionTas(arr, n);
    for (int i = n - 1; i > 0; i--) {
        echanger(&arr[0], &arr[i]);
        entasserMax(arr, i, 0);
    }
}

// Fonction pour générer un tableau aléatoire
void genererTableauAleatoire(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // Générer des nombres aléatoires entre 0 et 9999
    }
}

// Fonction pour écrire les résultats dans un fichier CSV
void ecrireDansCSV(const char* nomFichier, int tailles[], double temps[], int nbTests) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier %s\n", nomFichier);
        return;
    }

    fprintf(fichier, "Taille,Temps de Tri (s)\n");
    for (int i = 0; i < nbTests; i++) {
        fprintf(fichier, "%d,%.6f\n", tailles[i], temps[i]);
    }

    fclose(fichier);
}

int main() {
    srand(time(NULL)); // Initialiser la graine aléatoire

    const int taillesTests[] = {1000, 5000, 10000, 50000, 100000};
    const int nbTests = sizeof(taillesTests) / sizeof(taillesTests[0]);

    double tempsON[nbTests];
    double tempsONLogN[nbTests];

    for (int t = 0; t < nbTests; t++) {
        int n = taillesTests[t];
        int* tableau = (int*)malloc(n * sizeof(int));
        if (!tableau) {
            printf("Erreur : Mémoire insuffisante pour un tableau de taille %d\n", n);
            return 1;
        }

        // Générer un tableau aléatoire
        genererTableauAleatoire(tableau, n);

        // Mesurer le temps pour O(n)
        int* copieON = (int*)malloc(n * sizeof(int));
        memcpy(copieON, tableau, n * sizeof(int));
        clock_t debut = clock();
        triParTas(copieON, n, construireTasON);
        clock_t fin = clock();
        tempsON[t] = (double)(fin - debut) / CLOCKS_PER_SEC;
        free(copieON);

        // Mesurer le temps pour O(n log n)
        int* copieONLogN = (int*)malloc(n * sizeof(int));
        memcpy(copieONLogN, tableau, n * sizeof(int));
        debut = clock();
        triParTas(copieONLogN, n, construireTasNLogN);
        fin = clock();
        tempsONLogN[t] = (double)(fin - debut) / CLOCKS_PER_SEC;
        free(copieONLogN);

        free(tableau);
    }

    // Écrire les résultats dans des fichiers CSV
    ecrireDansCSV("resultats_Tri_ON.csv", taillesTests, tempsON, nbTests);
    ecrireDansCSV("resultats_Tri_ONLogN.csv", taillesTests, tempsONLogN, nbTests);

    printf("Les tests sont terminés. Les résultats sont enregistrés dans 'resultats_Tri_ON.csv' et 'resultats_Tri_ONLogN.csv'.\n");

    return 0;
}
