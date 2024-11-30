import random
import time

# Définition d'un nœud pour une liste chaînée bidirectionnelle
class Node:
    def __init__(self, data):
        self.data = data
        self.prev = None
        self.next = None

# Fonction pour insérer un élément dans la liste (triée)
def insert(head, value):
    new_node = Node(value)
    if head is None:
        head = new_node
        return head
    
    current = head
    previous = None
    
    # Trouver la position correcte pour insérer
    while current is not None and current.data < value:
        previous = current
        current = current.next
    
    # Insérer au début
    if previous is None:
        new_node.next = head
        head.prev = new_node
        head = new_node
    else:
        # Insérer au milieu ou à la fin
        new_node.next = current
        new_node.prev = previous
        previous.next = new_node
        if current is not None:
            current.prev = new_node

    return head

# Fonction pour supprimer un nœud dans la liste
def delete_node(head, key):
    current = head
    # Recherche du nœud à supprimer
    while current is not None and current.data != key:
        current = current.next
    
    # Si le nœud n'existe pas, on retourne
    if current is None:
        return head
    
    # Si le nœud à supprimer est le premier
    if current.prev is None:
        head = current.next
        if head is not None:
            head.prev = None
    else:
        current.prev.next = current.next
        if current.next is not None:
            current.next.prev = current.prev

    del current
    return head

# Fonction pour supprimer un élément par sa clé
def remove_key(head, key):
    current = head
    # Chercher le nœud à supprimer
    while current is not None and current.data != key:
        current = current.next
    
    if current is None:
        print("Clé non trouvée.")
        return head

    # Supprimer le nœud
    if current.prev is not None:
        current.prev.next = current.next
    else:
        head = current.next
    
    if current.next is not None:
        current.next.prev = current.prev
    
    del current
    print(f"Clé {key} supprimée avec succès.")
    return head

# Fonction pour rechercher un élément dans la liste
def search(head, key):
    current = head
    while current is not None:
        if current.data == key:
            return True
        current = current.next
    return False

# Fonction pour afficher la liste
def print_list(head):
    if head is None:
        print("La liste est vide.")
        return
    current = head
    print("Liste : ", end="")
    while current is not None:
        print(current.data, end=" ")
        current = current.next
    print()

# Fonction pour mesurer le temps d'exécution des insertions
def experiment():
    head = None
    n_values = [1, 100, 10000, 100000]  # Différentes tailles de données
    print("Expérimentation sur les temps d'insertion :")
    print("-------------------------------------------------")
    print("| Nombre d'éléments | Temps d'insertion (ms)   |")
    print("-------------------------------------------------")
    
    for n in n_values:
        start_time = time.time()
        # Libérer la liste pour chaque test
        while head is not None:
            head = delete_node(head, head.data)
        
        # Mesurer le temps d'insertion de n éléments aléatoires
        for _ in range(n):
            value = random.randint(0, 999)  # Valeurs aléatoires entre 0 et 999
            head = insert(head, value)
        
        end_time = time.time()
        elapsed_time = (end_time - start_time) * 1000  # en millisecondes
        print(f"| {n:17d} | {elapsed_time:24.3f} ms |")
    
    print("-------------------------------------------------")
    print("Fin de l'expérimentation.")

# Fonction principale pour gérer les opérations sur la liste chaînée bidirectionnelle
def bd_operations():
    head = None
    tree_size = 30
    random.seed(time.time())

    # Remplir la liste avec des valeurs initiales
    for _ in range(tree_size):
        value = random.randint(0, 999)  # Plage plus petite
        head = insert(head, value)

    print("Liste Initiale : ")
    print_list(head)

    while True:
        print("\nOpérations sur la Liste Chaînée Bidirectionnelle :")
        print("1. Insérer")
        print("2. Supprimer")
        print("3. Rechercher")
        print("4. Afficher la Liste")
        print("5. Expérimentation")
        print("6. Retour au menu principal")
        choice = int(input("Entrez votre choix : "))

        if choice == 1:
            key = int(input("Entrez la clé à insérer : "))
            head = insert(head, key)
        elif choice == 2:
            key = int(input("Entrez la clé à supprimer : "))
            head = remove_key(head, key)
        elif choice == 3:
            key = int(input("Entrez la clé à rechercher : "))
            if search(head, key):
                print("Clé trouvée !")
            else:
                print("Clé non trouvée.")
        elif choice == 4:
            print_list(head)
        elif choice == 5:
            experiment()
        elif choice == 6:
            print("Retour au menu principal.")
            break
        else:
            print("Choix invalide. Veuillez réessayer.")

# Fonction principale
if __name__ == "__main__":
    bd_operations()
