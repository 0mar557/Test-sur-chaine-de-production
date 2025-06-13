<?php
// Inclure la connexion PDO
include('db_connect.php');
// Requête pour compter les réussites et les échecs
$sql_stats = "
    SELECT 
      SUM(CASE WHEN status = 'reussi' THEN 1 ELSE 0 END) AS nb_reussite,
      SUM(CASE WHEN status = 'raté'   THEN 1 ELSE 0 END) AS nb_echec
    FROM ouvrier
";
try {
    $stmt_stats = $pdo->prepare($sql_stats);
    $stmt_stats->execute();
    $stats = $stmt_stats->fetch(PDO::FETCH_ASSOC);
    // Si vos statuts sont différents (ex. 'success' / 'failure'), adaptez les chaînes ci-dessous.
    $nbReussite = $stats['nb_reussite'];
    $nbEchec    = $stats['nb_echec'];
} catch (PDOException $e) {
    die("Erreur SQL (stats) : " . $e->getMessage());
}
// Récupérer les tests depuis la base de données
$sql = "SELECT id_test, valeur1, valeur2, valeur3, valeur4, valeur5, status 
        FROM ouvrier ";
try {
    $stmt = $pdo->prepare($sql);
    $stmt->execute();
    $result = $stmt->fetchAll(); // Récupération des résultats sous forme de tableau
} catch (PDOException $e) {
    die("Erreur SQL : " . $e->getMessage());
}
?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Historique des Tests</title>
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
        .accordion { 
            margin: 20px auto; 
            width: 90%; 
            max-width: 600px; 
        }
        .accordion-item { 
            background-color: #fff; 
            margin-bottom: 10px; 
            border-radius: 5px; 
            box-shadow: 0 2px 5px rgba(0, 0, 0, 0.1); 
            overflow: hidden; 
        }
        .accordion-header { 
            padding: 15px; 
            display: flex; 
            justify-content: space-between; 
            align-items: center; 
            background-color: #007BFF; 
            color: white; 
            cursor: pointer; 
        }
        .accordion-header:hover { 
            background-color: #0056b3; 
        }
        .accordion-body { 
            display: none; 
            padding: 15px; 
            border-top: 1px solid #ddd; 
            background-color: #f4f4f4; 
        }
        .details-button { 
            padding: 5px 10px; 
            background-color: #007BFF; 
            color: white; 
            text-decoration: none; 
            border-radius: 5px; 
            font-size: 14px; 
            border: none; 
            cursor: pointer; 
        }
        .details-button:hover { 
            background-color: #0056b3; 
        }
        .stats-header {
    padding: 10px 20px;
    background-color: #f1f1f1;
    color: #333;
    font-size: 16px;
    display: flex;
    gap: 20px;
    align-items: center;
}
.stats-header span {
    font-weight: bold;
}

    </style>
</head>
<body>
    <header>
        <h1>Historique des Tests Mode Ouvrier</h1>
        <nav>
            <a href="index.php">Accueil</a>
            <a href="historique_ouvrier.php">Historique Ouvrier</a>
            <a href="historique_tech.php">Historique Technicien</a>
            <a href="limites.php">Limites</a>
        </nav>
        <!-- Nouveau : statistiques -->
    <div class="stats-header">
        <span>✅ Réussites : <?php echo $nbReussite; ?></span>
        <span>❌ Échecs : <?php echo $nbEchec; ?></span>
    </div>
    </header>

    <div class="accordion">
        <?php if (!empty($result)): ?>
            <?php foreach ($result as $row): ?>
                <div class="accordion-item">
                    <div class="accordion-header" onclick="toggleAccordion(this)">
                        <span>Test n°<?php echo htmlspecialchars($row['id_test']); ?></span>
                    </div>
                    <div class="accordion-body">
                        <p><strong>Valeurs Mesurées :</strong></p>
                        <ul>
                            <li>Valeur mesure 1 : <?php echo htmlspecialchars($row['valeur1']); ?></li>
                            <li>Valeur mesure 2 : <?php echo htmlspecialchars($row['valeur2']); ?></li>
                            <li>Valeur mesure 3 : <?php echo htmlspecialchars($row['valeur3']); ?></li>
                            <li>Valeur mesure 4 : <?php echo htmlspecialchars($row['valeur4']); ?></li>
                            <li>Valeur mesure 5 : <?php echo htmlspecialchars($row['valeur5']); ?></li>
                        </ul>
                        <p><strong>Status :</strong> <?php echo htmlspecialchars($row['status']); ?></p>
                        <a href="detail_ouvrier.php?id_test=<?php echo urlencode($row['id_test']); ?>" class="details-button">Voir Détails</a>
                    </div>
                </div>
            <?php endforeach; ?>
        <?php else: ?>
            <p>Aucun test trouvé.</p>
        <?php endif; ?>
    </div>

    <script>
        function toggleAccordion(element) {
            const body = element.nextElementSibling;
            const allBodies = document.querySelectorAll('.accordion-body');
            allBodies.forEach(b => { if (b !== body) b.style.display = 'none'; });
            body.style.display = (body.style.display === 'block') ? 'none' : 'block';
        }
    </script>
</body>
</html>
