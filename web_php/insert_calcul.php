<?php
// Inclure le fichier de connexion
include('db_connect.php');

// Récupérer les limites actuelles depuis la base de données
$sql = "SELECT * FROM limites WHERE id = 1";
$stmt = $pdo->prepare($sql);
$stmt->execute();
$limites = $stmt->fetch(PDO::FETCH_ASSOC);

if (!$limites) {
    die("Aucune limite trouvée.");
}

// Simuler des valeurs mesurées (normalement, elles viendraient de l'utilisateur ou d'un capteur)
$id_appareil = 1; // ID de l'appareil qui effectue le test
$valeur_mesure_1 = rand(-20, 20); // Simulation de valeurs aléatoires
$valeur_mesure_2 = rand(-20, 20);
$valeur_mesure_3 = rand(-20, 20);
$valeur_mesure_4 = rand(-20, 20);
$valeur_mesure_5 = rand(-20, 20);

// Comparer chaque valeur avec ses limites et attribuer le statut correspondant
$status_1 = ($valeur_mesure_1 >= $limites['limite_valeur_inferieure_1'] && $valeur_mesure_1 <= $limites['limite_valeur_superieure_1']) ? 'Reussi' : 'Rate';
$status_2 = ($valeur_mesure_2 >= $limites['limite_valeur_inferieure_2'] && $valeur_mesure_2 <= $limites['limite_valeur_superieure_2']) ? 'Reussi' : 'Rate';
$status_3 = ($valeur_mesure_3 >= $limites['limite_valeur_inferieure_3'] && $valeur_mesure_3 <= $limites['limite_valeur_superieure_3']) ? 'Reussi' : 'Rate';
$status_4 = ($valeur_mesure_4 >= $limites['limite_valeur_inferieure_4'] && $valeur_mesure_4 <= $limites['limite_valeur_superieure_4']) ? 'Reussi' : 'Rate';
$status_5 = ($valeur_mesure_5 >= $limites['limite_valeur_inferieure_5'] && $valeur_mesure_5 <= $limites['limite_valeur_superieure_5']) ? 'Reussi' : 'Rate';

// Déterminer si tous les tests sont "Reussi"
$status_global = ($status_1 == 'Reussi' && $status_2 == 'Reussi' && $status_3 == 'Reussi' && $status_4 == 'Reussi' && $status_5 == 'Reussi') ? 'Reussi' : 'Rate';

// Insérer les valeurs et leur statut global dans la base de données
$sql_insert = "INSERT INTO information (id_appareil, valeur_mesure_1, valeur_mesure_2, valeur_mesure_3, valeur_mesure_4, valeur_mesure_5, 
                                        status, date_test, time_test) 
               VALUES (?, ?, ?, ?, ?, ?, ?, CURRENT_DATE(), CURRENT_TIME())";

$stmt = $pdo->prepare($sql_insert);

if (!$stmt) {
    die("Erreur dans la préparation de la requête : " . $pdo->errorInfo()[2]);
}

// Exécution de la requête avec les valeurs mesurées et leur statut global
$stmt->execute([
    $id_appareil, 
    $valeur_mesure_1, $valeur_mesure_2, $valeur_mesure_3, $valeur_mesure_4, $valeur_mesure_5, 
    $status_global
]);

echo "Valeurs insérées avec succès.";
?>
