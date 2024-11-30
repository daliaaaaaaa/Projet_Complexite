#ifndef RAPIDE_H_INCLUDED
#define RAPIDE_H_INCLUDED

int partitionner(int tab[], int first, int last, int n);
int partitionnerlast(int tab[], int first, int last, int n);
int partitionnerrand(int tab[], int first, int last, int n);
void triRapidelast(int tab[], int first, int last, int n);
int partitionn(int tab[], int first, int last);
int partitionner_r(int tab[], int first, int last, int n);
void triRapiderand(int tab[], int first, int last, int n);
void printArrayR(int arr[], int size);
void ecrireDansCSVR(const char *nomFichier, const int tailles[], const double temps[], int nbTests);
void testTriRapideAndGenerateCSV();
void executeTriRapide(int taille);
int displayMenuTriRapide();

#endif // RAPIDE_H_INCLUDED
