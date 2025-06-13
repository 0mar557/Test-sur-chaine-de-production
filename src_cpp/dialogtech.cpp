
// dialogtech.cpp
#include "dialogtech.h"
#include "ui_dialogtech.h"
#include <QtMath>
#include <QPen>
#include <QBrush>
#include <QSizePolicy>
#include <QDebug>
#include <QMessageBox>
#include <qmath.h>
#include <QThread>
#include <QSqlQuery>

#define C2(x) ((x)*(x))
#define NB_MAX_PT 600

DialogTech::DialogTech(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogTech)
{
    ui->setupUi(this);
    connectToDatabase();
    chargerLimitesDepuisBDD(1);
    // Pour que la vue suive la taille du widget
    ui->graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    nBPoints= 21;
}

DialogTech::~DialogTech()
{
    delete ui;
}

// Stub si non utilisé
double DialogTech::ampli(double freq)// Jenoush
{
    // double Amp=20, Fi=100, Fs=10e3;
    return Amp / qSqrt(1+C2(freq/Fs)) / qSqrt(1+C2(Fi/freq));
}


void DialogTech::setData(const QVector<double>& freq,
                         const QVector<double>& ve,
                         const QVector<double>& vs)// Anthony
{
    freqValues = freq;
    veValues   = ve;
    vsValues   = vs;
    qDebug() << "[DialogTech] setData:"
             << freqValues.size() << "points chargés";
}

void DialogTech::mesureTest()// Jenoush
{
    veValues.clear();
    vsValues.clear();
    freqValues.clear();
    for(int i=0,j=0; i<=NB_MAX_PT; i+=NB_MAX_PT/(nBPoints-1),j++) // 11 valeurs de frequence
    {
        freqValues<<qPow(10,i/100.0);
        veValues<< 1; // Ve = 1V
        vsValues<< veValues[j]*ampli(freqValues[j]); // on fait la mesure
        //qDebug()<<freqValues[j]<<veValues[j]<<vsValues[j];
    }
}

void DialogTech::lireValeursReelles()// Jenoush
{
    ViSession defaultRM, vi[4]; // 0: multimètre Ve, 1: multimètre Vs, 2: générateur, 3: oscillo CH2
    char buf[3][256] = {{0}};
    QString instruments[4] = {
        "USB0::0xF4EC::0xEE38::NDM35FAD2R0189::0::INSTR",   // Ve
        "USB0::0xF4EC::0xEE38::NDM35FAD2R0210::0::INSTR",   // Vs normal
        "USB0::0x1AB1::0x0642::DG1ZA231001077::0::INSTR",   // Générateur
        "USB0::0x1AB1::0x0515::MS5A252504538::0::INSTR"    // Oscillo CH2
    };

    veValues.clear();
    vsValues.clear();
    freqValues.clear();

    if (viOpenDefaultRM(&defaultRM) != VI_SUCCESS) {
        qDebug() << "[lireValeursReelles] Échec ouverture session VISA";
        return;
    }

    // Connexion aux 4 instruments
    for (int i = 0; i < 4; ++i) {
        if (viOpen(defaultRM,
                   instruments[i].toUtf8().constData(),
                   VI_NULL, VI_NULL, &vi[i]) != VI_SUCCESS) {
            qDebug() << QString("[lireValeursReelles] Échec ouverture %1").arg(instruments[i]);
            for (int j = 0; j < i; ++j) viClose(vi[j]);
            viClose(defaultRM);
            return;
        }
    }

    // Boucle de mesure
    for (int i = 0, cycle = 0; i <= NB_MAX_PT; i += NB_MAX_PT / (nBPoints - 1), ++cycle) {
        double freqLog = qPow(10.0, i / 100.0);
        QString cmdGen = QString(":APPL:SIN %1HZ, 500mVPP, 0V\n").arg(freqLog, 0, 'f', 2);

        // Générateur
        viPrintf(vi[2], cmdGen.toUtf8().constData());
        viPrintf(vi[2], "OUTP1:STAT ON\n");
        QThread::msleep(300);

        // Lecture Ve, Vs et F
        for (int k = 0; k < 3; ++k) {
            memset(buf[k], 0, sizeof(buf[k]));
            bool ok = false;
            int tries = 0;

            while (!ok && tries < 2) {
                if (k == 0) {
                    // multimètre Ve
                    viPrintf(vi[0], ":MEAS:VOLT:AC?\n");
                    viFlush(vi[0], VI_READ_BUF);
                }
                else if (k == 1) {
                    // multimètre Vs (CORRECTION : on utilise vi[1] ici)
                    QThread::msleep(500);
                    viPrintf(vi[1], ":MEAS:VOLT:AC?\n");
                    viFlush(vi[1], VI_READ_BUF);
                }
                else {
                    // générateur (lecture fréquence)
                    viPrintf(vi[2], ":FREQ?\n");
                    viFlush(vi[2], VI_READ_BUF);
                }

                QThread::msleep(500);
                ViStatus status = viScanf(vi[k], "%t", buf[k]);
                if (status == VI_SUCCESS) {
                    ok = true;
                } else {
                    ++tries;
                    QThread::msleep(500);
                }
            }

            if (!ok) {
                qDebug() << QString("[lireValeursReelles] Erreur lecture instr %1").arg(k);
            }
        }

        // Conversion en double et stockage
        bool ok1 = false, ok2 = false, ok3 = false;
        double ve    = QString(buf[0]).toDouble(&ok1);
        double vs    = QString(buf[1]).toDouble(&ok2);
        double freqR = QString(buf[2]).toDouble(&ok3);

        if (ok1 && ok2 && ok3) {
            veValues.append(ve);
            vsValues.append(vs);
            freqValues.append(freqR);
            double gain = 20.0 * log10(vs / ve);
            qDebug() << QString("[Cycle %1] Ve=%2 V | Vs=%3 V | F=%4 Hz | Gain=%5 dB")
                        .arg(cycle+1).arg(ve).arg(vs).arg(freqR).arg(gain);
        } else {
            qDebug() << QString("[Cycle %1] Erreur conversion").arg(cycle+1);
        }
    }

    // Fermeture des sessions VISA
    for (int i = 0; i < 4; ++i) viClose(vi[i]);
    viClose(defaultRM);
}

