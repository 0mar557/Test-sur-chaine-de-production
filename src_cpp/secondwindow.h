#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSqlDatabase>
#include <QTimer>
#include <QSqlError>
#include <QMessageBox>
#include <visa.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void readData(); // Lit les données de la douchette
    void startTest(); // Démarre le test
    void updateProgressBar(); // Met à jour la barre de progression
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort serial; // Port série pour la douchette
    QSqlDatabase db; // Base de données
    QTimer *timer; // Timer pour la barre de progression
    int progressValue; // Valeur actuelle de la barre de progression
    void connectToDatabase();
    QString m_combox;
    bool checkVoltage();
    bool checkBarcodeScanned();
};

#endif // MAINWINDOW_H
