# Test sur chaîne de production - BTS CIEL 2024/2025

![BTS CIEL](https://img.shields.io/badge/BTS-CIEL-blue) ![Licence MIT](https://img.shields.io/badge/License-MIT-green) ![Lycée Dorian](https://img.shields.io/badge/Lycée-Dorian-red)

---

## 🚀 Présentation

Ce projet automatise le contrôle qualité en fin de chaîne pour des appareils électroniques.  
Il pilote des instruments de mesure (oscilloscope, multimètre, générateur), exécute des tests précis, affiche un verdict clair (bon/mauvais), et archive tous les résultats dans une base de données consultable via une interface web intuitive.

**Objectif :** Gagner du temps, réduire les erreurs humaines, et offrir un suivi fiable et en temps réel des tests industriels.

---

## 🎥 Démo du projet

[![Voir la démo](https://img.youtube.com/vi/8ID-ndiZLLg/maxresdefault.jpg)](https://youtu.be/8ID-ndiZLLg)

Cliquez sur l’image pour regarder la vidéo de démonstration.
---

## 📋 Fonctionnalités principales

- Pilotage automatique des instruments via bus IEEE-488 (GPIB)
- Identification des appareils par lecture de code-barres RS232
- Test automatisé avec analyse selon seuils configurables
- Verdict "Bon" ou "Mauvais" affiché à l’opérateur
- Archivage des résultats dans une base MySQL pour traçabilité complète
- Interface web PHP pour consultation des historiques, statistiques et gestion sécurisée
- Mode technicien avec accès avancé : modification des seuils, visualisation détaillée

---

## 🏗️ Architecture technique

| Composant           | Technologie / Matériel                     | Rôle                                  |
|---------------------|-------------------------------------------|-------------------------------------|
| Banc de mesure      | Oscilloscope Rigol MSO5074, Multimètres FI 2348MT, Générateur Rigol DG1022Z | Acquisition des signaux et mesures  |
| Application PC       | C++ avec Qt Creator                       | Pilotage instruments, interface opérateur |
| Serveur Web          | WAMP (Windows + Apache + MySQL + PHP)    | Stockage des résultats, interface web |
| Lecteur code-barres  | Lecteur RS232                            | Identification des appareils         |

---

## 📦 Installation et déploiement

### Prérequis

- Windows avec WAMP installé
- Qt Creator + compilateur C++ compatible
- Instruments connectés et configurés (oscilloscope, multimètre, générateur)
- Lecteur code-barres connecté en RS232

### Étapes

1. Cloner le dépôt :  
   ```bash
   git clone https://github.com/tonpseudo/Test-sur-chaine-production.git
   cd Test-sur-chaine-production 

2. Installer la base de données : 
  La structure SQL de la base est fournie dans le fichier `database_create.sql` (dans `/sql`).
  Pour créer la base sans données, importez ce fichier dans votre serveur MySQL.  
  Les données de test ne sont pas incluses afin que vous puissiez démarrer avec une base propre.

    ```bash
     mysql -u utilisateur -p nom_de_la_base < database_create.sql

## 📬 Contact
Pour toute question, contactez-moi à :
omar.elnmrawy@example.com

# ⭐ Merci de laisser une étoile ⭐ si ce projet vous a été utile !
