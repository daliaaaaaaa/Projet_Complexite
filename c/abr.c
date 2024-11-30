#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "abr.h"

Noeud *minimum(Noeud *noeud)
{
    while (noeud && noeud->fg != NULL)
    {
        noeud = noeud->fg;
    }
    return noeud;
}

void Suppression(int x, Noeud **racine)
{
    Noeud *noeud = *racine;
    Noeud *parent = NULL;
    Noeud *enfant = NULL;
    Noeud *successeur = NULL;

    // 1. Recherche du nœud contenant la clé x à supprimer
    while (noeud != NULL && noeud->cle != x)
    {
        parent = noeud;
        if (x < noeud->cle)
        {
            noeud = noeud->fg;
        }
        else
        {
            noeud = noeud->fd;
        }
    }

    // Si le nœud n'est pas trouvé, on sort
    if (noeud == NULL)
    {
        printf("L'élément %d n'existe pas dans l'arbre.\n", x);
        return;
    }

    // 2. Cas où le nœud est une feuille (sans enfants)
    if (noeud->fg == NULL && noeud->fd == NULL)
    {
        if (parent == NULL)
        {
            *racine = NULL; // Si c'est la racine, l'arbre devient vide
        }
        else
        {
            if (parent->fg == noeud)
            {
                parent->fg = NULL; // Si le nœud est à gauche du parent
            }
            else
            {
                parent->fd = NULL; // Si le nœud est à droite du parent
            }
        }
        free(noeud);
        return;
    }

    // 3. Cas où le nœud a un seul enfant
    if (noeud->fg == NULL || noeud->fd == NULL)
    {
        if (noeud->fg != NULL)
        {
            enfant = noeud->fg;
        }
        else
        {
            enfant = noeud->fd;
        }

        if (parent == NULL)
        {
            *racine = enfant; // Si c'est la racine, on la remplace
        }
        else
        {
            if (parent->fg == noeud)
            {
                parent->fg = enfant;
            }
            else
            {
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
    while (noeud != successeur)
    {
        parent = noeud;
        noeud = noeud->fg;
    }

    // 5. Suppression du successeur
    if (noeud->fg == NULL && noeud->fd == NULL)
    {
        if (parent->fg == noeud)
        {
            parent->fg = NULL; // Le successeur est une feuille
        }
        else
        {
            parent->fd = NULL;
        }
    }
    else
    {
        enfant = (noeud->fg != NULL) ? noeud->fg : noeud->fd;
        if (parent->fg == noeud)
        {
            parent->fg = enfant;
        }
        else
        {
            parent->fd = enfant;
        }
    }

    free(noeud);
}

// Fonction d'insertion d'un élément dans l'arbre
void insertion(Noeud **racine, int x)
{
    // Création du nouveau noeud
    Noeud *p = malloc(sizeof(Noeud));
    if (p == NULL)
    {
        printf("Erreur d'allocation mémoire.\n");
        return; // Si l'allocation échoue, on quitte la fonction
    }

    p->cle = x;
    p->fg = NULL;
    p->fd = NULL;

    // Si l'arbre est vide, on place directement le noeud comme racine
    if (*racine == NULL)
    {
        *racine = p;
        return;
    }

    Noeud *noeud = *racine;
    Noeud *parent = NULL;
    int existe = 0;

    // Recherche de l'emplacement où insérer le nouveau noeud
    while (noeud != NULL && !existe)
    {
        parent = noeud;
        if (x == noeud->cle)
        {
            existe = 1; // L'élément existe déjà, on ne l'insère pas
        }
        else if (x < noeud->cle)
        {
            noeud = noeud->fg; // On continue la recherche à gauche
        }
        else
        {
            noeud = noeud->fd; // On continue la recherche à droite
        }
    }

    // Si l'élément n'existe pas, on insère le nouveau noeud
    if (!existe)
    {
        if (x < parent->cle)
        {
            parent->fg = p; // Insertion à gauche
        }
        else
        {
            parent->fd = p; // Insertion à droite
        }
    }
}

Noeud *recherche(Noeud *racine, int x)
{
    Noeud *noeud = racine;

    if (racine != NULL)
    {
        if (x == noeud->cle)
        {
            return noeud; // L'élément a été trouvé
        }
        else if (x < noeud->cle)
        {
            return recherche(noeud->fg, x); // Recherche à gauche
        }
        else
        {
            return recherche(noeud->fd, x); // Recherche à droite
        }
    }
    return NULL; // Si l'élément n'est pas trouvé, retourner NULL
}

void mesurer_complexite(Noeud **racine) {
    int tailles[] = {100, 200, 300, 400, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000, 30000};
    int taille_count = sizeof(tailles) / sizeof(tailles[0]);
    clock_t start, end;
    double time_taken_insert[sizeof(tailles) / sizeof(tailles[0])];
    double time_taken_search[sizeof(tailles) / sizeof(tailles[0])];
    double time_taken_delete[sizeof(tailles) / sizeof(tailles[0])];
    for (int j = 0; j < taille_count; j++) {
        srand(time(NULL));
        printf("\nCalcul des temps pour taille %d :\n", tailles[j]);

        // Mesurer le temps pour l'insertion
        start = clock();
        for (int i = 1; i <= tailles[j]; i++) {
            int rand_value = rand() % 1000 + 1;
            insertion(racine, rand_value);
        }
        end = clock();
        time_taken_insert[j] = ((double)(end - start)) / CLOCKS_PER_SEC;
       

        // Mesurer le temps pour la recherche
        start = clock();
        for (int k = 0; k < tailles[j]; k++) {
            int random_value = rand() % 1000 + 1;
            recherche(*racine, random_value);
        }
        end = clock();
        time_taken_search[j] = ((double)(end - start)) / CLOCKS_PER_SEC;
        

        // Mesurer le temps pour la suppression
        start = clock();
        for (int k = 0; k < tailles[j]; k++) {
            int random_value = rand() % 1000 + 1;
            Suppression(random_value, racine);
        }
        end = clock();
        time_taken_delete[j] = ((double)(end - start)) / CLOCKS_PER_SEC;
        
    }
    printf("Taille Insertion Recherche Suppression\n");
    for(int j=0;j<taille_count;j++){
        printf("%d  %f  %f  %f\n",tailles[j],time_taken_insert[j],time_taken_search[j],time_taken_delete[j]);
    }
}

// Fonction pour le parcours infixe (In-order)
void afficher_infixe(Noeud *racine) {
    if (racine != NULL) {
        afficher_infixe(racine->fg);   // Parcours du sous-arbre gauche
        printf("%d ", racine->cle);    // Affichage du nœud
        afficher_infixe(racine->fd); // Parcours du sous-arbre droit
    }
}

// Fonction pour le parcours préfixe (Pre-order)
void afficher_prefixe(Noeud *racine) {
    if (racine != NULL) {
        printf("%d ", racine->cle);    // Affichage du nœud
        afficher_prefixe(racine->fg); // Parcours du sous-arbre gauche
        afficher_prefixe(racine->fd);// Parcours du sous-arbre droit
    }
}

// Fonction pour le parcours postfixe (Post-order)
void afficher_postfixe(Noeud *racine) {
    if (racine != NULL) {
        afficher_postfixe(racine->fg);   // Parcours du sous-arbre gauche
        afficher_postfixe(racine->fd); // Parcours du sous-arbre droit
        printf("%d ", racine->cle);      // Affichage du nœud
    }
}



void menu_abr(Noeud **racine)
{
    int choix, valeur, i;
    Noeud *resultat;
    do
    {
        printf("\n--- Menu de traitement de l'arbre binaire de recherche ---\n");
        printf("1. Insertion\n");
        printf("2. Suppression\n");
        printf("3. Recherche\n");
        printf("4. Calculer le temps d'exécution (complexite experimentale)\n");
        printf("5. Retour au Menu Principale\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            printf("Entrez la valeur à insérer : ");
            scanf("%d", &valeur);
            insertion(racine, valeur);
            printf("Valeur %d insérée dans l'arbre.\n", valeur);
            printf("--Affichege de l'arbre--\n");
            printf("Postfixe:\n");
            afficher_postfixe(*racine);
            printf("\nPrefixe:\n");
            afficher_prefixe(*racine);
            printf("\nInfixe:\n");
            break;

        case 2:
            printf("Entrez la valeur à supprimer : ");
            scanf("%d", &valeur);
            Suppression(valeur, racine);
            printf("Valeur %d supprimée de l'arbre (si elle était présente).\n", valeur);
            printf("--Affichege de l'arbre--\n");
            printf("Postfixe:\n");
            afficher_postfixe(*racine);
            printf("\nPrefixe:\n");
            afficher_prefixe(*racine);
            printf("\nInfixe:\n");
            break;

        case 3:
            printf("Entrez la valeur à rechercher : ");
            scanf("%d", &valeur);
            resultat = recherche(*racine, valeur);
            if (resultat != NULL)
            {
                printf("Valeur %d trouvée dans l'arbre.\n", valeur);
            }
            else
            {
                printf("Valeur %d non trouvée dans l'arbre.\n", valeur);
            }
            break;

        case 4:
            mesurer_complexite(racine);
            break;
        

        case 5:
            printf("Quitter le programme.\n");
            break;

        default:
            printf("Option invalide, veuillez réessayer.\n");
        }
    } while (choix != 5);
}
