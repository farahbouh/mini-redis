<div align="center">

# mini-redis

**Serveur clé-valeur TCP multithread, écrit en C++**

![Status](https://img.shields.io/badge/status-fonctionnel-brightgreen)
![Dernière mise à jour](https://img.shields.io/github/last-commit/farahbouh/mini-redis?label=derni%C3%A8re%20mise%20%C3%A0%20jour)
![C++](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=c%2B%2B&logoColor=white)
![Linux](https://img.shields.io/badge/plateforme-Linux-FCC624?logo=linux&logoColor=black)

[Installation](#mise-en-place) · [Tests](#tests) · [Signaler un bug](../../issues)

</div>

---

## Pourquoi ce projet ?

Projet personnel : comprendre comment fonctionne un serveur TCP multi-clients en C++,
en réimplémentant un mini Redis - un stockage clé-valeur en mémoire, accessible via
un protocole texte simple.

---

## Stack technique

| | |
|---|---|
| **Langage** | C++17 |
| **Réseau** | Sockets POSIX (`socket`, `bind`, `listen`, `accept`, `recv`, `send`) |
| **Concurrence** | `std::thread` (un thread par client), `std::atomic<bool>`, `std::mutex` |
| **Build** | `g++` via `Makefile` |
| **Tests** | Tests unitaires C++ (`tests/`) |
| **Test manuel** | `nc` (netcat) |

---

## Fonctionnalités

- Écoute sur un port TCP (8080 par défaut)
- Accepte **plusieurs clients simultanément** (un thread par connexion)
- Protocole texte : `SET clé valeur`, `GET clé`, `DEL clé`
- Stockage clé-valeur **partagé** entre tous les clients, protégé par un mutex
- Réponses : `OK`, la valeur, ou `ERREUR ...`

---

## Mise en place

Il vous faut un compilateur C++17 (`g++`), `make`, et `netcat` pour tester.

```bash
git clone https://github.com/farahbouh/mini-redis
cd mini-redis
make
./mini-redis
```

Le serveur écoute sur le port 8080.

### Test rapide

Dans un autre terminal :

```bash
nc localhost 8080
SET a 1
GET a
```

Réponse attendue : `OK` puis `1`.

Ouvrez un **second** terminal `nc localhost 8080` : les deux sessions partagent
le même stockage (un `SET` dans l'un est visible par l'autre).

### Exemple de session

```bash
$ nc localhost 8080
SET pat pa
OK
GET pat
pa
DEL pat
OK
GET pat
ERREUR cle inconnue
```

---

## Tests

```bash
make test
```

Trois suites de tests unitaires couvrent le stockage, l'analyseur de protocole
et le serveur :

| Fichier | Ce qu'il teste |
|---|---|
| `tests/store_test.cpp` | `Stockage` : `mettre`, `recuperer`, `supprimer` |
| `tests/analyseur_test.cpp` | `Analyseur` : découpage, validation des commandes |
| `tests/serveur_test.cpp` | `Serveur` : exécution des commandes de bout en bout |

---

<details>
<summary>Structure du projet</summary>

```bash
.
├── data
├── src
│   ├── client
│   ├── protocole
│   ├── serveur
│   ├── stockage
│   └── main.cpp
├── tests
│   ├── analyseur_test.cpp
│   ├── serveur_test.cpp
│   └── store_test.cpp
├── Makefile
└── README.md
```

</details>

---

## Ce que ce projet m'a appris

- Programmer des sockets TCP côté serveur (cycle `socket` -> `bind` -> `listen` -> `accept`)
- Gérer plusieurs clients en parallèle avec `std::thread`
- Protéger une structure de données partagée avec `std::mutex` (thread-safety)
- Utiliser `std::atomic` pour un flag lu par plusieurs threads
- Séparer les responsabilités : réseau (`Serveur`), protocole (`Analyseur`), données (`Stockage`)
- Écrire des tests unitaires pour du code C++
- Organiser un projet C++ avec un `Makefile` (cibles `all`, `test`, `clean`)

---
## Contribuer

Les idées et retours sont les bienvenus : n'hésitez pas à ouvrir un [ticket](../../issues).

---
<div align="center">

Réalisé par [Farah](https://github.com/farahbouh) 

Contact : [LinkedIn](https://www.linkedin.com/in/farahbouh) · [Email](mailto:farah.bouhnaida@gmail.com)

</div>
