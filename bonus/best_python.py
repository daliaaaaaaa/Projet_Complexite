import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

# Lecture des données depuis le fichier CSV 'best_cas_genom.csv'
data = pd.read_csv('best_cas_genom.csv')

# Affichage des colonnes pour vérifier leur nom
print("Colonnes dans le fichier CSV : ", data.columns)

# Extraction des données
sizes = data['Taille des Données (n)']
execution_times = data['Temps d\'Execution (secondes)']

# Génération de la courbe de complexité y = x^2
complexity = sizes ** 2

# Plotting
plt.figure(figsize=(8, 6))

# Graphique pour les données (Temps d'Execution)
plt.plot(sizes, execution_times, marker='o', linestyle='-', color='b', label="Temps d'Execution")

# Graphique pour la complexité y = x^2
plt.plot(sizes, complexity, linestyle='--', color='r', label="Complexité (y = x^2)")

# Labels et titre
plt.xlabel("Taille des Données (n)")
plt.ylabel("Temps d'Execution (secondes)")
plt.title("Graphique: Taille des Données vs Temps d'Execution et Complexité")

# Légende
plt.legend()

# Affichage du graphique
plt.grid(True)
plt.show()
plt.savefig("complexite_temps_best_gnom.png")