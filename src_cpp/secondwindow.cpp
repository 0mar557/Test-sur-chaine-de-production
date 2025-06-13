#include "secondwindow.h"
#include "ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget *parent)
    : QWidget(parent), ui(new Ui::SecondWindow)
{
    ui->setupUi(this);

    connect(ui->pushButtonRetour, &QPushButton::clicked, this, [=]() {
        this->hide();
        parent->show(); // afficher MainWindow à nouveau
    });
}

SecondWindow::~SecondWindow()
{
    delete ui;
}
