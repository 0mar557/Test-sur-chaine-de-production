// mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QThread>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    progressValue(0)// Anthony, Omar
{
    ui->setupUi(this);

    // --- config du port série ---
    serial.setPortName("COM5");
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
    if (serial.open(QIODevice::ReadOnly)) {
        connect(&serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    } else {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir le port série !");
    }

    // timer de progression
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateProgressBar);

    // bouton de lancement
    connect(ui->pushButtonTest, &QPushButton::clicked,
            this, &MainWindow::startTest);

    // on prépare la connexion BDD (host, user…) — détails à adapter si nécessaire
    connectToDatabase();
}

MainWindow::~MainWindow()// Anthony

{
    serial.close();
    if (db.isOpen()) db.close();
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event) // Anthony
{
    if (event->key() == Qt::Key_F10)
    {
        DialogLogin dlg;
        dlg.setDialogTech(&tech);
        dlg.exec();
    }
}

void MainWindow::readData() // Anthony, Omar
{
    qDebug() << "Données reçues";
    static QByteArray buffer;
    buffer += serial.readAll();

    if (buffer.endsWith('\n') || buffer.endsWith('\r')) {
        QString barcode = QString::fromUtf8(buffer).trimmed();
        buffer.clear();

        ui->lineEditBarcode->setText(barcode);
        QSqlQuery query;
        query.prepare("SELECT * FROM appareils WHERE code_barres = ?");
        query.addBindValue(barcode);
        if (query.exec() && query.next()) {
            ui->textEditInfo->setText(query.value("info").toString());
        } else {
            ui->textEditInfo->setText("Code non trouvé.");
        }
    }
}

bool MainWindow::checkVoltage()// Jenoush, Anthony
{
    ViSession defaultRM, vi[3];
    char buf[3][256] = {{0}};
    QString instruments[3] = {
        "USB0::0xF4EC::0xEE38::NDM35FAD2R0189::0::INSTR",
        "USB0::0xF4EC::0xEE38::NDM35FAD2R0210::0::INSTR",
        "USB0::0x1AB1::0x0642::DG1ZA231001077::0::INSTR"
    };

    QString commandsForThirdInstrument[5] = {
        ":APPL:SIN 10HZ, 500mVPP, 0V\n",
        ":APPL:SIN 100HZ, 500mVPP, 0V\n",
        ":APPL:SIN 1KHZ, 500mVPP, 0V\n",
        ":APPL:SIN 10KHZ, 500mVPP, 0V\n",
        ":APPL:SIN 100KHZ, 500mVPP, 0V\n"
    };

    m_veValues.clear();
    m_vsValues.clear();
    m_freqValues.clear();
    m_gainValues.clear();  // <--- on vide les gains précédents

    qDebug() << "[checkVoltage] Ouverture session VISA...";
    if (viOpenDefaultRM(&defaultRM) != VI_SUCCESS) {
        qDebug() << "[checkVoltage] Échec ouverture session VISA";
        return false;
    }

    qDebug() << "[checkVoltage] Connexion aux instruments...";
    for (int i = 0; i < 3; ++i) {
        if (viOpen(defaultRM,
                   instruments[i].toUtf8().constData(),
                   VI_NULL, VI_NULL, &vi[i]) != VI_SUCCESS) {
            qDebug() << QString("[checkVoltage] Échec ouverture instrument %1")
                        .arg(i + 1);
            for (int j = 0; j < i; ++j) viClose(vi[j]);
            viClose(defaultRM);
            return false;
        }
    }

    for (int cycle = 0; cycle < 5; ++cycle) {
        qDebug() << QString("-------- Test cycle %1 --------").arg(cycle + 1);

        // on génère le signal sine
        if (viPrintf(vi[2], commandsForThirdInstrument[cycle].toUtf8().constData()) != VI_SUCCESS ||
            viPrintf(vi[2], "OUTP1:STAT ON\n") != VI_SUCCESS) {
            qDebug() << "[checkVoltage] Erreur envoi commande";
            for (int i = 0; i < 3; ++i) viClose(vi[i]);
            viClose(defaultRM);
            return false;
        }

        QThread::msleep(300);

        for (int i = 0; i < 3; ++i) {
            QThread::msleep(500);
            memset(buf[i], 0, sizeof(buf[i]));
            bool success = false;
            int tryCount = 0;

            // À placer dans le for (int i = 0; i < 3; ++i) juste après le QThread::msleep(500) et avant le test de success :
            while (!success && tryCount < 2) {
                ViStatus viStatus;
                switch (i) {
                case 0:
                    // Multimètre Ve
                    viPrintf(vi[0], ":CONF:VOLT:AC\n");
                    QThread::msleep(300);
                    viPrintf(vi[0], ":MEAS:VOLT:AC?\n");
                    viFlush(vi[0], VI_READ_BUF);
                    QThread::msleep(500);
                    viStatus = viScanf(vi[0], "%s", buf[0]);
                    break;

                case 1:
                    // Multimètre Vs
                    viPrintf(vi[1], ":CONF:VOLT:AC\n");
                    QThread::msleep(300);
                    viPrintf(vi[1], ":MEAS:VOLT:AC?\n");
                    viFlush(vi[1], VI_READ_BUF);
                    QThread::msleep(500);
                    viStatus = viScanf(vi[1], "%s", buf[1]);
                    break;

                case 2:
                    // Générateur → lecture fréquence
                    viPrintf(vi[2], ":FREQ?\n");
                    QThread::msleep(300);
                    viStatus = viScanf(vi[2], "%s", buf[2]);
                    break;
                }

                if (viStatus == VI_SUCCESS) {
                    success = true;
                } else {
                    ++tryCount;
                    QThread::msleep(300);
                }
            }

            if (!success) {
                qDebug() << QString("[checkVoltage] Erreur lecture instrument %1").arg(i + 1);
                for (int j = 0; j < 3; ++j) viClose(vi[j]);
                viClose(defaultRM);
                return false;
            }

        }

        // conversion en double
        double ve = QString(buf[0]).toDouble();
        double vs = QString(buf[1]).toDouble();
        double freq = QString(buf[2]).toDouble();

        m_veValues.append(ve);
        m_vsValues.append(vs);
        m_freqValues.append(freq);

        // calcul du gain en dB
        double gain = 0.0;
        if (ve != 0.0) {
            gain = 20.0 * log10(fabs(vs) / fabs(ve));
        }
        m_gainValues.append(gain);  // <--- on stocke

        QString sGain = QString::number(gain, 'f', 2);
        qDebug() << QString("[Cycle %1] Ve=%2 V | Vs=%3 V | F=%4 Hz | Gain=%5 dB")
                    .arg(cycle+1)
                    .arg(ve, 0, 'f', 8)
                    .arg(vs, 0, 'f', 8)
                    .arg(freq, 0, 'f', 0)
                    .arg(sGain);

        ui->textEditInfo->append(
            QString("Cycle %1\n→ Entrée : %2 V\n→ Sortie : %3 V\n→ Fréquence : %4 Hz\n→ Gain : %5 dB\n")
                .arg(cycle + 1)
                .arg(ve, 0, 'f', 8)
                .arg(vs, 0, 'f', 8)
                .arg(freq, 0, 'f', 0)
                .arg(sGain)
        );
    }

    qDebug() << "[checkVoltage] Fin des cycles.";
    for (int i = 0; i < 3; ++i) viClose(vi[i]);
    viClose(defaultRM);
    return true;
}

