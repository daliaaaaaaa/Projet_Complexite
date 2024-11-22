#include <stdio.h>
#include <stdlib.h>
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

#include <time.h> // Inclure time.h pour clock()

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
        {
            
            FILE *file = fopen("complexite_temps_abr.csv", "w");
            int tailles[] = {100, 500, 1000, 15000, 20000, 25000, 30000}; // Tailles de l'arbre
            int taille_count = sizeof(tailles) / sizeof(tailles[0]);
            clock_t start, end;
            double time_taken;
            fprintf(file, "Taille,temps insertion,temps recherche,temps suppression\n");
            for (int j = 0; j < taille_count; j++)
            {
                srand(time(NULL)); 
                printf("\nCalcul des temps pour taille %d :\n", tailles[j]);
                fprintf(file, "%d ", tailles[j]);
                // Mesurer le temps pour l'insertion
                start = clock();
                for (i = 1; i <= tailles[j]; i++)
                {
                    int rand_value=rand()%1000+1;
                    insertion(racine, i);
                }
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Convertir en millisecondes
                printf("Temps pour insertion de %d noeuds : %.2f ms\n", tailles[j], time_taken);
                fprintf(file, " %f ", time_taken);
                // Mesurer le temps pour la recherche
                start = clock();
                
                for (int k = 0; k < tailles[j]; k++) {  // Répéter la recherche 10 fois pour chaque taille
                    int random_value = rand() % 1000 + 1;
                    recherche(*racine, random_value);
                }
                
                end = clock();
                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Convertir en millisecondes
                printf("Temps pour recherche de %d noeuds : %.2f ms\n", tailles[j], time_taken);
                fprintf(file, " %f ", time_taken);
                // Mesurer le temps pour la suppression
               
                start = clock();
                for (int k = 0; k < tailles[j]; k++) {  // Répéter la suppression 10 fois pour chaque taille
                    int random_value = rand() % 1000 + 1;
                    Suppression(random_value, racine);
                }
                end = clock();

                time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Convertir en millisecondes
                printf("Temps pour suppression de %d noeuds : %.2f ms\n", tailles[j], time_taken);
                fprintf(file, " %f \n", time_taken);
            }
            fclose(file);
            break;
        }

        case 5:
            printf("Quitter le programme.\n");
            break;

        default:
            printf("Option invalide, veuillez réessayer.\n");
        }
    } while (choix != 5);
}
