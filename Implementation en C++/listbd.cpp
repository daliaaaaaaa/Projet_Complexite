#include <iostream>
#include <cstdlib>
#include <ctime>

// Definition of a node for a doubly linked list
struct Node {
    int data;
    Node* prev;
    Node* next;
};

// Function to insert an element into the list (sorted)
void insert(Node** head, int value) {
    Node* new_node = new Node();
    new_node->data = value;
    new_node->prev = NULL;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* current = *head;
    Node* previous = NULL;

    // Find the correct position to insert
    while (current != NULL && current->data < value) {
        previous = current;
        current = current->next;
    }

    // Insert at the beginning
    if (previous == NULL) {
        new_node->next = *head;
        (*head)->prev = new_node;
        *head = new_node;
    }
    // Insert in the middle or at the end
    else {
        new_node->next = current;
        new_node->prev = previous;
        previous->next = new_node;
        if (current != NULL) {
            current->prev = new_node;
        }
    }
}

// Function to delete a node from the list
void delete_node(Node** head, int key) {
    Node* current = *head;
    
    // Search for the node to delete
    while (current != NULL && current->data != key) {
        current = current->next;
    }

    // If the node doesn't exist, return
    if (current == NULL) {
        return;
    }

    // If the node to delete is the first
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

    delete current; // Free memory for the deleted node
}

// Function to remove a node by its key
void removeKey(Node** head, int key) {
    if (*head == NULL) {
        std::cout << "The list is empty.\n";
        return;
    }

    Node* current = *head;

    // Find the node to delete
    while (current != NULL && current->data != key) {
        current = current->next;
    }

    if (current == NULL) {
        std::cout << "Key not found.\n";
        return;
    }

    // Delete the node
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        *head = current->next;
    }

    if (current->next != NULL) {
        current->next->prev = current->prev;
    }

    delete current;
    std::cout << "Key " << key << " successfully deleted.\n";
}

// Function to search for an element in the list
bool search(Node* head, int key) {
    Node* current = head;

    while (current != NULL) {
        if (current->data == key) {
            return true;
        }
        current = current->next;
    }

    return false;
}

// Function to print the list
void print_list(Node* head) {
    Node* current = head;

    if (current == NULL) {
        std::cout << "The list is empty.\n";
        return;
    }

    std::cout << "List: ";
    while (current != NULL) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n";
}

// Function to perform the insertion time experiment
void experiment() {
    Node* head = NULL;
    int n_values[] = {1, 100, 10000, 100000}; // Different sizes of data
    int n_tests = sizeof(n_values) / sizeof(n_values[0]);
    
    std::cout << "Experiment on insertion times:\n";
    std::cout << "-------------------------------------------------\n";
    std::cout << "| Number of elements | Insertion time (ms)   |\n";
    std::cout << "-------------------------------------------------\n";

    for (int i = 0; i < n_tests; i++) {
        int n = n_values[i];
        clock_t start_time, end_time;
        double elapsed_time;

        // Clear the list for each test (if it contains previous data)
        while (head != NULL) {
            delete_node(&head, head->data);
        }

        // Measure the insertion time for n random elements
        start_time = clock();
        for (int j = 0; j < n; j++) {
            int value = rand() % 1000; // Random values between 0 and 999
            insert(&head, value);
        }
        end_time = clock();

        // Calculate elapsed time in milliseconds
        elapsed_time = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000;
        std::cout << "| " << n << "             | " << elapsed_time << " ms |\n";
    }
    
    std::cout << "-------------------------------------------------\n";
    std::cout << "End of experiment.\n";
}

// Main function to manage operations on the doubly linked list
void bd_operations() {
    int choice = 0, key;
    const int list_size = 30;

    Node* head = NULL;

    // Fill the list with initial random values
    srand(time(NULL));
    for (int j = 0; j < list_size; j++) {
        int value = rand() % 1000; // Smaller range
        insert(&head, value);
    }

    std::cout << "Initial List: \n";
    print_list(head);

    while (choice != 6) {
        std::cout << "\nOperations on Doubly Linked List:\n";
        std::cout << "1. Insert\n";
        std::cout << "2. Delete\n";
        std::cout << "3. Search\n";
        std::cout << "4. Print List\n";
        std::cout << "5. Experiment\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter the key to insert: ";
            std::cin >> key;
            insert(&head, key);
            break;

        case 2:
            std::cout << "Enter the key to delete: ";
            std::cin >> key;
            removeKey(&head, key);
            break;

        case 3:
            std::cout << "Enter the key to search: ";
            std::cin >> key;
            if (search(head, key)) {
                std::cout << "Key found!\n";
            } else {
                std::cout << "Key not found.\n";
            }
            break;

        case 4:
            print_list(head);
            break;

        case 5:
            experiment();
            break;

        case 6:
            std::cout << "Exiting...\n";
            break;

        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    }
}

int main() {
    bd_operations();
    return 0;
}
