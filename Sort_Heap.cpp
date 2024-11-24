#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>

using namespace std;

// Fonction pour échanger deux éléments
void echanger(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Fonction pour entasser (heapify) un tableau
void entasserMax(vector<int>& arr, int n, int i) {
    int plusGrand = i;
    int gauche = 2 * i + 1;
    int droite = 2 * i + 2;

    if (gauche < n && arr[gauche] > arr[plusGrand])
        plusGrand = gauche;

    if (droite < n && arr[droite] > arr[plusGrand])
        plusGrand = droite;

    if (plusGrand != i) {
        echanger(arr[i], arr[plusGrand]);
        entasserMax(arr, n, plusGrand);
    }
}

// Construction initiale du tas avec complexité O(n log n)
void construireTasNLogN(vector<int>& arr, int n) {
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j > 0) {
            int parent = (j - 1) / 2;
            if (arr[j] > arr[parent]) {
                echanger(arr[j], arr[parent]);
                j = parent;
            } else {
                break;
            }
        }
    }
}

// Construction initiale du tas optimisée avec complexité O(n)
void construireTasON(vector<int>& arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        entasserMax(arr, n, i);
}

// Tri par tas (Heap Sort)
void triParTas(vector<int>& arr, int n, void (*constructionTas)(vector<int>&, int)) {
    constructionTas(arr, n);
    for (int i = n - 1; i > 0; i--) {
        echanger(arr[0], arr[i]);
        entasserMax(arr, i, 0);
    }
}

// Fonction pour générer un tableau aléatoire
void genererTableauAleatoire(vector<int>& arr, int n) {
    for (int i = 0; i < n; i++) {
        arr.push_back(rand() % 10000); // Générer des nombres aléatoires entre 0 et 9999
    }
}

// Fonction pour écrire les résultats dans un fichier CSV
void ecrireDansCSV(const string& nomFichier, const vector<int>& tailles, const vector<double>& temps) {
    ofstream fichier(nomFichier);
    if (!fichier) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << endl;
        return;
    }

    fichier << "Taille,Temps de Tri (s)" << endl;
    for (size_t i = 0; i < tailles.size(); i++) {
        fichier << tailles[i] << "," << temps[i] << endl;
    }
    fichier.close();
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Initialiser la graine aléatoire

    const vector<int> taillesTests = {1000, 5000, 10000, 50000, 100000};
    const int nbTests = taillesTests.size();

    vector<double> tempsON(nbTests);
    vector<double> tempsONLogN(nbTests);

    for (size_t t = 0; t < nbTests; t++) {
        int n = taillesTests[t];
        vector<int> tableau;

        // Générer un tableau aléatoire
        genererTableauAleatoire(tableau, n);

        // Mesurer le temps pour O(n)
        vector<int> copieON = tableau;
        clock_t debut = clock();
        triParTas(copieON, n, construireTasON);
        clock_t fin = clock();
        tempsON[t] = static_cast<double>(fin - debut) / CLOCKS_PER_SEC;

        // Mesurer le temps pour O(n log n)
        vector<int> copieONLogN = tableau;
        debut = clock();
        triParTas(copieONLogN, n, construireTasNLogN);
        fin = clock();
        tempsONLogN[t] = static_cast<double>(fin - debut) / CLOCKS_PER_SEC;
    }

    // Écrire les résultats dans des fichiers CSV
    ecrireDansCSV("resultats_ON_C++.csv", taillesTests, tempsON);
    ecrireDansCSV("resultats_ONLogN_C++.csv", taillesTests, tempsONLogN);

    cout << "Les tests sont terminés. Les résultats sont enregistrés dans 'resultats_ON_C++.csv' et 'resultats_ONLogN_C++.csv'." << endl;

    return 0;
}