void DialogTech::resizeEvent(QResizeEvent *event)// Anthony
{
    QDialog::resizeEvent(event);
    if (!scene.items().isEmpty()) {
        ui->graphicsView->fitInView(scene.sceneRect(), Qt::KeepAspectRatio);
    }
}

void DialogTech::on_comboBox_currentIndexChanged(int index)// Anthony
{
    // Vérifier que l'index est valide
    if (index >= 0) {
        m_combox = ui->comboBox->itemText(index); // Stocke le texte sélectionné dans la variable m_combox
    }
}

double DialogTech::getFrequency()// Jenoush
{
    ViSession defaultRM, vi;
    char buf[256] = {0};
    double freq = 0.0;

    QString selectedInstrument = ui->comboBoxInstrument_2->currentText().trimmed();
    if (selectedInstrument.isEmpty()) return 0.0;

    if (viOpenDefaultRM(&defaultRM) != VI_SUCCESS) return 0.0;
    if (viOpen(defaultRM, selectedInstrument.toUtf8().constData(), VI_NULL, VI_NULL, &vi) != VI_SUCCESS) {
        viClose(defaultRM);
        return 0.0;
    }

    // Envoie la commande de fréquence
    if (viPrintf(vi, ":MEAS:FREQ?\n") == VI_SUCCESS &&
            viScanf(vi, "%t", buf) == VI_SUCCESS) {
        freq = QString::fromUtf8(buf).toDouble();
    }

    viClose(vi);
    viClose(defaultRM);
    return freq;
}

