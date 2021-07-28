#include "iiwindow.h"
#include "ui_iiwindow.h"

IIWindow::IIWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IIWindow)
{
    ui->setupUi(this);
}

IIWindow::~IIWindow()
{
    delete ui;
}
