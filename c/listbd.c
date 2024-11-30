#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Définition d'un nœud pour une liste chaînée bidirectionnelle
typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

// Fonction pour insérer un élément dans la liste (triée)
void insertbd(Node **head, int value) {
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

    while (current != NULL && current->data < value) {
        previous = current;
        current = current->next;
    }

    if (previous == NULL) {
        new_node->next = *head;
        (*head)->prev = new_node;
        *head = new_node;
    } else {
        new_node->next = current;
        new_node->prev = previous;
        previous->next = new_node;
        if (current != NULL) {
            current->prev = new_node;
        }
    }
}

// Fonction pour supprimer un nœud dans la liste
void delete_nodebd(Node **head, int key) {
    Node *current = *head;

    while (current != NULL && current->data != key) {
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

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

    free(current);
}

// Fonction pour rechercher un élément dans la liste
bool searchbd(Node *head, int key) {
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
void print_bd(Node *head) {
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

// Fonction pour exporter la liste dans un fichier CSV
void export_to_csv(Node *head, const char *filename) {
    FILE *file = fopen("../Experimentation/complexite_temps_bd.csv", "w");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", filename);
        return;
    }

    fprintf(file, "Index,Data\n");
    Node *current = head;
    int index = 0;

    while (current != NULL) {
        fprintf(file, "%d,%d\n", index++, current->data);
        current = current->next;
    }

    fclose(file);
    printf("Données exportées avec succès dans le fichier %s.\n", filename);
}

// Fonction pour mesurer les performances et exporter dans un fichier CSV
void measure_and_export_performance(const char *filename) {
    const int sizes[] = {100, 1000, 10000}; // Tailles pour l'expérimentation
    const int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    FILE *file = fopen(filename, "w+");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", filename);
        return;
    }

    fprintf(file, "Taille,Temps insertion (ms),Temps recherche (ms),Temps suppression (ms)\n");

    for (int i = 0; i < num_sizes; i++) {
        int size = sizes[i];
        Node *head = NULL;
        clock_t start, end;

        start = clock();
        for (int j = 0; j < size; j++) {
            int value = rand() % 1000;
            insertbd(&head, value);
        }
        end = clock();
        double insertion_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

        start = clock();
        for (int j = 0; j < size; j++) {
            int value = rand() % 1000;
            searchbd(head, value);
        }
        end = clock();
        double search_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000 / size;

        start = clock();
        for (int j = 0; j < size; j++) {
            delete_nodebd(&head, rand() % 1000);
        }
        end = clock();
        double deletion_time = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;

        fprintf(file, "%d,%.2f,%.2f,%.2f\n", size, insertion_time, search_time, deletion_time);
        printf("Données pour taille %d exportées : %.2f ms insertion, %.2f ms recherche, %.2f ms suppression.\n",
               size, insertion_time, search_time, deletion_time);
    }

    fclose(file);
    printf("Performances exportées avec succès dans le fichier %s.\n", filename);
}

// Fonction principale pour gérer les opérations sur la liste chaînée bidirectionnelle
void bd_operations() {
    int choice = 0, key;
    const int tree_size = 30;

    Node *head = NULL;

    srand(time(NULL));
    for (int j = 0; j < tree_size; j++) {
        int value = rand() % 1000;
        insertbd(&head, value);
    }

    printf("Liste Initiale : \n");
    print_bd(head);

    while (choice != 7) {
        printf("\nOpérations sur la Liste Chaînée Bidirectionnelle :\n");
        printf("1. Insérer\n");
        printf("2. Supprimer\n");
        printf("3. Rechercher\n");
        printf("4. Afficher la Liste\n");
        printf("5. Exporter vers CSV\n");
        printf("6. Mesurer et exporter les performances\n");
        printf("7. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Entrez la clé à insérer : ");
            scanf("%d", &key);
            insertbd(&head, key);
            break;

        case 2:
            printf("Entrez la clé à supprimer : ");
            scanf("%d", &key);
            delete_nodebd(&head, key);
            break;

        case 3:
            printf("Entrez la clé à rechercher : ");
            scanf("%d", &key);
            if (searchbd(head, key)) {
                printf("Clé trouvée !\n");
            } else {
                printf("Clé non trouvée.\n");
            }
            break;

        case 4:
            print_bd(head);
            break;

        case 5:
            export_to_csv(head, "../Experimentation/complexite_temps_bd.csv");
            break;

        case 6:
            measure_and_export_performance("performance.csv");
            break;

        case 7:
            printf("Quitter.\n");
            break;

        default:
            printf("Choix invalide. Veuillez réessayer.\n");
        }
    }
}

// Fonction principale
int main() {
    bd_operations();
    return 0;
}
