#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "methodestrie.h"
#include "fonction.h"
int main()
{
    // menu
    int choix;
    printf("Votre choix : ");

    printf("Choisissez si vous voulez un tableau dans :\n");
    printf("1. Tri de gnome (tapez 1)\n");
    printf("2. Tri rapide (tapez 2)\n");
    printf("3. Tri par fusion (tapez 3)\n");

    if (scanf("%d", &choix) != 1)
    {
        printf("Erreur : veuillez entrer un numéro valide.\n");
        exit(EXIT_FAILURE); // Si l'entrée n'est pas un nombre
    }
    // scanf("%d",&choix);
    switch (choix)
    {

    case 1:
    {
        printf("Tri gnome : \n\n");
        gnome();
        break;
    }
    case 2:
    {
        printf("Tri rapide : \n\n");
        rapide();
        break;
    }
    case 3:
    {
        printf("Tri Par Fusion : \n\n");
        TriParFusion();
        break;
    }
    }
    return 0;
}
