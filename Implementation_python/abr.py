import time
import random


class Noeud:
    def __init__(self, cle):
        self.cle = cle
        self.fg = None  # Fils gauche
        self.fd = None  # Fils droit


def minimum(noeud):
    while noeud and noeud.fg is not None:
        noeud = noeud.fg
    return noeud


def suppression(x, racine):
    parent = None
    noeud = racine

    # 1. Recherche du nœud à supprimer
    while noeud is not None and noeud.cle != x:
        parent = noeud
        if x < noeud.cle:
            noeud = noeud.fg
        else:
            noeud = noeud.fd

    if noeud is None:
        print(f"L'élément {x} n'existe pas dans l'arbre.")
        return racine

    # 2. Suppression
    if noeud.fg is None and noeud.fd is None:  # Cas feuille
        if parent is None:
            return None
        elif parent.fg == noeud:
            parent.fg = None
        else:
            parent.fd = None

    elif noeud.fg is None or noeud.fd is None:  # Cas un seul enfant
        enfant = noeud.fg if noeud.fg is not None else noeud.fd
        if parent is None:
            return enfant
        elif parent.fg == noeud:
            parent.fg = enfant
        else:
            parent.fd = enfant

    else:  # Cas deux enfants
        successeur = minimum(noeud.fd)
        noeud.cle = successeur.cle
        noeud.fd = suppression(successeur.cle, noeud.fd)

    return racine


def insertion(racine, x):
    if racine is None:
        return Noeud(x)

    parent = None
    noeud = racine
    while noeud is not None:
        parent = noeud
        if x == noeud.cle:
            return racine  # Ne pas insérer de doublons
        elif x < noeud.cle:
            noeud = noeud.fg
        else:
            noeud = noeud.fd

    if x < parent.cle:
        parent.fg = Noeud(x)
    else:
        parent.fd = Noeud(x)

    return racine


def recherche(racine, x):
    noeud = racine
    while noeud is not None:
        if x == noeud.cle:
            return noeud
        elif x < noeud.cle:
            noeud = noeud.fg
        else:
            noeud = noeud.fd
    return None


def mesurer_complexite():
    tailles = [100, 200, 300, 400, 500, 1000, 2000, 3000]
    temps_insertion = []
    temps_recherche = []
    temps_suppression = []

    for taille in tailles:
        racine = None
        valeurs = random.sample(range(1, 10000), taille)

        # Temps d'insertion
        start = time.time()
        for v in valeurs:
            racine = insertion(racine, v)
        end = time.time()
        temps_insertion.append(end - start)

        # Temps de recherche
        start = time.time()
        for _ in range(taille):
            recherche(racine, random.choice(valeurs))
        end = time.time()
        temps_recherche.append(end - start)

        # Temps de suppression
        start = time.time()
        for v in valeurs:
            racine = suppression(v, racine)
        end = time.time()
        temps_suppression.append(end - start)

    print("Taille  Insertion  Recherche  Suppression")
    for i, taille in enumerate(tailles):
        print(f"{taille:6}  {temps_insertion[i]:.5f}  {temps_recherche[i]:.5f}  {temps_suppression[i]:.5f}")


def menu_abr():
    racine = None
    while True:
        print("\n--- Menu ABR ---")
        print("1. Insertion")
        print("2. Suppression")
        print("3. Recherche")
        print("4. Mesurer complexité")
        print("5. Quitter")
        choix = int(input("Votre choix : "))

        if choix == 1:
            valeur = int(input("Entrez une valeur à insérer : "))
            racine = insertion(racine, valeur)
            print(f"Valeur {valeur} insérée.")
        elif choix == 2:
            valeur = int(input("Entrez une valeur à supprimer : "))
            racine = suppression(valeur, racine)
            print(f"Valeur {valeur} supprimée (si elle existait).")
        elif choix == 3:
            valeur = int(input("Entrez une valeur à rechercher : "))
            resultat = recherche(racine, valeur)
            if resultat:
                print(f"Valeur {valeur} trouvée.")
            else:
                print(f"Valeur {valeur} non trouvée.")
        elif choix == 4:
            mesurer_complexite()
        elif choix == 5:
            print("Quitter le programme.")
            break
        else:
            print("Option invalide.")


# Exemple d'exécution
menu_abr()
