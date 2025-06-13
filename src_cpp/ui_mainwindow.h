/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *lineEditBarcode;
    QPushButton *pushButtonTest;
    QProgressBar *progressBar;
    QLabel *label;
    QLineEdit *lineEditResultat;
    QTextEdit *textEditInfo;
    QLabel *label_2;
    QTextEdit *textEditInstructions;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(305, 554);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(20, 10, 276, 550));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEditBarcode = new QLineEdit(groupBox);
        lineEditBarcode->setObjectName(QStringLiteral("lineEditBarcode"));

        gridLayout->addWidget(lineEditBarcode, 0, 0, 1, 2);

        pushButtonTest = new QPushButton(groupBox);
        pushButtonTest->setObjectName(QStringLiteral("pushButtonTest"));

        gridLayout->addWidget(pushButtonTest, 1, 0, 1, 2);

        progressBar = new QProgressBar(groupBox);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 2, 0, 1, 2);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        lineEditResultat = new QLineEdit(groupBox);
        lineEditResultat->setObjectName(QStringLiteral("lineEditResultat"));

        gridLayout->addWidget(lineEditResultat, 3, 1, 1, 1);

        textEditInfo = new QTextEdit(groupBox);
        textEditInfo->setObjectName(QStringLiteral("textEditInfo"));
        textEditInfo->setReadOnly(true);

        gridLayout->addWidget(textEditInfo, 4, 0, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 5, 0, 1, 1);

        textEditInstructions = new QTextEdit(groupBox);
        textEditInstructions->setObjectName(QStringLiteral("textEditInstructions"));
        textEditInstructions->setReadOnly(true);

        gridLayout->addWidget(textEditInstructions, 6, 0, 1, 2);

        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 18, 15));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Test d'appareil", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Lecteur Code-barre", nullptr));
        lineEditBarcode->setPlaceholderText(QApplication::translate("MainWindow", "Code-barres scann\303\251", nullptr));
        pushButtonTest->setText(QApplication::translate("MainWindow", "Tester l'appareil", nullptr));
        label->setText(QApplication::translate("MainWindow", "Resultat", nullptr));
        textEditInfo->setPlaceholderText(QApplication::translate("MainWindow", "Informations de l'appareil", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Etape:", nullptr));
        textEditInstructions->setPlaceholderText(QApplication::translate("MainWindow", "Instructions", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
