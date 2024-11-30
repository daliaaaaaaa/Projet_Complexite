import pandas as pd
import matplotlib.pyplot as plt

# Charger les données depuis le fichier CSV
csv_file = 'complexite_temps_bd_exp.csv'  # Remplacez ceci par le chemin de votre fichier CSV
data = pd.read_csv(csv_file)

# Extraire les données du CSV
sizes = data['Taille']
insertion_times = data['Temps insertion (ms)']
search_times = data['Temps recherche (ms)']
deletion_times = data['Temps suppression (ms)']

# Calcul de la complexité théorique y = x
theoretical_complexity = sizes  # y = x

# Création du graphique
plt.figure(figsize=(10, 6))

# Graphiques pour chaque opération
plt.plot(sizes, insertion_times, label="Temps d'insertion (ms)", marker='o', color='blue')
plt.plot(sizes, search_times, label="Temps de recherche (ms)", marker='o', color='green')
plt.plot(sizes, deletion_times, label="Temps de suppression (ms)", marker='o', color='red')

# Ajout de la courbe y = x (complexité théorique)
plt.plot(sizes, theoretical_complexity, label="Complexité théorique (y=x)", linestyle='--', color='black')

# Paramétrage du graphique
plt.xlabel("Taille")
plt.ylabel("Temps (ms)")
plt.title("Temps d'insertion, recherche et suppression vs Taille avec Complexité théorique")
plt.legend()
plt.grid(True)

# Affichage du graphique
plt.show()
plt.savefig("complexite_temps_bd_exp.png")