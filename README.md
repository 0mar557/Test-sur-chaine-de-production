<p align="center">
<h1 align="center">🔧 Test sur chaîne de production 🔬</h1>
<h3 align="center">Automatisation du contrôle qualité en électronique - BTS CIEL 2024/2025 - Lycée Dorian</h3>
</p>

<p align="center">
<a href="https://github.com/0mar557/Test-sur-chaine-de-production/blob/d68c1dc6264e85869d21461591bceec1b387220e/Projet%20CIEL-IR%202025%20%20%E2%80%93%20El%20nmrawy%20Omar%20-%20Da%20Silva%20Anthony%20-%20Jegatheeswaran%20Jenoush%20%E2%80%93%20Test%20sur%20cha%C3%AEne%20de%20production%20%E2%80%93%20Rapport.pdf">📄 Rapport Complet</a> | <a href="https://youtu.be/8ID-ndiZLLg">🎬 Vidéo Démo</a> | <a href="https://github.com/0mar557/Test-sur-chaine-de-production">📂 Code Source</a>
</p>

---

## 🎯 Objectif du projet

Ce projet a pour but d'automatiser les tests qualité en fin de chaîne pour les appareils électroniques. Il combine logiciel (Visual studio Code/Qt), language(C++/PHP/HTML/CSS/javascript), matériel (instruments de mesure), et base de données (MySQL) pour garantir un suivi efficace, rapide et précis des produits testés.

**Avantages clés :**
- Réduction des erreurs humaines.
- Gain de temps considérable.
- Traçabilité complète via base de données.

---

## 🎥 Démonstration

[![Démo du projet](https://img.youtube.com/vi/8ID-ndiZLLg/maxresdefault.jpg)](https://youtu.be/8ID-ndiZLLg)

Cliquez sur l'image pour voir la démo vidéo.

---

## 🚀 Fonctionnalités

- ✅ **Pilotage automatique** : Instruments via bus IEEE-488 (GPIB).
- ✅ **Identification rapide** : Lecture de codes-barres RS232.
- ✅ **Analyse précise** : Seuils configurables stockés dans la base MySQL.
- ✅ **Interface intuitive** : Verdict clair ("Bon/Mauvais").
- ✅ **Archivage sécurisé** : Résultats consultables via une interface web PHP.
- ✅ **Mode avancé technicien** : Gestion approfondie des seuils et analyses détaillées.

---

## 🛠️ Architecture technique

| Composant              | Technologie / Matériel                                            | Rôle                               |
|------------------------|-------------------------------------------------------------------|------------------------------------|
| 🖥️ **Application PC**   | C++ / Qt Creator                                                  | Pilotage instruments, interface    |
| 📡 **Instruments**       | Oscilloscope Rigol MSO5074, Multimètres FI 2348MT, Générateur DG1022Z | Acquisition et mesure des signaux  |
| 🌐 **Serveur Web**      | WAMP (Windows + Apache + MySQL + PHP)                            | Stockage résultats et web          |
| 📊 **Base de données**  | MySQL                                                             | Archivage résultats et seuils      |
| 📟 **Lecteur code-barres** | RS232                                                             | Identification rapide des appareils|

---

## 📦 Installation rapide

### 1. Cloner le dépôt
```bash
git clone https://github.com/0mar557/Test-sur-chaine-de-production.git
cd Test-sur-chaine-production
```

### 2. Installer la base de données
Le fichier SQL se trouve dans `/sql/database_create.sql` :

```bash
mysql -u root -p Projet_Ajo < sql/database_create.sql
```

### 3. Déployer l'interface web
Placez les fichiers PHP dans votre serveur WAMP (`www`).

### 4. Compiler l'application Qt
Ouvrez `/src_cpp` avec Qt Creator, compilez et lancez.

---

## 📬 Contact

Pour toute question ou suggestion, contactez-moi à :  
📧 **omar.elnmrawy@hotmail.com**

---

<h1 align="center">
⭐ Merci de laisser une étoile si ce projet vous a plu ! ⭐
</h1>

<p align="center">
<em>Projet réalisé au Lycée Dorian dans le cadre du BTS CIEL 2024/2025.</em>
</p>
