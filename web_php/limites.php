<?php
// Inclure le fichier de connexion
include('db_connect.php');

// Récupérer les limites actuelles depuis la base de données
$sql = "SELECT Amplitude_min,Amplitude_max,Fréquence_Inférieur,Fréquence_Supérieur
        FROM limites WHERE id = 1";
$stmt = $pdo->prepare($sql);
$stmt->execute();
$limites = $stmt->fetch(PDO::FETCH_ASSOC);

if (!$limites) {
    die("Aucune limite trouvée.");
}

// Définir les valeurs par défaut si aucune limite n'est trouvée dans la base
$Amplitude_min = $limites['Amplitude_min'] ?? 5;
$Amplitude_max = $limites['Amplitude_max'] ?? 10;
$Fréquence_Inférieur = $limites['Fréquence_Inférieur'] ?? 100;
$Fréquence_Supérieur = $limites['Fréquence_Supérieur'] ?? 10000;

// Initialiser le message d'erreur ou de succès
$message = '';

// Si le formulaire est soumis, mettre à jour les limites dans la base
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $action = $_POST['action'];

    if ($action === 'update') {
        // Récupérer les nouvelles limites depuis le formulaire
        $limite_superieure_1 = floatval($_POST['Amplitude_min']);
        $limite_inferieure_1 = floatval($_POST['Amplitude_max']);
        $Fréquence_Inférieur = floatval($_POST['Fréquence_Inférieur']);
        $Fréquence_Supérieur = floatval($_POST['Fréquence_Supérieur']);

        // Mettre à jour les limites dans la base de données
        $update_sql = "UPDATE limites SET 
                    Amplitude_min = ?, Amplitude_max = ?,
                    Fréquence_Inférieur = ?, Fréquence_Supérieur = ?
                    WHERE id = 1";
        $stmt = $pdo->prepare($update_sql);
        $stmt->execute([
            $Amplitude_min, $Amplitude_max,
            $Fréquence_Inférieur, $Fréquence_Supérieur,

        ]);

        $message = "<p style='color: green;'>Limites mises à jour avec succès !</p>";
    }
    elseif ($action === 'default') {
        // Réinitialiser les limites à leurs valeurs par défaut
        $Amplitude_min = 5;
        $Amplitude_max = 20;
        $Fréquence_Inférieur = 100;
        $Fréquence_Supérieur = 10000;

        // Mettre à jour les limites par défaut dans la base de données
        $update_sql = "UPDATE limites SET 
                    Amplitude_min = ?, Amplitude_max = ?,
                    Fréquence_Inférieur = ?, Fréquence_Supérieur = ?
                    WHERE id = 1";
        $stmt = $pdo->prepare($update_sql);
        $stmt->execute([
            $Amplitude_min, $Amplitude_max,
            $Fréquence_Inférieur, $Fréquence_Supérieur,
        ]);

        $message = "<p style='color: green;'>Limites réinitialisées aux valeurs par défaut.</p>";
    }
}
?>

<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Modifier les Limites</title>
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
        .form-container {
            display: flex;
            flex-direction: column;
            align-items: center; 
        }

        .form-container label {
            margin-bottom: 10px;
            font-weight: bold;
        }

        .form-container .input-group {
            display: flex;
            margin-bottom: 15px;
            justify-content: space-between;
        }

        .form-container .input-group input {
            width: 15%;
            padding: 8px;
            margin-bottom: 15px;
            border: 1px solid #ccc;
            border-radius: 4px;
        }

        .form-container button {
            padding: 10px 15px;
            background-color: #007BFF;
            color: white;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }

        .form-container button:hover {
            background-color: #0056b3;
        }

    </style>
</head>
<body>
    <header>    
    <h1 style="text-align: center;">Modification des Limites</h1>
    <nav>
            <a href="index.php">Accueil</a>
            <a href="historique_ouvrier.php">Historique Ouvrier</a>
            <a href="historique_tech.php">Historique Technicien</a>
            <a href="limites.php">Limites</a>
        </nav>
    </header>
    <!-- Formulaire pour modifier les limites -->
    <div class="form-container">
    <h3>Modifier les Limites</h3>
    <form method="post">
        <div class="input-group">
            <label for="Amplitude_min">Amplitude min</label>
            <input type="number" step="0.01" name="Amplitude_min" value="<?php echo $Amplitude_min; ?>" required>
            <label for="Amplitude_max">Amplitude max</label>
            <input type="number" step="0.01" name="Amplitude_max" value="<?php echo $Amplitude_max; ?>" required>
        </div>

        <!-- Limites Inférieures et Supérieures 2 -->
        <div class="input-group">
            <label for="Fréquence_Inférieur">Fréquence Inférieur</label>
            <input type="number" step="0.01" name="Fréquence_Inférieur" value="<?php echo $Fréquence_Inférieur; ?>" required>
            <label for="Fréquence_Supérieur">Fréquence Supérieur</label>
            <input type="number" step="0.01" name="Fréquence_Supérieur" value="<?php echo $Fréquence_Supérieur; ?>" required>
        </div>

        <button type="submit" name="action" value="update">Mettre à jour</button>
        <button type="submit" name="action" value="default">Réinitialiser aux valeurs par défaut</button>
        <?php if (!empty($message)) echo $message; ?>
    </form>
</div>

</body>
</html>