bool MainWindow::checkBarcodeScanned()// Anthony
{
    return !ui->lineEditBarcode->text().isEmpty();
}

void MainWindow::startTest()// Anthony
{
    ui->textEditInstructions->setText("Vérification de la connexion...");

    // 1) Vérification du code-barres
    if (!checkBarcodeScanned()) {
        ui->textEditInstructions->append("Erreur : Aucun code-barres scanné !");
        return;
    }

    // 2) Mesure des tensions
    if (!checkVoltage()) {
        ui->textEditInstructions->append("Erreur : test de tension échoué !");
        return;
    }

    // 3) Calcul des gabarits, comparaison, affichage du résultat et enregistrement
    gabaritcalcule();

    // 4) Lancement de la barre de progression
    progressValue = 0;
    ui->progressBar->setValue(progressValue);
    timer->start(100);
}

void MainWindow::gabaritcalcule()// Anthony, Jenoush
{
    const int ID_LIMITES = 1;  // adaptez si besoin

    // 1) Charger les limites (Amplitude_min = gain_min, Amplitude_max = gain_max)
    if (!loadLimits(ID_LIMITES)) {
        QMessageBox::warning(this, "Limites", "Impossible de charger les limites !");
        return;
    }

    // 2) Comparer chaque gain calculé aux bornes
    bool passe = true;
    for (double g : m_gainValues) {
        if (g < Amp_min || g > Amp_max) {
            passe = false;
            break;
        }
    }

    // 3) Mettre à jour le résultat à l'écran
    QString status = passe ? "Réussi" : "Raté";
    ui->lineEditResultat->setText(status);

    // 4) Enregistrer en base le code-barres + tous les gains + idLimites + status
    const QString codebar = ui->lineEditBarcode->text().trimmed();
    saveResults(codebar, m_gainValues, ID_LIMITES, status);
}

void MainWindow::updateProgressBar() // Anthony
{
    progressValue += 1;
    ui->progressBar->setValue(progressValue);
    if (progressValue >= 100) {
        timer->stop();
        ui->textEditInstructions->append("2: Test terminé");
        ui->textEditInstructions->append("3: Débranchez");
    }
}