void DialogTech::connectToDatabase()//Omar
{
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

void DialogTech::chargerLimitesDepuisBDD(int idLimites)//Omar
{
    if (!db.isOpen()) {
        qWarning() << "[DB] Connexion fermée, tentative de reconnexion...";
        connectToDatabase();
        if (!db.isOpen()) {
            qWarning() << "[DB] Échec de reconnexion.";
            return;
        }
    }

    QSqlQuery query(db);
    QString sql = QString(R"(
                          SELECT
                          Amplitude_min,
                          Amplitude_max,
                          `Fréquence_Inférieur`,
                          `Fréquence_Supérieur`
                          FROM limites
                          WHERE id = %1
                          )").arg(idLimites);

    if (!query.exec(sql)) {
        qWarning() << "[SQL] Erreur requête SELECT :" << query.lastError().text();
        return;
    }


    if (!query.exec()) {
        qWarning() << "[SQL] Erreur requête SELECT :" << query.lastError().text();
        return;

    }

    if (!query.next()) {
        qWarning() << "[SQL] Aucune ligne trouvée avec id =" << idLimites;
        return;
    }

    qDebug() << "[SQL] Données limites chargées avec succès";
    // Extraction des valeurs depuis le record SQL
    double ampMin     = query.value(0).toDouble();
    double ampMax     = query.value(1).toDouble();
    double frequenceI = query.value(2).toDouble();
    double frequenceS = query.value(3).toDouble();

    // Mise à jour des QLineEdit
    ui->lineEditAmp_min->setText(QString::number(ampMin));
    ui->lineEditAmp_max->setText(QString::number(ampMax));
    ui->lineEditFinf   ->setText(QString::number(frequenceI));
    ui->lineEditFsup   ->setText(QString::number(frequenceS));

    //Affectation des valeur//
    Amp_min = ampMin;
    Amp_max = ampMax;
    Fi = frequenceI;
    Fs = frequenceS;
    qDebug() << "[SQL] Limites internes initialisées :"
             << "Amp_min=" << Amp_min
             << "Amp_max=" << Amp_max
             << "Fi="      << Fi
             << "Fs="      << Fs;
}

void DialogTech::on_pushButton_3_clicked()// Jenoush
{
    ViSession defaultRM, vi;

    char buf[256] = {0};
    QString strTemp;

    // Récupérer l'instrument sélectionné dans la comboBoxInstrument
    QString selectedInstrument = ui->comboBoxInstrument_2->currentText().trimmed();
    if (selectedInstrument.isEmpty()) {
        QMessageBox::warning(this, "Avertissement", "Aucun instrument sélectionné.");
        return;
    }

    // Ouvrir la session VISA par défaut
    if (viOpenDefaultRM(&defaultRM) != VI_SUCCESS) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir la session VISA");
        return;
    }

    // Ouvrir la connexion avec l'instrument sélectionné
    if (viOpen(defaultRM, selectedInstrument.toUtf8().constData(), VI_NULL, VI_NULL, &vi) != VI_SUCCESS) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir la connexion avec l'instrument sélectionné");
        viClose(defaultRM);
        return;
    } else {
        qDebug() << "Connexion ouverte avec :" << selectedInstrument;
    }

    // Récupérer la commande sélectionnée dans la QComboBox principale
    strTemp = ui->comboBox->currentText() + "\n";
    QByteArray command = strTemp.toUtf8();

    // Envoyer la commande
    if (viPrintf(vi, command.constData()) != VI_SUCCESS) {
        QMessageBox::critical(this, "Erreur", "Échec de l'envoi de la commande");
        viClose(vi);
        viClose(defaultRM);
        return;
    }

    // Lire la réponse de l'instrument
    if (viScanf(vi, "%t\n", buf) != VI_SUCCESS) {
        QMessageBox::critical(this, "Erreur", "Échec de la lecture de la réponse");
        viClose(vi);
        viClose(defaultRM);
        return;
    }

    qDebug() << "Réponse : " << buf;
    ui->textEdit_2->setText(QString::fromUtf8(buf));

    // Fermer les sessions
    viClose(vi);
    viClose(defaultRM);

}

void DialogTech::on_pushButtonAfficherGraph_clicked()// Anthony
{
    //lireValeursReelles();

    // simulation:
    Amp= 10,Fi=100, Fs=10e3;
    mesureTest(); // pour le test
    // juste après mesureTest(), avant tout re-simulé
    m_origFreq = freqValues;
    m_origVe   = veValues;
    m_origVs   = vsValues;


    //Initialise la grille
    initGrid();

    //Affiche les valeur du test effectuer ci dessus
    QPen pen(QBrush(QColor(255,0,0)),1);
    double yOld= NB_MAX_PT/2-5*20*log10(vsValues[0]/veValues[0]); // première valeur à 1Hz
    //yOld = NB_MAX_PT - yOld;
    int xOld= 0;
    for(int i=NB_MAX_PT/(nBPoints-1),j=1; i<=NB_MAX_PT; i+=NB_MAX_PT/(nBPoints-1),j++) // 11 valeurs de frequence
    {   //double y= NB_MAX_PT/2-5*ampli(freqValues[i]);
        double y= NB_MAX_PT/2-5*20*log10(vsValues[j]/veValues[j]);
        //y = NB_MAX_PT - y;
        //double y= NB_MAX_PT/2-5*20*log10(vsValues[i]/veValues[i]);
        //int x1= NB_MAX_PT/6*(log10(freqValues[i-1]));
        //int x2= NB_MAX_PT/6*(log10(freqValues[i]));
        scene.addLine(xOld,yOld,i,y,pen);
        xOld= i;
        yOld= y;
    }

    // 5) Calcul des gains des deux gabarits (sans les dessiner)
    afficherPointsGabarit();
    //resize(NB_MAX_PT+100,NB_MAX_PT+100);
    ui->graphicsView->setScene(&scene);
    graphDrawn = true;
    gabaritcalcule();
}

