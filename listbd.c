#include <stdio.h>
#include <stdlib.h>
#include<time.h>

//dans les listes doublements chainees on rajoute juste un deusieme pointeur precedant
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

//declaration de la liste doublement chiannes 
typedef struct Listbd {
    int info;
    struct Listbd* svt;
    struct Listbd* prc;
} Listbd;

//creation de la liste elle retourne le pointeur de la cellule for the first time  
Listbd* createNode(int info) {
    Listbd* pbd = (Listbd*)malloc(sizeof(Listbd));
    pbd->info = info;
    pbd->svt = NULL;
    pbd->prc = NULL;
    return pbd;
}

//insertion dans la tete 
void insertAttete(Listbd** tete, int info) {
    Listbd* pbd = createNode(info);
    pbd->svt = *tete;
    if (*tete != NULL) {
        (*tete)->prc = pbd;
    }
    *tete = pbd;
}

//insertion dans la queue de la liste
void insertAtqueue(Listbd** tete, int info) {
    Listbd* pbd = createNode(info);
    if (*tete == NULL) {
        *tete = pbd;
        return;
    }
    Listbd* temp = *tete;
    while (temp->svt != NULL) {
        temp = temp->svt;
    }
    temp->svt = pbd;
    pbd->prc = temp;
}


void affiche_tete(Listbd* tete) {
    Listbd* temp = tete;
    printf("Liste dans l'ordre : ");
    while (temp != NULL) {
        printf("%d ", temp->info);
        temp = temp->svt;
    }
    printf("\n");
}
//affichage de la liste dans les deux sense 
void affiche_queue(Listbd* queue) {
    Listbd* temp = queue;
    printf("Liste dans l'ordre inverse : ");
    while (temp != NULL) {
        printf("%d ", temp->info);
        temp = temp->prc;
    }
    printf("\n");
}

//supression d'un element de la liste doublement chinees
void supp_ele(Listbd** tete, int key) {
    Listbd* temp = *tete;

    // Rechercher le nœud à supprimer
    while (temp != NULL && temp->info != key) {
        temp = temp->svt;
    }

    // Si le nœud n'existe pas
    if (temp == NULL) return;

    // Mise à jour des pointeurs pour le supprimer
    if (temp->prc != NULL) {
        temp->prc->svt = temp->svt;
    } else {
        *tete = temp->svt;
    }

    if (temp->svt != NULL) {
        temp->svt->prc = temp->prc;
    }

    free(temp);
}


void listbd_operations() {
    Listbd* tete = NULL;

    insertAttete(&tete, 10);
    insertAttete(&tete, 20);
    insertAtqueue(&tete, 30);

    affiche_tete(tete);

    // Obtenir le dernier element pour afficher en ordre inverse
    Listbd* queue = tete;
    while (queue->svt != NULL) {
        queue = queue->svt;
    }
    affiche_queue(queue);

    supp_ele(&tete, 20);

    affiche_tete(tete);


/*
clock_t t1, t2;
float delta;
t1=clock();
//fonction
t2=clock();
printf("\n");
delta =(t2-t1)/CLOCKS_PER_SEC;
Affichage(tab, n);
printf("\nLe temps d'execution = %f secondes pour n = %d",delta,n);
*/
    return 0;
}
