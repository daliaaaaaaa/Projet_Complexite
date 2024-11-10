#ifndef TAS_H
#define TAS_H

#include <stdio.h>
#include <stdlib.h>

// Function prototypes
void entasser(int *arr, int i, int n);
void construireTas(int *arr, int n);
void insererTAS(int *arr, int *n, int x);
void rechercherTAS(int *arr, int n, int x);
void supprimerTAS(int *arr, int *n, int x);
void afficherTASvecteur(int *arr, int n);
void afficherTASarbre(int *arr, int n);
void afficherTAS(int *arr, int n);
void mesurerPerformance();
void TAS_operations();


#endif // TAS_H