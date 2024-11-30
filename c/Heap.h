// Heap.h
#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Fonctions communes
void echangerMax(int *a, int *b);
void echangerMin(int *a, int *b);

// Max-Heap
void entasserMax(int arr[], int n, int i);
void construireTasMax(int arr[], int n);
void insererElementMax(int arr[], int *n, int element);
void supprimerMax(int arr[], int *n);
int rechercherElementMax(int arr[], int n, int element);
void afficherTableauMax(int arr[], int n);

// Min-Heap
void entasserMin(int arr[], int n, int i);
void construireTasMin(int arr[], int n);
void insererElementMin(int arr[], int *n, int element);
void supprimerMin(int arr[], int *n);
int rechercherElementMin(int arr[], int n, int element);
void afficherTableauMin(int arr[], int n);

// Mesure de la complexité
void mesurerComplexiteMAX();
void mesurerComplexiteMIN();

// Operations sur le Heap
void operationsTASmax();
void operationsTASmin();

void construireTasNLogN(int arr[], int n);
void construireTasON(int arr[], int n);
void triParTas(int arr[], int n, void (*constructionTas)(int[], int));
void genererTableauAleatoire(int arr[], int n);
void ecrireDansCSV(const char *nomFichier, const int tailles[], double temps[], int nbTests);

#endif // HEAP_H