void DialogTech::gabaritcalcule()// Anthony
{
    // 1) Relire les limites depuis l'UI (inchangé)...
    bool ok;
    double ampMin = ui->lineEditAmp_min->text().toDouble(&ok);
    if (ok) Amp_min = ampMin;
    double ampMax = ui->lineEditAmp_max->text().toDouble(&ok);
    if (ok) Amp_max = ampMax;
    double frequenceI = ui->lineEditFinf->text().toDouble(&ok);
    if (ok) Fi = frequenceI;
    double frequenceS = ui->lineEditFsup->text().toDouble(&ok);
    if (ok) Fs = frequenceS;

    qDebug() << "[Draw] Nouvelles limites :"
             << "Amp_min=" << Amp_min
             << "Amp_max=" << Amp_max
             << "Fi="      << Fi
             << "Fs="      << Fs;

    initGrid();

    // 2) Définir les indices à tester : 2 premiers, le milieu, 2 derniers
    const int N = nBPoints;
    const QVector<int> indices = { 0, 1, N/2, N-2, N-1 };

    // 3) Calculer en une fois les gabarits haut et bas pour ces 5 points
    QVector<double> hiGains, loGains;
    // gabarit haut (Amp_max)
    Amp = Amp_max;
    mesureTest();
    for (int idx : indices) {
        hiGains.append(20.0 * log10(vsValues[idx] / veValues[idx]));
    }
    // gabarit bas (Amp_min)
    Amp = Amp_min;
    mesureTest();
    for (int idx : indices) {
        loGains.append(20.0 * log10(vsValues[idx] / veValues[idx]));
    }

    // 4) Calculer les gains mesurés « originaux » à ces mêmes indices
    QVector<double> origGains;
    for (int idx : indices) {
        double g = 20.0 * log10(m_origVs[idx] / m_origVe[idx]);
        origGains.append(g);
        qDebug() << QString("Pt %1: G_orig=%2 dB, Lo=%3 dB, Hi=%4 dB")
                    .arg(idx)
                    .arg(g)
                    .arg(loGains.last())
                    .arg(hiGains.last());
    }

    // 5) Vérifier que pour chacun des 5 points, lo <= orig <= hi
    bool passe = true;
    for (int i = 0; i < indices.size(); ++i) {
        if (origGains[i] < loGains[i] || origGains[i] > hiGains[i]) {
            passe = false;
            break;
        }
    }
    const QString status = passe ? "Réussi" : "Raté";
    ui->textEdit_resultat->setText(passe ? "Réussi" : "Raté");
    QString codebarre = ui->lineEditCodebarre->text().trimmed();
    if (!codebarre.isEmpty()) {
        enregistrerResultats(codebarre, origGains, /*idLimites=*/1, status);
    } else {
        QMessageBox::warning(this, "Champ vide",
                             "Veuillez saisir un code-barres pour l'enregistrement.");
    }
    ui->graphicsView->setScene(&scene);
}

