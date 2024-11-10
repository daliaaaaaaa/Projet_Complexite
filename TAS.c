#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tas.h"

void entasser(int *arr, int i, int n) {
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= n && arr[left] > arr[largest]) {
        largest = left;
    }

    if (right <= n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        entasser(arr, largest, n);
    }
}

void construireTas(int *arr, int n) {
    for (int i = n / 2; i > 0; i--) {
        entasser(arr, i, n);
    }
}

void insererTAS(int *arr, int *n, int x) {
    *n = *n + 1;
    arr[*n] = x;

    int i = *n;
    while (i > 1 && arr[i / 2] < arr[i]) {
        int temp = arr[i];
        arr[i] = arr[i / 2];
        arr[i / 2] = temp;
        i = i / 2;
    }
}

void rechercherTAS(int *arr, int n, int x) {
    for(int i = 1; i <= n; i++){
        if(arr[i] == x){
            printf("Element trouve à la position %d\n", i);
            return;
        }
    }
    printf("Element non trouvé\n");
}

void supprimerTAS(int *arr, int *n, int x) {
    int i;
    for(i = 1; i <= *n; i++){
        if(arr[i] == x){
            break;
        }
    }
    if(i == *n){
        *n = *n - 1;
        return;
    }
    arr[i] = arr[*n];
    *n = *n - 1;
    entasser(arr, i, *n);
}

void afficherTASvecteur(int *arr, int n) {
    for(int i = 1; i <= n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void afficherTASarbre(int *arr, int n) {
    for (int i = 1; i <= n; i++) {
        printf("Noeud %d : %d\n", i, arr[i]);
        int left = 2 * i;
        int right = 2 * i + 1;

        if (left <= n)
            printf("  Fils gauche de %d : %d\n", arr[i], arr[left]);
        if (right <= n)
            printf("  Fils droit de %d : %d\n", arr[i], arr[right]);
    }
}

void afficherTAS(int *arr, int n) {
    for(int i = 1; i <= n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void mesurerPerformance() {
    int n;
    clock_t start, end;
    double time_spent;

    for (int size = 1000; size <= 10000; size += 1000) {
        int arr[size];
        n = size;
        for (int j = 1; j <= n; j++) {
            arr[j] = rand() % 100;
        }
        construireTas(arr, n);

        // Measure insertion time
        start = clock();
        insererTAS(arr, &n, rand() % 100);
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Insertion time for %d elements: %f seconds\n", n, time_spent);

        // Measure search time
        start = clock();
        rechercherTAS(arr, n, arr[rand() % n + 1]);
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Search time for %d elements: %f seconds\n", n, time_spent);

        // Measure deletion time
        start = clock();
        for (int k = 0; k < 1000; k++) { // Répétez la suppression pour plus de précision
            supprimerTAS(arr, &n, arr[1]);
        }
        end = clock();
        time_spent = (double)(end - start) / CLOCKS_PER_SEC;
        printf("Temps pour 1000 suppressions avec %d éléments initiaux: %f secondes\n\n", size, time_spent);
    }
}

void TAS_operations() {
    int choice, key;
    int arr[100] = {8, 16, 5, 17, 2, 36, 18, 22, 7, 31};
    int n = 10;
    construireTas(arr, 10);
    
    int arr1[10] = {36, 31, 22, 18, 17, 16, 8, 7, 5, 2};
    int arr2[10] = {36, 22, 31, 17, 8, 16, 18, 5, 7, 2};

    while (1) {
        printf("\nTAS Operations:\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Print TAS as Vector\n");
        printf("5. Print TAS as Tree\n");
        printf("6. Essaie Time\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter key to insert: ");
            scanf("%d", &key);

            clock_t start1 = clock();
            insererTAS(arr1, &n, key);
            clock_t end1 = clock();
            double time_spent1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
            printf("Temps pour le pire cas: %f secondes\n", time_spent1);

            clock_t start2 = clock();
            insererTAS(arr2, &n, key);
            clock_t end2 = clock();
            double time_spent2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
            printf("Temps pour le meilleur cas: %f secondes\n", time_spent2);

            break;
        case 2:
            printf("Suppression de la racine pour les pires et meilleurs cas:\n");

            clock_t start3 = clock();
            supprimerTAS(arr1, &n, arr1[1]);
            clock_t end3 = clock();
            double time_spent3 = (double)(end3 - start3) / CLOCKS_PER_SEC;
            printf("Temps pour le pire cas de suppression (racine): %f secondes\n", time_spent3);

            int feuille = arr2[n];  
            clock_t start4 = clock();
            supprimerTAS(arr2, &n, feuille);
            clock_t end4 = clock();
            double time_spent4 = (double)(end4 - start4) / CLOCKS_PER_SEC;
            printf("Temps pour le meilleur cas de suppression (feuille): %f secondes\n", time_spent4);
            break;
        case 3:
            printf("Enter key to search: ");
            scanf("%d", &key);
            clock_t start5 = clock();
            rechercherTAS(arr, n, key);
            clock_t end5 = clock();
            double time_spent5 = (double)(end5 - start5) / CLOCKS_PER_SEC;
            printf("Temps : %f secondes\n", time_spent5);

            clock_t start6 = clock();
            rechercherTAS(arr, n, key);
            clock_t end6 = clock();
            double time_spent6 = (double)(end6 - start6) / CLOCKS_PER_SEC;
            printf("Temps pour le pire cas: %f secondes\n", time_spent6);

            clock_t start7 = clock();
            rechercherTAS(arr, n, key);
            clock_t end7 = clock();
            double time_spent7 = (double)(end7 - start7) / CLOCKS_PER_SEC;
            printf("Temps pour le meilleur cas: %f secondes\n", time_spent7);

            break;
        case 4:
            afficherTASvecteur(arr, n);
            break;
        case 5:
            afficherTASarbre(arr, n);
            break;
        case 6:
            srand(time(NULL));
            mesurerPerformance();
            break;
        case 7:
            return; //exit 
        default:
            printf("Choix invalide. reessayer encore.\n");
        }
    }
}


int main() {
 TAS_operations();
 }