<?php
// Connexion à la base
include('db_connect.php');

// Récupère les limites définies (ex. amplitude, fréquence)
$sql = "SELECT * FROM limites WHERE id = 1";
$stmt = $pdo->prepare($sql);
$stmt->execute();
$limites = $stmt->fetch(PDO::FETCH_ASSOC);

if (!$limites) {
    die("Aucune limite trouvée.");
}

// Vérifie qu’un ID de test est passé en paramètre
if (isset($_GET['id_test']) && is_numeric($_GET['id_test'])) {
    $id_test = intval($_GET['id_test']);

    // Récupère les données du test concerné
    $sql = "SELECT id_test, valeur1, valeur2, valeur3, valeur4, valeur5, status 
            FROM ouvrier WHERE id_test = ?";
    $stmt = $pdo->prepare($sql);
    $stmt->bindParam(1, $id_test, PDO::PARAM_INT);
    $stmt->execute();
    $row = $stmt->fetch(PDO::FETCH_ASSOC);

    if (!$row) {
        die("Aucun test trouvé pour cet ID.");
    }
} else {
    die("Aucun ID de test spécifié.");
}
?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Détails du Test</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
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
        .content {
            padding: 20px;
            max-width: 800px;
            margin: auto;
        }
        .limits {
            display: inline-block;
            padding-left: 20px;
            color: gray;
        }
    </style>
</head>
<body>
    <header>
        <h1>Détails du Test n°<?php echo htmlspecialchars($row['id_test']); ?></h1>
        <nav>
            <a href="index.php">Accueil</a>
            <a href="historique_ouvrier.php">Historique Ouvrier</a>
            <a href="historique_tech.php">Historique Technicien</a>
            <a href="limites.php">Limites</a>
        </nav>
    </header>

    <div class="content">
        <h2>Informations sur le Test</h2>
        <p><strong>ID test :</strong> <?php echo htmlspecialchars($row['id_test']); ?></p>

        <p>
            <strong>Valeur Mesurée 1 :</strong> <?php echo htmlspecialchars($row['valeur1']); ?>
            <span class="limits">Amplitude_min : <?php echo htmlspecialchars($limites['Amplitude_min'] ?? '–'); ?></span>
        </p>
        <p>
            <strong>Valeur Mesurée 2 :</strong> <?php echo htmlspecialchars($row['valeur2']); ?>
            <span class="limits">Amplitude_max : <?php echo htmlspecialchars($limites['Amplitude_max'] ?? '–'); ?></span>
        </p>
        <p>
            <strong>Valeur Mesurée 3 :</strong> <?php echo htmlspecialchars($row['valeur3']); ?>
            <span class="limits">Fréquence_Inférieur : <?php echo htmlspecialchars($limites['Fréquence_Inférieur'] ?? '–'); ?></span>
        </p>
        <p>
            <strong>Valeur Mesurée 4 :</strong> <?php echo htmlspecialchars($row['valeur4']); ?>
            <span class="limits">Fréquence_Supérieur : <?php echo htmlspecialchars($limites['Fréquence_supérieur'] ?? '–'); ?></span>
        </p>
        <p>
            <strong>Valeur Mesurée 5 :</strong> <?php echo htmlspecialchars($row['valeur5']); ?>
        </p>
        <p>
            <strong>Status :</strong> <?php echo htmlspecialchars($row['status']); ?>
        </p>
    </div>
</body>
</html>
