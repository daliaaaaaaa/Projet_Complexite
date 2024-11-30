#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Definition d'un nœud pour une liste chaînee bidirectionnelle
typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

// Fonction pour inserer un element dans la liste (triee)
void insert(Node **head, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node *current = *head;
    Node *previous = NULL;

    // Trouver la position correcte pour inserer
    while (current != NULL && current->data < value) {
        previous = current;
        current = current->next;
    }

    // Inserer au debut
    if (previous == NULL) {
        new_node->next = *head;
        (*head)->prev = new_node;
        *head = new_node;
    }
    // Inserer au milieu ou à la fin
    else {
        new_node->next = current;
        new_node->prev = previous;
        previous->next = new_node;
        if (current != NULL) {
            current->prev = new_node;
        }
    }
}
// Fonction pour supprimer un nœud dans la liste
void delete_node(Node **head, int key) {
    Node *current = *head;
    
    // Recherche du nœud à supprimer
    while (current != NULL && current->data != key) {
        current = current->next;
    }

    // Si le nœud n'existe pas, on retourne
    if (current == NULL) {
        return;
    }

    // Si le nœud à supprimer est le premier
    if (current->prev == NULL) {
        *head = current->next;
        if (*head != NULL) {
            (*head)->prev = NULL;
        }
    } else {
        current->prev->next = current->next;
        if (current->next != NULL) {
            current->next->prev = current->prev;
        }
    }

    free(current); // Liberer la memoire du nœud supprime
}

// Fonction pour supprimer un element par sa cle
void removeKey(Node **head, int key) {
    if (*head == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    Node *current = *head;

    // Chercher le nœud à supprimer
    while (current != NULL && current->data != key) {
        current = current->next;
    }

    if (current == NULL) {
        printf("Cle non trouvee.\n");
        return;
    }

    // Supprimer le nœud
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    free(current);
    printf("Cle %d supprimee avec succès.\n", key);
}

// Fonction pour rechercher un element dans la liste
bool search(Node *head, int key) {
    Node *current = head;

    while (current != NULL) {
        if (current->data == key) {
            return true;
        }
        current = current->next;
    }

    return false;
}

// Fonction pour afficher la liste
void print_tree(Node *head) {
    Node *current = head;

    if (current == NULL) {
        printf("La liste est vide.\n");
        return;
    }

    printf("Liste : ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Fonction pour mesurer le temps d'execution des insertions
void experiment() {
    struct Node* head = NULL;
    int n_values[] = {1, 100, 10000, 100000}; // Differentes tailles de donnees
    int n_tests = sizeof(n_values) / sizeof(n_values[0]);
    
    printf("Experimentation sur les temps d'insertion :\n");
    printf("-------------------------------------------------\n");
    printf("| Nombre d'elements | Temps d'insertion (ms)   |\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < n_tests; i++) {
        int n = n_values[i];
        clock_t start_time, end_time;
        double elapsed_time;

        // Liberer la liste pour chaque test (si elle contient des donnees precedentes)
        while (head != NULL) {
            delete_node(&head, head->data);
        }

        // Mesurer le temps d'insertion de n elements aleatoires
        start_time = clock();
        for (int j = 0; j < n; j++) {
            int value = rand() % 1000; // Valeurs aleatoires entre 0 et 999
            insert(&head, value);
        }
        end_time = clock();

        // Calculer le temps ecoule en millisecondes
        elapsed_time = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000;
        printf("| %17d | %24.3f ms |\n", n, elapsed_time);
    }
    
    printf("-------------------------------------------------\n");
    printf("Fin de l'experimentation.\n");
}


// Fonction principale pour gerer les operations sur la liste chaînee bidirectionnelle
void bd_operations() {
    int choice = 0, key;
    const int tree_size = 30;

    Node *head = NULL;

    // Remplir la liste avec des valeurs initiales
    srand(time(NULL));
    for (int j = 0; j < tree_size; j++) {
        int value = rand() % 1000; // Plage plus petite
        insert(&head, value);
    }

    printf("Liste Initiale : \n");
    print_tree(head);

    while (choice != 6) {
        printf("\nOperations sur la Liste Chainee Bidirectionnelle :\n");
        printf("1. Inserer\n");
        printf("2. Supprimer\n");
        printf("3. Rechercher\n");
        printf("4. Afficher la Liste\n");
        printf("5. Experimentation\n");
        printf("6. Retour au menu principal\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Entrez la cle a inserer : ");
            scanf("%d", &key);
            insert(&head, key);
            break;

        case 2:
            printf("Entrez la cle a supprimer : ");
            scanf("%d", &key);
            removeKey(&head, key);
            break;

        case 3:
            printf("Entrez la cle a rechercher : ");
            scanf("%d", &key);
            if (search(head, key)) {
                printf("Cle trouvee !\n");
            } else {
                printf("Cle non trouvee.\n");
            }
            break;

        case 4:
            print_tree(head);
            break;

        case 5:
            experiment();
            break;

        case 6:
            printf("Retour au menu principal.\n");
            break;

        default:
            printf("Choix invalide. Veuillez reessayer.\n");
        }
    }
}

// Fonction principale


// int main() {
//     bd_operations();
//     return 0;
// }
