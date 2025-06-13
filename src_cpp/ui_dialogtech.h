/********************************************************************************
** Form generated from reading UI file 'dialogtech.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGTECH_H
#define UI_DIALOGTECH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_DialogTech
{
public:
    QPushButton *pushButtonAfficherGraph;
    QDialogButtonBox *buttonBox;
    QGraphicsView *graphicsView;
    QLabel *ledLabel;
    QLabel *ledLabel_2;
    QGroupBox *groupBox_2;
    QComboBox *comboBox;
    QPushButton *pushButton_3;
    QLabel *label_14;
    QTextEdit *textEdit_2;
    QComboBox *comboBoxInstrument_2;
    QLabel *label_15;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_6;
    QLineEdit *lineEditAmp_min;
    QLineEdit *lineEditFinf;
    QLabel *label_5;
    QLabel *label_7;
    QLineEdit *lineEditAmp_max;
    QLineEdit *lineEditFsup;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *defaultButton;
    QLineEdit *lineEditCodebarre;
    QLabel *label_2;
    QTextEdit *textEdit_resultat;
    QLabel *label_3;

    void setupUi(QDialog *DialogTech)
    {
        if (DialogTech->objectName().isEmpty())
            DialogTech->setObjectName(QStringLiteral("DialogTech"));
        DialogTech->resize(1242, 974);
        pushButtonAfficherGraph = new QPushButton(DialogTech);
        pushButtonAfficherGraph->setObjectName(QStringLiteral("pushButtonAfficherGraph"));
        pushButtonAfficherGraph->setGeometry(QRect(9, 789, 481, 23));
        buttonBox = new QDialogButtonBox(DialogTech);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(500, 790, 156, 23));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        graphicsView = new QGraphicsView(DialogTech);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 10, 911, 761));
        ledLabel = new QLabel(DialogTech);
        ledLabel->setObjectName(QStringLiteral("ledLabel"));
        ledLabel->setGeometry(QRect(930, 760, 47, 13));
        ledLabel_2 = new QLabel(DialogTech);
        ledLabel_2->setObjectName(QStringLiteral("ledLabel_2"));
        ledLabel_2->setGeometry(QRect(930, 780, 47, 13));
        groupBox_2 = new QGroupBox(DialogTech);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(940, 200, 291, 181));
        comboBox = new QComboBox(groupBox_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(60, 50, 111, 22));
        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(180, 50, 91, 23));
        label_14 = new QLabel(groupBox_2);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 50, 51, 20));
        textEdit_2 = new QTextEdit(groupBox_2);
        textEdit_2->setObjectName(QStringLiteral("textEdit_2"));
        textEdit_2->setGeometry(QRect(10, 79, 251, 91));
        textEdit_2->setReadOnly(true);
        comboBoxInstrument_2 = new QComboBox(groupBox_2);
        comboBoxInstrument_2->addItem(QString());
        comboBoxInstrument_2->addItem(QString());
        comboBoxInstrument_2->addItem(QString());
        comboBoxInstrument_2->addItem(QString());
        comboBoxInstrument_2->setObjectName(QStringLiteral("comboBoxInstrument_2"));
        comboBoxInstrument_2->setGeometry(QRect(100, 20, 111, 22));
        label_15 = new QLabel(groupBox_2);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(20, 20, 71, 20));
        QFont font;
        font.setPointSize(10);
        label_15->setFont(font);
        groupBox = new QGroupBox(DialogTech);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(940, 10, 292, 181));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font);

        gridLayout->addWidget(label_6, 0, 1, 1, 2);

        lineEditAmp_min = new QLineEdit(groupBox);
        lineEditAmp_min->setObjectName(QStringLiteral("lineEditAmp_min"));

        gridLayout->addWidget(lineEditAmp_min, 1, 0, 1, 1);

        lineEditFinf = new QLineEdit(groupBox);
        lineEditFinf->setObjectName(QStringLiteral("lineEditFinf"));

        gridLayout->addWidget(lineEditFinf, 1, 1, 1, 2);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font);

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font);

        gridLayout->addWidget(label_7, 2, 1, 1, 2);

        lineEditAmp_max = new QLineEdit(groupBox);
        lineEditAmp_max->setObjectName(QStringLiteral("lineEditAmp_max"));

        gridLayout->addWidget(lineEditAmp_max, 3, 0, 1, 1);

        lineEditFsup = new QLineEdit(groupBox);
        lineEditFsup->setObjectName(QStringLiteral("lineEditFsup"));

        gridLayout->addWidget(lineEditFsup, 3, 1, 1, 2);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 4, 0, 1, 3);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 5, 0, 1, 1);

        defaultButton = new QPushButton(groupBox);
        defaultButton->setObjectName(QStringLiteral("defaultButton"));

        gridLayout->addWidget(defaultButton, 5, 1, 1, 2);

        lineEditCodebarre = new QLineEdit(DialogTech);
        lineEditCodebarre->setObjectName(QStringLiteral("lineEditCodebarre"));
        lineEditCodebarre->setGeometry(QRect(740, 790, 113, 20));
        label_2 = new QLabel(DialogTech);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(670, 790, 71, 16));
        label_2->setFont(font);
        textEdit_resultat = new QTextEdit(DialogTech);
        textEdit_resultat->setObjectName(QStringLiteral("textEdit_resultat"));
        textEdit_resultat->setGeometry(QRect(1010, 390, 131, 41));
        textEdit_resultat->setReadOnly(true);
        label_3 = new QLabel(DialogTech);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(950, 400, 71, 16));
        label_3->setFont(font);

        retranslateUi(DialogTech);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogTech, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogTech, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogTech);
    } // setupUi

    void retranslateUi(QDialog *DialogTech)
    {
        DialogTech->setWindowTitle(QApplication::translate("DialogTech", "Dialog", nullptr));
        pushButtonAfficherGraph->setText(QApplication::translate("DialogTech", "Afficher le graphe", nullptr));
        ledLabel->setText(QString());
        ledLabel_2->setText(QString());
        groupBox_2->setTitle(QApplication::translate("DialogTech", "Test unitaire", nullptr));
        comboBox->setItemText(0, QApplication::translate("DialogTech", "*IDN?", nullptr));
        comboBox->setItemText(1, QApplication::translate("DialogTech", ":APPL:SIN 1KHZ, 1VPP, 0V", nullptr));
        comboBox->setItemText(2, QApplication::translate("DialogTech", "MEASure:VPP? CHAN1", nullptr));
        comboBox->setItemText(3, QApplication::translate("DialogTech", ":MEAS:VOLT:AC?", nullptr));
        comboBox->setItemText(4, QApplication::translate("DialogTech", "MEASure:VPP? CHAN2", nullptr));
        comboBox->setItemText(5, QString());

        pushButton_3->setText(QApplication::translate("DialogTech", "send and read", nullptr));
        label_14->setText(QApplication::translate("DialogTech", "command", nullptr));
        textEdit_2->setPlaceholderText(QApplication::translate("DialogTech", "edit", nullptr));
        comboBoxInstrument_2->setItemText(0, QApplication::translate("DialogTech", "USB0::0x1AB1::0x0642::DG1ZA231001077::0", nullptr));
        comboBoxInstrument_2->setItemText(1, QApplication::translate("DialogTech", "USB0::0xF4EC::0xEE38::NDM35FAD2R0210::0::INSTR", nullptr));
        comboBoxInstrument_2->setItemText(2, QApplication::translate("DialogTech", "USB0::0xF4EC::0xEE38::NDM35FAD2R0189::0::INSTR", nullptr));
        comboBoxInstrument_2->setItemText(3, QApplication::translate("DialogTech", "USB0::0x1AB1::0x0515::MS5A252504538::0::INSTR", nullptr));

        label_15->setText(QApplication::translate("DialogTech", "Instrument :", nullptr));
        groupBox->setTitle(QApplication::translate("DialogTech", "Gabarit", nullptr));
        label->setText(QApplication::translate("DialogTech", "Amplitude min", nullptr));
        label_6->setText(QApplication::translate("DialogTech", "Fr\303\251quence inf\303\251rieur", nullptr));
        label_5->setText(QApplication::translate("DialogTech", "Amplitude max", nullptr));
        label_7->setText(QApplication::translate("DialogTech", "Fr\303\251quence Sup\303\251rieur", nullptr));
        pushButton->setText(QApplication::translate("DialogTech", "Tracer Gabarit", nullptr));
        pushButton_2->setText(QApplication::translate("DialogTech", "Enregistrement DataBase", nullptr));
        defaultButton->setText(QApplication::translate("DialogTech", "Par d\303\251faut", nullptr));
        label_2->setText(QApplication::translate("DialogTech", "code Barre", nullptr));
        textEdit_resultat->setPlaceholderText(QApplication::translate("DialogTech", "edit", nullptr));
        label_3->setText(QApplication::translate("DialogTech", "R\303\251sultat", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogTech: public Ui_DialogTech {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGTECH_H