void DialogTech::on_pushButton_clicked()// Anthony
{
    // 1) Relire les valeurs dans l'UI
    bool ok;
    double ampMin = ui->lineEditAmp_min->text().toDouble(&ok);
    if (ok) Amp_min = ampMin;
    double ampMax = ui->lineEditAmp_max->text().toDouble(&ok);
    if (ok) Amp_max = ampMax;
    double frequenceI = ui->lineEditFinf->text().toDouble(&ok);
    if (ok) Fi = frequenceI;
    double frequenceS = ui->lineEditFsup->text().toDouble(&ok);
    if (ok) Fs = frequenceS;

    qDebug() << "[Draw] Nouvelles limites :"
             << "Amp_min=" << Amp_min
             << "Amp_max=" << Amp_max
             << "Fi="      << Fi
             << "Fs="      << Fs;

    //2) Supprimer uniquement les anciens gabarits
    for (QGraphicsItem* it : m_gabaritItems) {
        scene.removeItem(it);
        delete it;
    }
    m_gabaritItems.clear();

    initGrid();

    Amp=Amp_max;
    mesureTest(); // pour le test

    QPen pen2(QBrush(QColor(0,255,0)),1);
    int yOld= NB_MAX_PT/2-5*20*log10(vsValues[0]/veValues[0]); // première valeur à 1Hz
    int xOld= 0;
    for(int i=NB_MAX_PT/(nBPoints-1),j=1; i<=NB_MAX_PT; i+=NB_MAX_PT/(nBPoints-1),j++) // 11 valeurs de frequence
    {   //double y= NB_MAX_PT/2-5*ampli(freqValues[i]);
        double y= (NB_MAX_PT)/2-5*20*log10(vsValues[j]/veValues[j]); //-100 ajoute pour le gabarit
        //double y= NB_MAX_PT/2-5*20*log10(vsValues[i]/veValues[i]);
        //int x1= NB_MAX_PT/6*(log10(freqValues[i-1]));
        //int x2= NB_MAX_PT/6*(log10(freqValues[i]));

        auto line = scene.addLine(xOld, yOld, i, y, pen2);
        m_gabaritItems.append(line);

        xOld= i;
        yOld= y;
    }

    Amp=Amp_min;
    mesureTest(); // pour le test

    QPen pen3(QBrush(QColor(100,55,100)),1);
    yOld= NB_MAX_PT/2-5*20*log10(vsValues[0]/veValues[0]); // première valeur à 1Hz
    xOld= 0;
    for(int i=NB_MAX_PT/(nBPoints-1),j=1; i<=NB_MAX_PT; i+=NB_MAX_PT/(nBPoints-1),j++) // 11 valeurs de frequence
    {   //double y= NB_MAX_PT/2-5*ampli(freqValues[i]);
        double y= (NB_MAX_PT)/2-5*20*log10(vsValues[j]/veValues[j]); //-100 ajoute pour le gabarit
        //double y= NB_MAX_PT/2-5*20*log10(vsValues[i]/veValues[i]);
        //int x1= NB_MAX_PT/6*(log10(freqValues[i-1]));
        //int x2= NB_MAX_PT/6*(log10(freqValues[i]));

        auto line = scene.addLine(xOld, yOld, i, y, pen3);
        m_gabaritItems.append(line);

        xOld= i;
        yOld= y;
    }

    if (graphDrawn) {
        gabaritcalcule();
    } else {
        qDebug() << "[Gabarit] La courbe n'est pas encore tracée, gabaritcalcule() non appelé.";
    }

    ui->graphicsView->setScene(&scene);
}

void DialogTech::on_pushButton_2_clicked() //Omar
{

    // 1) Récupération et validation des champs
    bool ok = false;
    qint64 amp_min = ui->lineEditAmp_min ->text().toLongLong(&ok);
    if (!ok) { QMessageBox::warning(this, tr("Erreur"), tr("Amplitude min invalide")); return; }
    qint64 amp_max = ui->lineEditFinf->text().toLongLong(&ok);
    if (!ok) { QMessageBox::warning(this, tr("Erreur"), tr("Amplitude max invalide")); return; }
    qint64 finf = ui->lineEditFinf->text().toLongLong(&ok);
    if (!ok) { QMessageBox::warning(this, tr("Erreur"), tr("Fréquence inférieure invalide")); return; }
    qint64 fsup = ui->lineEditFsup->text().toLongLong(&ok);
    if (!ok) { QMessageBox::warning(this, tr("Erreur"), tr("Fréquence supérieure invalide")); return; }

    // 2) Préparation de la chaîne SQL (MySQL convertira les nombres automatiquement)
    const qint64 idLimites = 1; // ou récupérez dynamiquement
    QString sql = QStringLiteral(
                "UPDATE limites SET "
                "Amplitude_min = %1, "
                "Amplitude_max = %2, "
                "Fréquence_Inférieur = %3, "
                "Fréquence_Supérieur = %4 "
                "WHERE id = %5;"
                )
            .arg(amp_min)
            .arg(amp_max)
            .arg(finf)
            .arg(fsup)
            .arg(idLimites);

    // 3) Exécution
    QSqlQuery query(db);
    if (!query.exec(sql)) {
        QMessageBox::warning(
                    this,
                    tr("Erreur"),
                    tr("Échec de la mise à jour des limites :\n%1").arg(query.lastError().text())
                    );
    }
    else {
        QMessageBox::information(this, tr("Succès"),
                                 tr("Limites mises à jour avec succès."));
    }

}

