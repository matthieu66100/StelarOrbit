# StelarOrbit 🌌

Une simulation interactive du système solaire en 2D réalisée avec C++ et SFML.

## Description

StelarOrbit est une simulation éducative qui représente le système solaire avec :
- Le Soleil
- Les 8 planètes principales
- Leurs principales lunes
- Des orbites et mouvements proportionnels aux vitesses réelles

## Prérequis

- C++ 17 ou supérieur
- SFML 2.5 ou supérieur
- CMake 3.10 ou supérieur

## Installation

1. Clonez le dépôt :

```bash
git clone https://github.com/votre-username/StelarOrbit.git
cd StelarOrbit
```

2. Créez et accédez au dossier de build :

```bash
mkdir build
cd build
```

3. Compilez le projet :

```bash
cmake ..
make
```

## Lancement

Depuis le dossier `build`, lancez l'exécutable :


```bash
./StelarOrbit
```

## Contrôles

- **Espace** : Mettre en pause / Reprendre la simulation
- **Échap** : Quitter la simulation

## Structure du projet

```
StelarOrbit/
├── include/ # Headers
│ ├── CelestialBody.h # Classe de base pour les corps célestes
│ ├── Star.h # Classe pour le soleil
│ ├── Planet.h # Classe pour les planètes
│ ├── Satellite.h # Classe pour les lunes
│ └── SolarSystem.h # Classe principale de gestion
├── src/ # Implémentations
│ ├── main.cpp
│ ├── CelestialBody.cpp
│ ├── Star.cpp
│ ├── Planet.cpp
│ ├── Satellite.cpp
│ └── SolarSystem.cpp
└── README.md
```

## Licence

Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus de détails.

## Auteur

Basto Matthieu

## Contribution

Les contributions sont les bienvenues ! N'hésitez pas à ouvrir une issue ou à proposer une pull request.