#ifndef SORT_HEAP_H
#define SORT_HEAP_H

// Function prototypes
void echanger(int *a, int *b);
void entasserMaxiumum(int arr[], int n, int i);
void construireTasNLogN(int arr[], int n);
void construireTasON(int arr[], int n);
void triParTas(int arr[], int n, void (*constructionTas)(int[], int));
void genererTableauAleatoire(int arr[], int n);
void ecrireDansCSV(const char *nomFichier, const int tailles[], double temps[], int nbTests);
void TriParTas_operations();
void testHeapSortAndGenerateCSV();

#endif // SORT_HEAP_H