// --- CHARGEMENT DES LIMITES ---
bool MainWindow::loadLimits(int idLimites)// Omar
{
    if (!db.isOpen()) {
        qWarning() << "[DB] Connexion fermée, tentative de reconnexion...";
        connectToDatabase();
        if (!db.isOpen()) {
            qWarning() << "[DB] Échec de reconnexion.";
            return false;
        }
    }

    QSqlQuery query(db);
    QString sql = QStringLiteral(R"(
        SELECT
            Amplitude_min,
            Amplitude_max
        FROM limites
        WHERE id = %1
    )").arg(idLimites);

    if (!query.exec(sql)) {
        qWarning() << "[SQL] Erreur requête SELECT :" << query.lastError().text();
        return false;
    }
    if (!query.next()) {
        qWarning() << "[SQL] Aucune ligne trouvée avec id =" << idLimites;
        return false;
    }

    // On ne récupère que Amp_min et Amp_max
    Amp_min = query.value(0).toDouble();
    Amp_max = query.value(1).toDouble();

    qDebug() << "[LIMITES] Amp_min =" << Amp_min << ", Amp_max =" << Amp_max;
    return true;
}


// --- VERIFICATION ET ENREGISTREMENT ---
void MainWindow::verifyAndSave()//Jenoush, Anthony
{
    const int ID_LIMITES = 1;  // ou lire dynamiquement
    if (!loadLimits(ID_LIMITES)) {
        QMessageBox::warning(this, "Limites",
                             "Impossible de charger les limites de test !");
        return;
    }

    // on compare chaque gain
    bool passe = true;
    for (double g : m_gainValues) {
        if (g < Amp_min || g > Amp_max) {
            passe = false;
            break;
        }
    }
    QString status = passe ? "Réussi" : "Raté";
    ui->lineEditResultat->setText(status);

    // on enregistre en base
    const QString codebar = ui->lineEditBarcode->text().trimmed();
    saveResults(codebar, m_gainValues, ID_LIMITES, status);
}

void MainWindow::saveResults(const QString &codebarre,
                             const QVector<double> &gains,
                             int idLimites,
                             const QString &status)// Omar
{
    if (!db.isOpen()) {
        connectToDatabase();
        if (!db.isOpen()) return;
    }

    // création table si nécessaire
    {
        QSqlQuery createQ(db);
        const QString createTbl = QStringLiteral(R"(
            CREATE TABLE IF NOT EXISTS technicien (
                id_test     INT AUTO_INCREMENT PRIMARY KEY,
                codebarre   VARCHAR(255) NOT NULL,
                valeur1     DOUBLE NOT NULL,
                valeur2     DOUBLE NOT NULL,
                valeur3     DOUBLE NOT NULL,
                valeur4     DOUBLE NOT NULL,
                valeur5     DOUBLE NOT NULL,
                id_limites  INT,
                status      VARCHAR(50) DEFAULT 'Inconnu',
                FOREIGN KEY (id_limites) REFERENCES limites(id)
                  ON UPDATE CASCADE ON DELETE SET NULL
            ) ENGINE=InnoDB;
        )");
        if (!createQ.exec(createTbl)) {
            qWarning() << "[BDD] Erreur création table technicien :"
                       << createQ.lastError().text();
            return;
        }
    }

    // insertion
    QString safeCode = codebarre;
    safeCode.replace("'", "''");

    QString sql = QStringLiteral(
        "INSERT INTO technicien "
        "(codebarre, valeur1, valeur2, valeur3, valeur4, valeur5, id_limites, status) "
        "VALUES ('%1', %2, %3, %4, %5, %6, %7, '%8');"
    ).arg(safeCode)
     .arg(gains.value(0,0.0), 0, 'f', 6)
     .arg(gains.value(1,0.0), 0, 'f', 6)
     .arg(gains.value(2,0.0), 0, 'f', 6)
     .arg(gains.value(3,0.0), 0, 'f', 6)
     .arg(gains.value(4,0.0), 0, 'f', 6)
     .arg(idLimites)
     .arg(status);

    QSqlQuery query(db);
    if (!query.exec(sql)) {
        qWarning() << "[BDD] Échec insertion :" << query.lastError().text();
        QMessageBox::warning(this, "Erreur",
                             "Insertion échouée :\n" + query.lastError().text());
    }
}

// --- CONNEXION BDD ---
void MainWindow::connectToDatabase()// Omar
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
        db = QSqlDatabase::database("qt_sql_default_connection");
    else
        db = QSqlDatabase::addDatabase("QMYSQL");

    db.setHostName("localhost");
    db.setDatabaseName("Projet_AJO");
    db.setUserName("root");
    db.setPassword("");
    if (!db.open()) {
        QMessageBox::critical(this, "Erreur de connexion",
                              "Impossible de se connecter :\n" + db.lastError().text());
    } else {
        qDebug() << "Connecté à MySQL.";
    }
}
