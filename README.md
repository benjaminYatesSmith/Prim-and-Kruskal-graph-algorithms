# Prim and Kruskal Graph Algorithms
Minimal Spanning Tree (MST) — Prim & Kruskal (C)
English
Overview

This project implements algorithms to compute a Minimum Spanning Tree (MST) of a weighted, undirected graph, inspired by a real-world use case: minimizing the cost of deploying fiber-optic cables while keeping all connection points reachable.

Two classic MST algorithms are implemented:
Kruskal’s algorithm (edge-sorting + Union-Find / Disjoint Set Union)
Prim’s algorithm (incremental growth from a start node, using an efficient data structure)

The work focuses on:
data structures (adjacency lists, edges, priority structures, Union-Find),
robustness (file parsing, error handling),
testing (unit + integration tests),
performance analysis (time and memory complexity in practice vs theory).

Key Concepts
Graphs (vertices, edges, weighted undirected graphs)
Minimum Spanning Tree (MST)
Adjacency list representation
Sorting + Union-Find (Kruskal)
Priority structure / heap (Prim)
Complexity and benchmarking

Repository Structure (typical)
include/ — header files (.h)
src/ — source files (.c) for core modules
test/ or tests/ — unit and integration tests
programs/ (if present) — final executables / main programs
graphes/ or data/ (if present) — small test graphs only (large datasets must not be committed)

Build
This project is intended to be compiled with make (as provided in the course bootstrap).

Typical commands:

make — build the project

make tests@check — run the full test suite (if available in the Makefile)
If your Makefile defines different targets, adapt accordingly.
Run (expected interface)
The final program typically follows the project specification:
acm <graphFile.txt> <0/1> [-v]

Where:
<graphFile.txt> is the graph input file
0 = Kruskal, 1 = Prim
-v (optional) prints the list of edges in the MST
(Exact executable name / options may vary depending on your implementation.)

Input format (graph files)
Graph files use a textual format:
first line: number of vertices and number of edges
vertex section: one line per vertex (id, latitude, longitude, name)
edge section: one line per edge (departure, arrival, cost)
For Prim (undirected graph), each edge may need to be duplicated internally (reverse direction), depending on the provided dataset format.

Notes about large datasets
Some provided graphs can be extremely large (hundreds of MB).
Do not commit large graph files to GitHub. Only keep small test graphs in the repository.

Teamwork & Project Method
This project was completed as a team project (planning, milestones, Git usage, testing strategy).
It also supports the development of Phelma competencies related to:
cooperating in a project team,
designing and delivering robust technical solutions.


Français

Présentation
Ce projet implémente le calcul d’un Arbre Couvrant Minimal (ACM) sur un graphe non orienté et valué, avec une mise en contexte réaliste : minimiser le coût d’installation d’un réseau (ex : fibre optique) tout en connectant tous les points.

Deux algorithmes classiques sont implémentés :
Algorithme de Kruskal (tri des arêtes + Union-Find / ensembles disjoints)
Algorithme de Prim (construction progressive depuis un sommet de départ avec une structure efficace)

Le projet met l’accent sur :
les structures de données (listes d’adjacence, arêtes, tas/structure de priorité, Union-Find),
la robustesse (lecture de fichier, gestion d’erreurs),
les tests (unitaires + intégration),
l’analyse de performance (temps et mémoire : théorie vs expérimentation).

Notions clés
Graphes (sommets, arêtes, graphes valués non orientés)
Arbre couvrant minimal (ACM)
Représentation en liste d’adjacence
Tri + Union-Find (Kruskal)
Tas / structure de priorité (Prim)
Complexité et mesures de performance

Structure du dépôt (typique)
include/ — fichiers d’en-tête (.h)
src/ — fichiers sources (.c) des modules
test/ ou tests/ — tests unitaires et d’intégration
programs/ (si présent) — programmes finaux / main
graphes/ ou data/ (si présent) — uniquement petits graphes de test (jamais les gros fichiers)

Compilation
Le projet est conçu pour être compilé avec make (bootstrap du module).

Commandes typiques :
make — compiler le projet
make tests@check — exécuter tous les tests (si disponible dans le Makefile)

Selon votre Makefile, les cibles peuvent varier.
Exécution (interface attendue)
Le programme final suit généralement la spécification du sujet :
acm <nomFichierGraphe.txt> <0/1> [-v]
Avec :
<nomFichierGraphe.txt> : fichier contenant le graphe
0 = Kruskal, 1 = Prim
-v (optionnel) : affiche la liste des arêtes de l’ACM
(Le nom exact de l’exécutable et les options peuvent varier selon l’implémentation.)

Format des fichiers d’entrée
Format texte :
ligne 1 : nombre de sommets et nombre d’arêtes
section sommets : une ligne par sommet (id, latitude, longitude, nom)
section arêtes : une ligne par arête (départ, arrivée, coût)
Pour Prim (graphe non orienté), il peut être nécessaire de créer un arc inverse en mémoire selon le format fourni.

Attention aux gros fichiers
Certains graphes réels fournis sont très volumineux (plusieurs centaines de Mo).
Il ne faut jamais les ajouter au dépôt Git (add/commit/push). Conserver uniquement des graphes simples pour les tests.

Travail en équipe & gestion de projet
Projet réalisé en équipe avec une logique de jalons, suivi, commits réguliers, et stratégie de tests.

Il contribue notamment aux compétences Phelma :
coopération en équipe / mode projet,
conception et livraison d’une solution technique robuste et réutilisable.
