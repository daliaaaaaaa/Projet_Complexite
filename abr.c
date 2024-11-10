#include <stdio.h>
#include <stdlib.h>
#include "abr.h"
typedef struct Noeud {
    int cle;
    struct Noeud* fg;  // fils gauche
    struct Noeud* fd;  // fils droit
} Noeud;

Noeud* minimum(Noeud* noeud) {
    while (noeud && noeud->fg != NULL) {
        noeud = noeud->fg;
    }
    return noeud;
}


void Suppression(int x, Noeud** racine) {
    Noeud* noeud = *racine;
    Noeud* parent = NULL;
    Noeud* enfant = NULL;
    Noeud* successeur = NULL;

    // 1. Recherche du nœud contenant la clé x à supprimer
    while (noeud != NULL && noeud->cle != x) {
        parent = noeud;
        if (x < noeud->cle) {
            noeud = noeud->fg;
        } else {
            noeud = noeud->fd;
        }
    }

    // Si le nœud n'est pas trouvé, on sort
    if (noeud == NULL) {
        printf("L'élément %d n'existe pas dans l'arbre.\n", x);
        return;
    }

    // 2. Cas où le nœud est une feuille (sans enfants)
    if (noeud->fg == NULL && noeud->fd == NULL) {
        if (parent == NULL) {
            *racine = NULL; // Si c'est la racine, l'arbre devient vide
        } else {
            if (parent->fg == noeud) {
                parent->fg = NULL; // Si le nœud est à gauche du parent
            } else {
                parent->fd = NULL; // Si le nœud est à droite du parent
            }
        }
        free(noeud);
        return;
    }

    // 3. Cas où le nœud a un seul enfant
    if (noeud->fg == NULL || noeud->fd == NULL) {
        if (noeud->fg != NULL) {
            enfant = noeud->fg;
        } else {
            enfant = noeud->fd;
        }
        
        if (parent == NULL) {
            *racine = enfant; // Si c'est la racine, on la remplace
        } else {
            if (parent->fg == noeud) {
                parent->fg = enfant;
            } else {
                parent->fd = enfant;
            }
        }
        free(noeud);
        return;
    }

    // 4. Cas où le nœud a deux enfants
    // On cherche le successeur en ordre (le plus petit dans le sous-arbre droit)
    successeur = minimum(noeud->fd);

    // Remplacer la valeur du nœud à supprimer par celle du successeur
    noeud->cle = successeur->cle;

    // Supprimer le successeur dans le sous-arbre droit
    parent = noeud;
    noeud = noeud->fd;
    
    // Recherche du successeur
    while (noeud != successeur) {
        parent = noeud;
        noeud = noeud->fg;
    }

    // 5. Suppression du successeur
    if (noeud->fg == NULL && noeud->fd == NULL) {
        if (parent->fg == noeud) {
            parent->fg = NULL; // Le successeur est une feuille
        } else {
            parent->fd = NULL;
        }
    } else {
        enfant = (noeud->fg != NULL) ? noeud->fg : noeud->fd;
        if (parent->fg == noeud) {
            parent->fg = enfant;
        } else {
            parent->fd = enfant;
        }
    }

    free(noeud);
}

// Fonction d'insertion d'un élément dans l'arbre
void insertion(Noeud** racine, int x) {
    // Création du nouveau noeud
    Noeud* p = malloc(sizeof(Noeud));
    if (p == NULL) {
        printf("Erreur d'allocation mémoire.\n");
        return;  // Si l'allocation échoue, on quitte la fonction
    }

    p->cle = x;
    p->fg = NULL;
    p->fd = NULL;

    // Si l'arbre est vide, on place directement le noeud comme racine
    if (*racine == NULL) {
        *racine = p;
        return;
    }

    Noeud* noeud = *racine;
    Noeud* parent = NULL;
    int existe = 0;

    // Recherche de l'emplacement où insérer le nouveau noeud
    while (noeud != NULL && !existe) {
        parent = noeud;
        if (x == noeud->cle) {
            existe = 1;  // L'élément existe déjà, on ne l'insère pas
        } else if (x < noeud->cle) {
            noeud = noeud->fg;  // On continue la recherche à gauche
        } else {
            noeud = noeud->fd;  // On continue la recherche à droite
        }
    }

    // Si l'élément n'existe pas, on insère le nouveau noeud
    if (!existe) {
        if (x < parent->cle) {
            parent->fg = p;  // Insertion à gauche
        } else {
            parent->fd = p;  // Insertion à droite
        }
    }
}

Noeud* recherche(Noeud* racine, int x) {
    Noeud* noeud = racine;

    if (racine != NULL) {
        if (x == noeud->cle) {
            return noeud;  // L'élément a été trouvé
        } else if (x < noeud->cle) {
            return recherche(noeud->fg, x);  // Recherche à gauche
        } else {
            return recherche(noeud->fd, x);  // Recherche à droite
        }
    }
    return NULL;  // Si l'élément n'est pas trouvé, retourner NULL
}
void menu(Noeud** racine) {
    int choix, valeur;
    Noeud* resultat;

    do {
        printf("\n--- Menu de traitement de l'arbre binaire de recherche ---\n");
        printf("1. Insertion\n");
        printf("2. Suppression\n");
        printf("3. Recherche\n");
        printf("4. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("Entrez la valeur à insérer : ");
                scanf("%d", &valeur);
                insertion(racine, valeur);
                printf("Valeur %d insérée dans l'arbre.\n", valeur);
                break;

            case 2:
                printf("Entrez la valeur à supprimer : ");
                scanf("%d", &valeur);
                Suppression(valeur, racine);
                printf("Valeur %d supprimée de l'arbre (si elle était présente).\n", valeur);
                break;

            case 3:
                printf("Entrez la valeur à rechercher : ");
                scanf("%d", &valeur);
                resultat = recherche(*racine, valeur);
                if (resultat != NULL) {
                    printf("Valeur %d trouvée dans l'arbre.\n", valeur);
                } else {
                    printf("Valeur %d non trouvée dans l'arbre.\n", valeur);
                }
                break;

            case 4:
                printf("Quitter le programme.\n");
                break;

            default:
                printf("Option invalide, veuillez réessayer.\n");
        }
    } while (choix != 4);
}




