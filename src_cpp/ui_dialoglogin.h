/********************************************************************************
** Form generated from reading UI file 'dialoglogin.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGLOGIN_H
#define UI_DIALOGLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogLogin
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEditUser;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEditPass;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DialogLogin)
    {
        if (DialogLogin->objectName().isEmpty())
            DialogLogin->setObjectName(QStringLiteral("DialogLogin"));
        DialogLogin->resize(307, 137);
        gridLayout = new QGridLayout(DialogLogin);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(DialogLogin);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        lineEditUser = new QLineEdit(DialogLogin);
        lineEditUser->setObjectName(QStringLiteral("lineEditUser"));

        verticalLayout->addWidget(lineEditUser);


        verticalLayout_3->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(DialogLogin);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        lineEditPass = new QLineEdit(DialogLogin);
        lineEditPass->setObjectName(QStringLiteral("lineEditPass"));
        lineEditPass->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(lineEditPass);


        verticalLayout_3->addLayout(verticalLayout_2);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(DialogLogin);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        retranslateUi(DialogLogin);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogLogin, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogLogin, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogLogin);
    } // setupUi

    void retranslateUi(QDialog *DialogLogin)
    {
        DialogLogin->setWindowTitle(QApplication::translate("DialogLogin", "Dialog", nullptr));
        label->setText(QApplication::translate("DialogLogin", "User:", nullptr));
        lineEditUser->setText(QString());
        label_2->setText(QApplication::translate("DialogLogin", "Password:", nullptr));
        lineEditPass->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogLogin: public Ui_DialogLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGLOGIN_H
