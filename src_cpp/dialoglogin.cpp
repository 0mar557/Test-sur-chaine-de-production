#include "dialoglogin.h"
#include "ui_dialoglogin.h"
#include <QMessageBox>
#include <QDebug>
#include "dialogtech.h"

DialogLogin::DialogLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogin)
{
    ui->setupUi(this);

}

DialogLogin::~DialogLogin()
{
    delete ui;
}


void DialogLogin::on_buttonBox_clicked(QAbstractButton *button)
{
    // Vérifie si l'utilisateur a cliqué sur "OK"
    if (ui->buttonBox->buttonRole(button) == QDialogButtonBox::AcceptRole) {
        QString user = ui->lineEditUser->text();
        QString pass = ui->lineEditPass->text();

        if (user == "" && pass == "") {

            qDebug()<<"login ok";
            dlg->exec();
            accept(); // Ferme la fenêtre en validant
        } else {
            QMessageBox::warning(this, "Erreur", "Identifiant ou mot de passe incorrect");
            qDebug()<<"login pas ok";
            reject(); // Ferme la fenêtre en annulant

        }
    } else if (ui->buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole) {
        reject();
    }
}
