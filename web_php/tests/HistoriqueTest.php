<?php
use PHPUnit\Framework\TestCase;

class HistoriqueTest extends TestCase
{
    private $pdo;

    protected function setUp()
    {
        // Charger l'autoload de Composer
        require_once __DIR__ . '/../vendor/autoload.php';
    
        // Vérifier si le fichier .env existe
        if (!file_exists(__DIR__ . '/../.env')) {
            die("❌ Erreur : Le fichier .env est introuvable !");
        }
    
        // Charger les variables d'environnement
        $dotenv = Dotenv\Dotenv::createImmutable(__DIR__ . '/..');
        $dotenv->load();
    
        // 🔹 Debug : Voir si `.env` est bien chargé
        echo "Valeurs de \$_ENV :\n";
        print_r($_ENV);
        echo "\nValeurs de \$_SERVER :\n";
        print_r($_SERVER);
        
    
        // Vérifier que les variables sont bien chargées
        if (!isset($_ENV['DB_HOST'], $_ENV['DB_USER'], $_ENV['DB_PASS'], $_ENV['DB_NAME'])) {
            die("❌ Erreur : Les variables d'environnement ne sont pas chargées correctement !");
        }
    
        // Charger la connexion à la base de données
        require_once __DIR__ . '/../db_connect.php';
        $this->pdo = $pdo;
        exit;
    }
    


    public function testDatabaseConnection()
    {
        $this->assertNotNull($this->pdo, "La connexion PDO doit être établie.");
    }

    public function testFetchData()
    {
        $stmt = $this->pdo->query("SELECT COUNT(*) FROM information");
        $count = $stmt->fetchColumn();
        $this->assertGreaterThanOrEqual(0, $count, "Le nombre de tests en base doit être supérieur ou égal à 0.");
    }

    public function testFetchValues()
    {
        $stmt = $this->pdo->query("SELECT id_test FROM information LIMIT 1");
        $result = $stmt->fetch();

        if ($result) {
            $this->assertArrayHasKey('id_test', $result, "La clé 'id_test' doit exister.");
        } else {
            $this->assertEmpty($result, "Aucun test trouvé, mais la requête est valide.");
        }
    }
}
?>
