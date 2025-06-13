// dialogtech.h
#ifndef DIALOGTECH_H
#define DIALOGTECH_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsSimpleTextItem>
#include <QVector>
#include <QResizeEvent>
#include <QMainWindow>
#include <QSerialPort>
#include <QSqlDatabase>
#include <QTimer>
#include <QSqlError>
#include <QMessageBox>
#include <visa.h>
#include "dialogtech.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DialogTech; }
QT_END_NAMESPACE

#define NB_LABELS_Y 10

class DialogTech : public QDialog
{
    Q_OBJECT
    QGraphicsScene scene;
    QGraphicsSimpleTextItem *lblTextY[10];
    int nBPoints;
    double Amp,Amp_min,Amp_max, Fi, Fs;
public:
    explicit DialogTech(QWidget *parent = nullptr);
    ~DialogTech();
    // Prototype si besoin (non utilisé par défaut)
    double ampli(double freq);
    // Initialise les données de fréquence et tensions
    void setData(const QVector<double>& freq,
                 const QVector<double>& ve,
                 const QVector<double>& vs);
    void mesureTest();
    void lireValeursReelles();

protected:
    // Réajuste l'affichage de la scène à chaque redimensionnement
    void resizeEvent(QResizeEvent *event) override;

private slots:
    // Génère et affiche le graphique
    void on_pushButtonAfficherGraph_clicked();
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_pushButton_2_clicked();



private:
    Ui::DialogTech *ui;
    QVector<double> freqValues;
    QVector<double> veValues;
    QSqlDatabase db;
    QVector<double> vsValues;
    QString m_combox;
    double getFrequency();
    ViSession defaultRM, vi[3];
    QVector<double> m_freqValues, m_veValues, m_vsValues;
    void connectToDatabase();
    QList<QGraphicsItem*> m_gabaritItems;
    void initGrid();
    double m_midFreqOriginal = 0.0;
    double m_midGainOriginal = 0.0;
    void gabaritcalcule();
    void chargerLimitesDepuisBDD(int idLimites);
    QVector<double> m_origFreq, m_origVe, m_origVs;
    QVector<QGraphicsItem*> m_annotationItems;
    void afficherPointsGabarit();
    int FreqToIndex(double freq) const;
    bool graphDrawn = false;
    void enregistrerResultats(const QString &codebarre, const QVector<double> &gains, int idLimites, const QString &status);
    void on_defaultButton_clicked();
};

#endif // DIALOGTECH_H
