#ifndef GNOM_H_INCLUDED
#define GNOM_H_INCLUDED

// Function declarations
void GnomeSort(int tab[], int n);
void AffichageGnome(int tab[], int n);
void choixmultipleGnome(int tab[], int n);
void ecrireDansCSVGnome(const char *nomFichier, const int tailles[], const double temps[], int nbTests);
int displayMenuGnomeSort();
void executeGnomeSort(int taille);
void testGnomeSortAndGenerateCSV();
void TriGnome();

#endif // GNOM_H_INCLUDED
