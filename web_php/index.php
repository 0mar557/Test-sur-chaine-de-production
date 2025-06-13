<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Accueil - Projet Banc de Production</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            text-align: center;
        }
        header {
            background-color: #007BFF;
            color: white;
            padding: 15px 20px;
            display: flex;
            justify-content: space-between;
            align-items: center;
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1);
        }
        header nav a {
            color: white;
            text-decoration: none;
            font-size: 16px;
            margin-left: 15px;
        }
        header nav a:hover {
            text-decoration: underline;
        }
        #tit{
            margin-top: 50px;
        }
    </style>
</head>
<body>
    <!-- En-tête -->
    <header>
        <h1>Accueil</h1>
        <nav>
            <a href="index.php">Accueil</a>
            <a href="historique_ouvrier.php">Historique Ouvrier</a>
            <a href="historique_tech.php">Historique Technicien</a>
            <a href="limites.php">Limites</a>
        </nav>
    </header>

    <!-- Contenu principal -->
    <h1 id="tit">Bienvenue sur le Projet Banc de Production</h1>
    <p>Ce projet permet de gérer les tests et de suivre leur historique.</p>
</body>
</html>
