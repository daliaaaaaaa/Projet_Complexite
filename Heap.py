def echanger(a, i, j):
    """
    Échange deux éléments dans une liste.
    :param a: Liste contenant les éléments.
    :param i: Indice du premier élément.
    :param j: Indice du second élément.
    """
    temp = a[i]
    a[i] = a[j]
    a[j] = temp

def entasser_min(arr, n, i):
    """
    Maintient la propriété de Min-Heap pour un sous-arbre enraciné à l'indice i.
    :param arr: Tableau représentant le tas.
    :param n: Nombre total d'éléments dans le tas.
    :param i: Indice du noeud à entasser.
    """
    plus_petit = i  # Supposons que le noeud courant est le plus petit
    gauche = 2 * i + 1  # Indice du fils gauche
    droite = 2 * i + 2  # Indice du fils droit

    # Vérifier si le fils gauche existe et est plus petit que le noeud courant
    if gauche < n and arr[gauche] < arr[plus_petit]:
        plus_petit = gauche

    # Vérifier si le fils droit existe et est plus petit que le plus petit actuel
    if droite < n and arr[droite] < arr[plus_petit]:
        plus_petit = droite

    # Si le plus petit n'est pas le noeud courant, échanger et entasser récursivement
    if plus_petit != i:
        echanger(arr, i, plus_petit)
        entasser_min(arr, n, plus_petit)

def construire_tas_min(arr):
    """
    Convertit un tableau non structuré en un Min-Heap valide.
    :param arr: Tableau représentant les éléments à organiser.
    """
    n = len(arr)
    # Commence à entasser à partir du dernier noeud parent
    for i in range(n // 2 - 1, -1, -1):
        entasser_min(arr, n, i)

def inserer_element(arr, element):
    """
    Ajoute un nouvel élément au Min-Heap et maintient sa propriété.
    :param arr: Liste représentant le tas.
    :param element: Valeur à insérer.
    """
    arr.append(element)  # Ajouter l'élément à la fin
    i = len(arr) - 1     # Indice de l'élément ajouté
    parent = (i - 1) // 2

    # Remonter l'élément pour maintenir la propriété de Min-Heap
    while i > 0 and arr[i] < arr[parent]:
        echanger(arr, i, parent)
        i = parent
        parent = (i - 1) // 2

def supprimer_min(arr):
    """
    Supprime l'élément minimum (racine) d'un Min-Heap et maintient sa propriété.
    :param arr: Liste représentant le tas.
    """
    if len(arr) == 0:
        return None  # Le tas est vide
    if len(arr) == 1:
        return arr.pop()  # Un seul élément dans le tas

    racine = arr[0]  # Enregistrer la racine à retourner
    arr[0] = arr.pop()  # Remplacer la racine par le dernier élément
    entasser_min(arr, len(arr), 0)  # Restaurer la propriété de Min-Heap
    return racine



def entasser_max(arr, n, i):
    """
    Maintient la propriété de Max-Heap pour un sous-arbre enraciné à l'indice i.
    :param arr: Tableau représentant le tas.
    :param n: Nombre total d'éléments dans le tas.
    :param i: Indice du noeud à entasser.
    """
    plus_grand = i  # Supposons que le noeud courant est le plus grand
    gauche = 2 * i + 1  # Indice du fils gauche
    droite = 2 * i + 2  # Indice du fils droit

    # Vérifier si le fils gauche existe et est plus grand que le noeud courant
    if gauche < n and arr[gauche] > arr[plus_grand]:
        plus_grand = gauche

    # Vérifier si le fils droit existe et est plus grand que le plus grand actuel
    if droite < n and arr[droite] > arr[plus_grand]:
        plus_grand = droite

    # Si le plus grand n'est pas le noeud courant, échanger et entasser récursivement
    if plus_grand != i:
        echanger(arr, i, plus_grand)
        entasser_max(arr, n, plus_grand)

def construire_tas_max(arr):
    """
    Convertit un tableau non structuré en un Max-Heap valide.
    :param arr: Tableau représentant les éléments à organiser.
    """
    n = len(arr)
    # Commence à entasser à partir du dernier noeud parent
    for i in range(n // 2 - 1, -1, -1):
        entasser_max(arr, n, i)

def inserer_element(arr, element):
    """
    Ajoute un nouvel élément au Max-Heap et maintient sa propriété.
    :param arr: Liste représentant le tas.
    :param element: Valeur à insérer.
    """
    arr.append(element)  # Ajouter l'élément à la fin
    i = len(arr) - 1     # Indice de l'élément ajouté
    parent = (i - 1) // 2

    # Remonter l'élément pour maintenir la propriété de Max-Heap
    while i > 0 and arr[i] > arr[parent]:
        echanger(arr, i, parent)
        i = parent
        parent = (i - 1) // 2

def supprimer_max(arr):
    """
    Supprime l'élément maximum (racine) d'un Max-Heap et maintient sa propriété.
    :param arr: Liste représentant le tas.
    """
    if len(arr) == 0:
        return None  # Le tas est vide
    if len(arr) == 1:
        return arr.pop()  # Un seul élément dans le tas

    racine = arr[0]  # Enregistrer la racine à retourner
    arr[0] = arr.pop()  # Remplacer la racine par le dernier élément
    entasser_max(arr, len(arr), 0)  # Restaurer la propriété de Max-Heap
    return racine


def rechercher_element(arr, n, element):
    """
    Recherche un élément spécifique dans une liste.

    :param arr: Liste d'entiers à parcourir.
    :param n: Taille de la liste.
    :param element: Élément à rechercher.
    :return: Index de l'élément s'il est trouvé, sinon -1.
    """
    # Parcourir chaque élément de la liste jusqu'à la taille spécifiée `n`
    for i in range(n):
        # Vérifier si l'élément courant est égal à l'élément recherché
        if arr[i] == element:
            # Si trouvé, retourner l'indice actuel
            return i

    # Si l'élément n'a pas été trouvé après avoir parcouru toute la liste, retourner -1
    return -1

arr=[3, 2, 1, 7, 8, 4, 10, 16, 12]