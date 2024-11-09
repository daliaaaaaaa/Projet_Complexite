#include <stdio.h>

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
            printf("Element trouvé à la position %d\n", i);
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


int main() {
    int arr[100] = {0, 28, 16, 5, 17, 2, 36, 18, 22, 7, 31};
    int n = 10;
    // creation du tas
    afficherTAS(arr,n);
    construireTas(arr, n);
    afficherTAS(arr,n);

    // insertion
    insererTAS(arr, &n, 50);
    afficherTAS(arr, n);

    // recherche
    printf("Recherche Pire cas (dernier element du tableau)\n");
    rechercherTAS(arr, n, 2);

    printf("Recherche Meilleur cas (premier element du tableau)\n");
    rechercherTAS(arr, n, 36);

    // suppression
    supprimerTAS(arr, &n, 50);


}