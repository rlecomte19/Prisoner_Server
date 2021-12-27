# Prisoner Server
> 3ICS - Année 2021/2022 --> Projet scolaire
## Desription
Ce programme correspond à la partie serveur du projet de Programmation C associé au module de **3ICS à CPE Lyon.**

Nous avons décidé avec mes collègues que ce serveur ait la charge de la logique métier, donc des règles du jeu du Dilemme du Prisonnier. En effet, pour des raions de sécurité, le client ne devrait aucunement avoir la main sur les résultats ainsi que sur la gestion de l'avancement des parties par exemple.

## Architecture
L'architecture de la partie est assez basique afin d'aider à la compréhension. En effet, nous avons quatre grandes parties ayant chacunes un rôle bien défini : 
* ***/src/Communication*** : contient la bibliothèque réseau effectuée par les autres membres du projet (permettant la communication client-serveur)
* ***/src/Configuration/*** : contient la gestion du fichier de paramétrage pour le doctorant ainsi que la récupération des données s'y trouvant
* ***/src/Game*** : sûrement la partie la plus importe, elle contient tout ce qui concerne la logique métier, à savoir :
   - la gestion des connexions
   - la gestion des tours de jeu
   - la gestion des parties
* ***/src/Results*** : contient la gestion du stockage des données de façon persistante en fin de phase d'essai du doctorant
* ***/src/Tests*** : contient les tests d'affirmation sur chacune des fonctions de la partie métier du serveur


## Dépendances
Du fait de la diversification de l'architecture précédemment citée, la partie métier dépend de chacune des parties de cette dernière. Il est a noter que la dépendance forte réside en la bibliothèque LibPrisonerNetwork créée par mes collègues lors de ce projet. En effet, c'est elle qui gère tout ce qui concerne le "threading" ainsi que l'échange de paquets entre le client et le serveur.

## Configuration
Le doctorant se voit fournir un fichier ***config.ini*** dans lequel il devra remplir les informations suivantes : 
* IP du serveur
* Port d'écoute
* Nombre maximal de tours de jeu dans une partie
* Quels joueurs (par leur ID) devront s'affronter au fur et à mesure

Ce fichier sera par la suite lu par le serveur et ses valeurs enregistrées.

**Voici une ébauche de ce dernier :**
```c
# server config file
# any line starting with a # or are blank will be ignored
# the space before and after '=' are mandatory for a correct file reading
# if a settings isn't found, default value will be used

# define the ip the server should listen to
# default: 0.0.0.0 (listen everywhere)
server_ip = 0.0.0.0

# define the server port
# default: 7799
server_port = 7799

# Number of round game
# default: 3
round_number = 3

# Define prisoner's pair
# default: 1,2|3,4
games = 1,2|3,4
```

Il est intéressant de noter les points suivants : 
* _server_ip_ correspond à l'addresse IP du serveur hébergeur
* _server_port_ correspond au port d'écoute de ce dernier
* _round_number_ correspond au nombre maximal de tours de jeu d'une partie
* _games_ indique (par leur id) les clients qui joueront contre

## Utilisation
> Afin de pouvoir utiliser cette application serveur

Récupérer le contenu de ce dépôt Github : 
```bash
git clone https://github.com/rlecomte19/Prisoner_C.git
```
Exécuter le compilateur (le Makefile est déjà configuré et intégré au projet) : 
```bash
make
```
Lancer le binaire récupéré par la commande précédente : 
```bash
./output/main
```
## Stockage des résultats
Ce dernier a été effectué grâce à une structure de données gérant la sauvegarde des réponses à chaque fin de tour de jeu d'une partie et ce, pour chaque partie.

Une fois une partie terminée, les résultats sont stockés dans le fichier : ***./results.csv***.

En voici une ébauche : 
```txt
Rapport généré le;Mon Dec 27 04:31:50 2021

--- INFORMATIONS GÉNÉRALES ---
Nombre de parties:;10


--- GAME #0 ---
Tour de jeu:;0
Tours de jeu prévu:;3

- BINOME -
Id joueur 1;1
Id joueur 2;2

- RESPONSES -
Round #;Joueur 1 (id 1); Joueur 2 (id 2)
0;Aucune réponse;Aucune réponse
1;Aucune réponse;Aucune réponse
2;Aucune réponse;Aucune réponse
3;Aucune réponse;Aucune réponse

--- GAME #1 ---
Tour de jeu:;0
Tours de jeu prévu:;3

- BINOME -
Id joueur 1;3
Id joueur 2;4

- REPONSES -
Round #;Joueur 1 (id 3); Joueur 2 (id 4)
0;Trahison;Collaboration
1;Aucune réponse;Aucune réponse
2;Aucune réponse;Aucune réponse
3;Aucune réponse;Aucune réponse

--- GAME #2 ---
Tour de jeu:;0
Tour de jeu prévu:;3

- BINOME -
Id joueur 1;-1
Id joueur 2;-1

- REPONSES -
Round #;Joueur 1 (id -1); Joueur 2 (id -1)
0;Aucune réponse;Aucune réponse
1;Aucune réponse;Aucune réponse
2;Aucune réponse;Aucune réponse
3;Aucune réponse;Aucune réponse

--- GAME #3 ---
Tour de jeu:;0
Tour de jeu prévu:;3

- BINOME -
Id joueur 1;-1
Id joueur 2;-1

- RESPONSES -
Round #;Joueur 1 (id -1); Joueur 2 (id -1)
0;Aucune réponse;Aucune réponse
1;Aucune réponse;Aucune réponse
2;Aucune réponse;Aucune réponse
3;Aucune réponse;Aucune réponse

```
Du fait de son extension CSV et de la gestion des colonnes faite en amont, il est possible d'exporter ce dernier en tant qu'Excel par exemple afin d'en améliorer la lisibilité.

## Documentation
Ayant utilisé Doxygen dans un but d'accroissement de la visiblité, il existe la possibilité d'exécuter la commande : 
```bash
make documentation
```
Cela génèrera une documentation conernant toutes les fonctions, dépendances, strucutres de données, etc.. de l'application. 

Vous pourrez par la suite la visualiser grâce aux fichiers ***html*** générés. Le point d'entrée de cette documentation est :  ***/doxygen/html/index.html***.

> Amusez vous bien ! 