//Bouton Par défaut Cliquer//
void DialogTech::on_defaultButton_clicked()//Omar
{
    const qint64 idLimites = 1; // ou récupérez dynamiquement
    QString sql = QStringLiteral(
                "UPDATE limites SET "
                "Amplitude_min = %1, "
                "Amplitude_max = %2, "
                "Fréquence_Inférieur = %3, "
                "Fréquence_Supérieur = %4 "
                "WHERE id = %5;"
                )
            .arg(5)
            .arg(20)
            .arg(100)
            .arg(10000)
            .arg(idLimites);
    QSqlQuery query(db);
    if (!query.exec(sql)) {
        QMessageBox::warning(
                    this,
                    tr("Erreur"),
                    tr("Échec de la mise à jour des limites :\n%1").arg(query.lastError().text())
                    );
    }
    else {
        QMessageBox::information(this, tr("Succès"),
                                 tr("Limites mises à jour avec succès."));
    }

    sql = QString(R"(
                  SELECT
                  Amplitude_min,
                  Amplitude_max,
                  `Fréquence_Inférieur`,
                  `Fréquence_Supérieur`
                  FROM limites
                  WHERE id = %1
                  )").arg(idLimites);

    if (!query.exec(sql)) {
        qWarning() << "[SQL] Erreur requête SELECT :" << query.lastError().text();
        return;
    }


    if (!query.exec()) {
        qWarning() << "[SQL] Erreur requête SELECT :" << query.lastError().text();
        return;

    }

    if (!query.next()) {
        qWarning() << "[SQL] Aucune ligne trouvée avec id =" << idLimites;
        return;
    }

    double ampMin     = query.value(0).toDouble();
    double ampMax     = query.value(1).toDouble();
    double frequenceI = query.value(2).toDouble();
    double frequenceS = query.value(3).toDouble();

    ui->lineEditAmp_min->setText(QString::number(ampMin));
    ui->lineEditAmp_max->setText(QString::number(ampMax));
    ui->lineEditFinf->setText(QString::number(frequenceI));
    ui->lineEditFsup->setText(QString::number(frequenceS));
}

void DialogTech::initGrid()// Anthony
{
    QColor color(0,0,255);
    QPen penR(QBrush(color),1);
    scene.addRect(0,0,NB_MAX_PT+1,NB_MAX_PT+1,penR);
    scene.addLine(0,NB_MAX_PT/2,NB_MAX_PT,NB_MAX_PT/2,penR);
    QPen penD(QBrush(color),1,Qt::DashLine);
    for(int i=0,l=1; i<6; i++,l*=10)
    {	for(int x=l; x<l*10; x+=l)
        {	int X=100*log10((double)x);
            scene.addLine(X,0,X,NB_MAX_PT,penD);
        }
    }
    for(int i=0; i<NB_MAX_PT; i+=100)
        scene.addLine(0,i,NB_MAX_PT,i,penD);
    QFont font= ui->graphicsView->font();
    for(int i=0; i<6; i++)
    {   QString txt= QString::asprintf("%d",(3-i)*20);
        lblTextY[i]= scene.addSimpleText(txt,font);
        lblTextY[i]->setPos(-20,i*100);
    }
}

