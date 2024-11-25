#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>

using namespace std;

// Échanger deux éléments
void echanger(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Fonction pour entasser en Min-Heap
void entasserMin(vector<int> &arr, int n, int i) {
    int plusPetit = i;
    int gauche = 2 * i + 1;
    int droite = 2 * i + 2;

    if (gauche < n && arr[gauche] < arr[plusPetit])
        plusPetit = gauche;

    if (droite < n && arr[droite] < arr[plusPetit])
        plusPetit = droite;

    if (plusPetit != i) {
        echanger(arr[i], arr[plusPetit]);
        entasserMin(arr, n, plusPetit);
    }
}

// Construire un Min-Heap
void construireTasMin(vector<int> &arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        entasserMin(arr, n, i);
}

// Afficher le tableau
void afficherTableau(const vector<int> &arr) {
    for (int val : arr)
        cout << val << " ";
    cout << endl;
}

// Rechercher un élément dans le tas
int rechercherElement(const vector<int> &arr, int element) {
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == element)
            return i;
    }
    return -1; // Élément non trouvé
}

void insererElement(vector<int> &arr, int element) {
    arr.push_back(element); 
    int i = arr.size() - 1; 

    while (i > 0 && arr[(i - 1) / 2] < arr[i]) {
        echanger(arr[i], arr[(i - 1) / 2]);  
        i = (i - 1) / 2; 
    }
}

// Supprimer la racine (le plus petit élément) du Min-Heap
void supprimerMin(vector<int> &arr) {
    if (arr.empty())
        return;
    arr[0] = arr.back();
    arr.pop_back();
    entasserMin(arr, arr.size(), 0);
}

// Mesurer la complexité des opérations
void mesurerComplexite() {
    vector<int> tailles = {100, 500, 1000, 5000, 10000, 20000, 50000, 100000, 200000, 500000};

    ofstream fichier("complexite_temps_Min_Heap_C++.csv");
    if (!fichier.is_open()) {
        cout << "Erreur lors de la creation du fichier.\n";
        return;
    }

    fichier << "Taille,Temps Insertion,Temps Recherche,Temps Suppression\n";

    cout << "Mesure de la complexite (resultats enregistres dans 'complexite_temps_Min_Heap_C++.csv'):\n";

    for (int taille : tailles) {
        vector<int> arr;
        arr.reserve(taille);

        cout << "\nTaille: " << taille << endl;

        // Mesurer le temps d'insertion
        clock_t debut = clock();
        for (int i = 0; i < taille; i++) {
            insererElement(arr, rand() % 1000);
        }
        clock_t fin = clock();
        double tempsInsertion = static_cast<double>(fin - debut) / CLOCKS_PER_SEC;
        cout << "Temps d'insertion pour taille " << taille << ": " << tempsInsertion << " secondes\n";

        // Mesurer le temps de recherche
        debut = clock();
        for (int i = 0; i < taille; i++) {
            rechercherElement(arr, rand() % 1000);
        }
        fin = clock();
        double tempsRecherche = static_cast<double>(fin - debut) / CLOCKS_PER_SEC;
        cout << "Temps de recherche pour taille " << taille << ": " << tempsRecherche << " secondes\n";

        // Mesurer le temps de suppression
        debut = clock();
        while (!arr.empty()) {
            supprimerMin(arr);
        }
        fin = clock();
        double tempsSuppression = static_cast<double>(fin - debut) / CLOCKS_PER_SEC;
        cout << "Temps de suppression pour taille " << taille << ": " << tempsSuppression << " secondes\n";

        fichier << taille << "," << tempsInsertion << "," << tempsRecherche << "," << tempsSuppression << "\n";
    }

    fichier.close();
    cout << "\nLes donnees de complexite temporelle ont ete enregistrees dans 'complexite_temps_Min_Heap_C++.csv'.\n";
}

// Opérations sur le Min-Heap
void operationsTAS() {
    int choix, cle;
    vector<int> arr = {36, 31, 22, 18, 17, 16, 8, 7, 5, 2};
    construireTasMin(arr, arr.size());

    while (true) {
        cout << "\nOperations sur le TAS (Min-Heap):\n";
        cout << "1. Inserer\n";
        cout << "2. Supprimer\n";
        cout << "3. Rechercher\n";
        cout << "4. Afficher le TAS en tant que vecteur\n";
        cout << "5. Mesurer le temps\n";
        cout << "6. Quitter\n";
        cout << "Entrez votre choix: ";
        cin >> choix;

        switch (choix) {
        case 1:
            cout << "Entrez la cle a inserer: ";
            cin >> cle;
            insererElement(arr, cle);
            break;
        case 2:
            supprimerMin(arr);
            cout << "Racine supprimee.\n";
            break;
        case 3:
            cout << "Entrez la cle a rechercher: ";
            cin >> cle;
            int index;
            index = rechercherElement(arr, cle);
            if (index != -1)
                cout << "Element trouve a l'index " << index << "\n";
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
            return; // quitter
        default:
            cout << "Choix invalide. Reessayez.\n";
        }
    }
}

int main() {
    operationsTAS();
}
