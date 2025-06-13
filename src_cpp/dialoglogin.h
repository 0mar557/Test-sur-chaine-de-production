#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include "dialogtech.h"

#include <QDialog>
#include <qabstractbutton.h>

namespace Ui {
class DialogLogin;
}

class DialogLogin : public QDialog
{
    Q_OBJECT
    DialogTech *dlg;
public:
    explicit DialogLogin(QWidget *parent = 0);
    ~DialogLogin();
    void setDialogTech(DialogTech *dlg) { this->dlg= dlg; }
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::DialogLogin *ui;
};

#endif // DIALOGLOGIN_H
