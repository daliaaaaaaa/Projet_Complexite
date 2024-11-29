#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>

using namespace std;

// Function to swap two elements
void echanger(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Heapify function for max-heap
void entasserMax(vector<int> &arr, int n, int i) {
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

// Function to build a max-heap
void construireTasMax(vector<int> &arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        entasserMax(arr, n, i);
}

// Display the heap as a vector
void afficherTableau(const vector<int> &arr) {
    for (int val : arr)
        cout << val << " ";
    cout << endl;
}

// Search for an element in the heap
int rechercherElement(const vector<int> &arr, int element) {
    auto it = find(arr.begin(), arr.end(), element);
    return (it != arr.end()) ? distance(arr.begin(), it) : -1;
}

void insererElement(vector<int> &arr, int element) {
    arr.push_back(element); 
    int i = arr.size() - 1; 

    while (i > 0 && arr[(i - 1) / 2] < arr[i]) {
        echanger(arr[i], arr[(i - 1) / 2]);  
        i = (i - 1) / 2; 
    }
}

// Remove the maximum element from the heap
void supprimerMax(vector<int> &arr) {
    if (arr.empty())
        return;
    arr[0] = arr.back();
    arr.pop_back();
    entasserMax(arr, arr.size(), 0);
}

// Measure performance complexity
void mesurerComplexite() {
    vector<int> tailles = {100, 500, 1000, 5000, 10000, 20000, 50000, 100000, 200000, 500000};
    ofstream fichier("../Experimentation/complexite_temps_MAX_HEAP_C++.csv");

    if (!fichier.is_open()) {
        cerr << "Erreur lors de la création du fichier.\n";
        return;
    }

    fichier << "Taille,Temps Insertion,Temps Recherche,Temps Suppression\n";

    cout << "Mesure de la complexité (résultats enregistrés dans 'complexite_temps_MAX_HEAP_C++.csv'):\n";

    for (int taille : tailles) {
        vector<int> arr;
        arr.reserve(taille);

        // Measure insertion time
        clock_t debut = clock();
        for (int i = 0; i < taille; i++) {
            insererElement(arr, rand() % 1000);
        }
        clock_t fin = clock();
        double tempsInsertion = static_cast<double>(fin - debut) / CLOCKS_PER_SEC;
        cout << "Temps d'insertion pour taille " << taille << ": " << tempsInsertion << " secondes\n";

        // Measure search time
        debut = clock();
        for (int i = 0; i < taille; i++) {
            rechercherElement(arr, rand() % 1000);
        }
        fin = clock();
        double tempsRecherche = static_cast<double>(fin - debut) / CLOCKS_PER_SEC;
        cout << "Temps de recherche pour taille " << taille << ": " << tempsRecherche << " secondes\n";

        // Measure deletion time
        debut = clock();
        while (!arr.empty()) {
            supprimerMax(arr);
        }
        fin = clock();
        double tempsSuppression = static_cast<double>(fin - debut) / CLOCKS_PER_SEC;
        cout << "Temps de suppression pour taille " << taille << ": " << tempsSuppression << " secondes\n";

        fichier << taille << "," << tempsInsertion << "," << tempsRecherche << "," << tempsSuppression << "\n";
    }

    fichier.close();
    cout << "\nLes donnees de complexite temporelle ont ete enregistrees dans 'complexite_temps_MAX_HEAP_C++.csv'.\n";
}

// Heap operations menu
void operationsTAS() {
    vector<int> arr = {8, 16, 5, 17, 2, 36, 18, 22, 7, 31};
    construireTasMax(arr);

    while (true) {
        cout << "\nOperations sur le TAS:\n";
        cout << "1. Inserer\n";
        cout << "2. Supprimer\n";
        cout << "3. Rechercher\n";
        cout << "4. Afficher le TAS en tant que vecteur\n";
        cout << "5. Mesurer le temps\n";
        cout << "6. Quitter\n";
        cout << "Entrez votre choix: ";
        int choix, cle;
        cin >> choix;

        switch (choix) {
            case 1:
                cout << "Entrez la cle a inserer: ";
                cin >> cle;
                insererElement(arr, cle);
                break;
            case 2:
                cout << "Suppression de la racine...\n";
                supprimerMax(arr);
                break;
            case 3:
                cout << "Entrez la cle a rechercher: ";
                cin >> cle;
                if (rechercherElement(arr, cle) != -1)
                    cout << "Element trouve.\n";
                else
                    cout << "Element non trouve.\n";
                break;
            case 4:
                afficherTableau(arr);
                break;
            case 5:
                srand(time(0));
                mesurerComplexite();
                break;
            case 6:
                return;
            default:
                cout << "Choix invalide. Reessayez.\n";
        }
    }
}

int main() {
    operationsTAS();
    return 0;
}
