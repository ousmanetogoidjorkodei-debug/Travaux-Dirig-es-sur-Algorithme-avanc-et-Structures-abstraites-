# TP : Complexité et Structures de Données Abstraites

**Filières :** IISD & IDRS — Semestre 2

---

## Structure du dépôt

```
tp_complexite/
├── TD1/
│   └── td1_structures.c        # Structures Point et Heure
├── TD2/
│   └── td2_complexite.c        # Complexité et récursivité
├── TD3/
│   └── td3_listes_piles_files.c # Listes, piles, files
├── TD4/
│   └── td4_abr.c               # Arbres Binaires de Recherche
└── README.md
```

---

## Compilation et exécution

```bash
# TD1
gcc TD1/td1_structures.c -o td1 -lm && ./td1

# TD2
gcc TD2/td2_complexite.c -o td2 && ./td2

# TD3
gcc TD3/td3_listes_piles_files.c -o td3 && ./td3

# TD4
gcc TD4/td4_abr.c -o td4 && ./td4
```

---

## Résumé des TDs

### TD1 — Les Structures
| Exercice | Sujet |
|----------|-------|
| Ex1 | Structure `Point` (coordonnées entières), tableau statique/dynamique, tri par distance |
| Ex2 | Structure `Heure` (hh:mm:ss), conversion secondes, addition, différence |

### TD2 — Complexité & Récursivité
| Exercice | Sujet | Complexité |
|----------|-------|-----------|
| Ex1 | Indice du minimum dans un tableau | O(n) |
| Ex2 | MiniMax d'une matrice n×m | O(n·m) |
| Ex3 | Puissance naive vs exponentiation rapide | O(n) vs O(log n) |
| Ex4 | `rec1` vs `rec2` (calculent 2ⁿ) | O(n) vs O(2ⁿ) |

### TD3 — Listes, Piles, Files
| Exercice | Sujet | Complexité |
|----------|-------|-----------|
| Ex1 | Créer une liste de 100 entiers aléatoires | O(n) |
| Ex2 | Rechercher une valeur | O(n) |
| Ex3 | Supprimer le nœud de valeur minimale | O(n) |
| Ex4 | Fusionner deux listes en alternance | O(n+m) |
| Ex5 | Détruire une liste (libérer la mémoire) | O(n) |
| Ex6 | Piles : séparer pairs et impairs | O(n) |
| Ex7 | Files + Pile : détecter un palindrome | O(n) |

### TD4 — Arbres Binaires de Recherche (ABR)
| Exercice | Sujet | Complexité |
|----------|-------|-----------|
| Ex1 | Insertion, recherche, occurrences, parcours, liste triée, tri par ABR | O(log n) ~ O(n) |
| Ex2 | Vérifier si un arbre est un ABR | O(n) |
| Ex3 | Trouver le plus petit élément | O(h) |

---

## Notions clés

### Notation de Landau (Grand O)
- **O(1)** : temps constant (ex : insertion en tête de liste)
- **O(log n)** : très rapide (ex : recherche dans un ABR équilibré)
- **O(n)** : linéaire (ex : parcourir une liste)
- **O(n log n)** : efficace (ex : tri par ABR)
- **O(n²)** : quadratique (ex : tri à bulles)
- **O(2ⁿ)** : exponentiel — à éviter !

### Structures de données
| Structure | Insertion | Recherche | Suppression |
|-----------|-----------|-----------|-------------|
| Tableau trié | O(n) | O(log n) | O(n) |
| Liste chaînée | O(1) tête | O(n) | O(n) |
| Pile (LIFO) | O(1) | — | O(1) |
| File (FIFO) | O(1) | — | O(1) |
| ABR (équilibré) | O(log n) | O(log n) | O(log n) |