void DialogTech::afficherPointsGabarit()// Anthony
{
    // 1) On supprime les anciens marqueurs
    for (auto it : m_annotationItems) {
        scene.removeItem(it);
        delete it;
    }
    m_annotationItems.clear();

    // 2) On définit les fréquences-cibles
    QVector<double> targets = {
        100.0,                // bas 1
        40.0,                // bas 2
        freqValues[nBPoints/2], // point milieu
        40000.0,              // haut 1
        200000.0              // haut 2
    };

    // 3) On crée la liste des indices correspondants
    QVector<int> indices;
    for (double f : targets) {
        indices.append( FreqToIndex(f) );
    }

    // 4) On trace pour chacun : cercle + texte
    const int step = NB_MAX_PT / (nBPoints - 1);
    QPen   penCircle(Qt::blue); penCircle.setWidth(2);
    QBrush brushCircle(Qt::blue);
    QFont  fontText = ui->graphicsView->font();

    for (int idx : indices) {
        // coordonnées
        int   x     = step * idx;
        double gain = 20.0 * log10(vsValues[idx] / veValues[idx]);
        double y     = NB_MAX_PT/2.0 - 5.0 * gain;

        // a) cercle
        auto ellipse = scene.addEllipse(x - 4, y - 4, 8, 8, penCircle, brushCircle);
        m_annotationItems.append(ellipse);

        // b) texte
        double freq = freqValues[idx];
        QString txt = QString("F = %1 Hz\nG = %2 dB")
                .arg(freq, 0, 'f', 2)
                .arg(gain, 0, 'f', 2);
        auto textItem = scene.addText(txt, fontText);
        textItem->setDefaultTextColor(Qt::blue);
        QRectF rect = textItem->boundingRect();
        textItem->setPos(x + 5, y - rect.height()/2);
        m_annotationItems.append(textItem);
    }

    // 5) Rafraîchir la vue
    ui->graphicsView->setScene(&scene);
}

int DialogTech::FreqToIndex(double freq) const// Anthony
{
    int bestIdx = 0;
    double bestDiff = qAbs(freqValues[0] - freq);
    for (int i = 1; i < freqValues.size(); ++i) {
        double diff = qAbs(freqValues[i] - freq);
        if (diff < bestDiff) {
            bestDiff = diff;
            bestIdx = i;
        }
    }
    return bestIdx;
}

void DialogTech::enregistrerResultats(const QString& codebarre,const QVector<double>& gains,int idLimites,const QString& status) //Omar
{
    // Récupère la connexion existante (ou reconnecte)
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        connectToDatabase();
        if (!db.isOpen()) return;
    }

    // 1) Création de la table si nécessaire
    {
        QSqlQuery createQ(db);
        const QString createTbl = QStringLiteral(R"(
                                                 CREATE TABLE IF NOT EXISTS technicien (
                                                 id_test    INT AUTO_INCREMENT PRIMARY KEY,
                                                 codebarre  VARCHAR(255) NOT NULL,
                                                 valeur1      DOUBLE      NOT NULL,
                                                 valeur2      DOUBLE      NOT NULL,
                                                 valeur3      DOUBLE      NOT NULL,
                                                 valeur4      DOUBLE      NOT NULL,
                                                 valeur      DOUBLE      NOT NULL,
                                                 id_limites INT,
                                                 status     VARCHAR(50)  DEFAULT 'Inconnu',
                                                 FOREIGN KEY (id_limites)
                                                 REFERENCES limites(id)
                                                 ON UPDATE CASCADE
                                                 ON DELETE SET NULL
                                                 ) ENGINE=InnoDB;
                                                 )");
        if (!createQ.exec(createTbl)) {
            qWarning() << "[DB] Erreur création table information :"
                       << createQ.lastError().text();
            return;
        }
    }

    // 2) Prépare la chaîne INSERT
    QString safeCode = codebarre;
    safeCode.replace("'", "''");  // échappe les apostrophes

    QString sql = QStringLiteral(
                "INSERT INTO technicien "
                "(codebarre, valeur1, valeur2, valeur3, valeur4, valeur5, id_limites, status) "
                "VALUES ('%1', %2, %3, %4, %5, %6, %7, '%8');"
                ).arg(safeCode)
            .arg(gains.value(0, 0.0), 0, 'f', 6)
            .arg(gains.value(1, 0.0), 0, 'f', 6)
            .arg(gains.value(2, 0.0), 0, 'f', 6)
            .arg(gains.value(3, 0.0), 0, 'f', 6)
            .arg(gains.value(4, 0.0), 0, 'f', 6)
            .arg(idLimites)
            .arg(status);

    // 3) Exécution
    QSqlQuery query(db);
    if (!query.exec(sql)) {
        qWarning() << "[DB] Échec de l'insertion :" << query.lastError().text();
        QMessageBox::warning(this, "Erreur",
                             "Insertion échouée :\n" + query.lastError().text());
    } else {
        QMessageBox::information(this, "Succès",
                                 "Résultats enregistrés en base.");
    }
}
