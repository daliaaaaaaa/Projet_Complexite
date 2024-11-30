#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Sort_Heap.h"

// Fonction pour échanger deux éléments
void echanger(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Fonction pour entasser (heapify) un tableau
void entasserMaxiumum(int arr[], int n, int i)
{
    int plusGrand = i;
    int gauche = 2 * i + 1;
    int droite = 2 * i + 2;

    if (gauche < n && arr[gauche] > arr[plusGrand])
        plusGrand = gauche;

    if (droite < n && arr[droite] > arr[plusGrand])
        plusGrand = droite;

    if (plusGrand != i)
    {
        echanger(&arr[i], &arr[plusGrand]);
        entasserMaxiumum(arr, n, plusGrand);
    }
}

// Construction initiale du tas avec complexité O(n log n)
void construireTasNLogN(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int j = i;
        while (j > 0)
        {
            int parent = (j - 1) / 2;
            if (arr[j] > arr[parent])
            {
                echanger(&arr[j], &arr[parent]);
                j = parent;
            }
            else
            {
                break;
            }
        }
    }
}

// Construction initiale du tas optimisée avec complexité O(n)
void construireTasON(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        entasserMaxiumum(arr, n, i);
}

// Tri par tas (Heap Sort)
void triParTas(int arr[], int n, void (*constructionTas)(int[], int))
{
    constructionTas(arr, n);
    for (int i = n - 1; i > 0; i--)
    {
        echanger(&arr[0], &arr[i]);
        entasserMaxiumum(arr, i, 0);
    }
}

// Fonction pour générer un tableau aléatoire
void genererTableauAleatoire(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 10000; // Générer des nombres aléatoires entre 0 et 9999
    }
}

// Fonction pour écrire les résultats dans un fichier CSV
void ecrireDansCSV(const char *nomFichier, const int tailles[], double temps[], int nbTests)
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
void TriParTas_operations()
{
    int choix;

    do
    {

        printf("1. Executer le tri en O(n)\n");
        printf("2. Executer le tri en O(n log n)\n");
        printf("3. Mesurer la complexite des deux algorithmes\n");
        printf("4. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
        {
            int taille;
            printf("Entrez la taille du tableau a trier : ");
            scanf("%d", &taille);

            int *tableau = (int *)malloc(taille * sizeof(int));
            if (!tableau)
            {
                printf("Erreur : Memoire insuffisante pour un tableau de taille %d\n", taille);
                break;
            }

            genererTableauAleatoire(tableau, taille);
            printf("Tableau intial : ");
            for (int i = 0; i < taille; i++)
            {
                printf("%d ", tableau[i]);
            }
            printf("\n");

            triParTas(tableau, taille, construireTasON);
            printf("Tri en O(n) effectue avec succes.\n");

            printf("Tableau Trie : ");
            for (int i = 0; i < taille; i++)
            {
                printf("%d ", tableau[i]);
            }
            printf("\n");
            free(tableau);
            break;
        }

        case 2:
        {
            int taille;
            printf("Entrez la taille du tableau a trier : ");
            scanf("%d", &taille);

            int *tableau = (int *)malloc(taille * sizeof(int));
            if (!tableau)
            {
                printf("Erreur : Memoire insuffisante pour un tableau de taille %d\n", taille);
                break;
            }

            genererTableauAleatoire(tableau, taille);
            printf("Tableau intial : ");
            for (int i = 0; i < taille; i++)
            {
                printf("%d ", tableau[i]);
            }
            printf("\n");

            triParTas(tableau, taille, construireTasNLogN);
            printf("Tri en O(n log n) effectué avec succes.\n");

            printf("Tableau intial : ");
            for (int i = 0; i < taille; i++)
            {
                printf("%d ", tableau[i]);
            }
            printf("\n");

            free(tableau);
            break;
        }

        case 3:
        {
            const int taillesTests[] = {1000, 5000, 10000, 50000, 100000};
            const int nbTests = sizeof(taillesTests) / sizeof(taillesTests[0]);

            double tempsON[nbTests];
            double tempsONLogN[nbTests];

            for (int t = 0; t < nbTests; t++)
            {
                int n = taillesTests[t];
                int *tableau = (int *)malloc(n * sizeof(int));
                if (!tableau)
                {
                    printf("Erreur : Memoire insuffisante pour un tableau de taille %d\n", n);
                    return;
                }

                genererTableauAleatoire(tableau, n);

                // Mesurer le temps pour O(n)
                int *copieON = (int *)malloc(n * sizeof(int));
                memcpy(copieON, tableau, n * sizeof(int));
                clock_t debut = clock();
                triParTas(copieON, n, construireTasON);
                clock_t fin = clock();
                tempsON[t] = (double)(fin - debut) / CLOCKS_PER_SEC;
                free(copieON);

                // Mesurer le temps pour O(n log n)
                int *copieONLogN = (int *)malloc(n * sizeof(int));
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

            printf("Les tests sont termines.\n");
            printf("Resultats enregistres dans 'resultats_Tri_ON.csv' et 'resultats_Tri_ONLogN.csv'.\n");
            break;
        }

        case 0:
            printf("Fin du programme.\n");
            break;

        default:
            printf("Choix invalide. Veuillez réessayer.\n");
            break;
        }
    } while (choix != 4);
}
