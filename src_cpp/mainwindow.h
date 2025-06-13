#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSqlDatabase>
#include <QTimer>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>
#include <QKeyEvent>
#include <QVector>
#include <QString>
#include <QStringList>
#include <visa.h>
#include "dialogtech.h"
#include "dialoglogin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    DialogTech tech;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event) override;

    // vos listes publiques existantes
    QVector<double> frequencyList;
    QVector<double> veList;
    QVector<double> vsList;

    void on_pushButtonGraph_clicked();

private slots:
    void readData();            // Lit les données de la douchette
    void startTest();           // Démarre le test
    void updateProgressBar();   // Met à jour la barre de progression
private:
    Ui::MainWindow *ui;

    QSerialPort    serial;      // Port série pour la douchette
    QSqlDatabase   db;          // Base de données
    QTimer        *timer;       // Timer pour la barre de progression
    int            progressValue;

    void connectToDatabase();

    bool checkVoltage();
    bool checkBarcodeScanned();

    int  valeurCourante;
    void testInstrument1();

    // vos buffers et timers internes
    QTimer       *testTimer;
    int           currentCycle;
    int           currentInstrument;
    char          buf[3][256];
    bool          testInProgress;
    QStringList   commandsForThirdInstrument;
    void performNextStep();
    void gabaritcalcule();

    // --- AJOUTS POUR VÉRIFICATION ET ENREGISTREMENT ---
    QVector<double> m_veValues;
    QVector<double> m_vsValues;
    QVector<double> m_freqValues;
    QVector<double> m_gainValues;  // stocke les gains calculés

    double Amp_min = 0.0;  // limites chargées depuis la BDD
    double Amp_max = 0.0;

    // charge Amp_min / Amp_max depuis la table `limites`
    bool loadLimits(int idLimites);

    // compare m_gainValues aux limites, écrit dans lineEditResultat et enregistre
    void verifyAndSave();

    // insère le code-barres, les gains, l'id des limites et le status en BDD
    void saveResults(const QString &codebarre,
                     const QVector<double> &gains,
                     int idLimites,
                     const QString &status);
};

#endif // MAINWINDOW_H
