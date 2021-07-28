#ifndef IIWINDOW_H
#define IIWINDOW_H

#include <QMainWindow>
#include"mainwindow.h"


namespace Ui {
class IIWindow;
}

class IIWindow : public QMainWindow
{

    Q_OBJECT

public:
    explicit IIWindow(QWidget *parent = nullptr);
    ~IIWindow();

private:
    Ui::IIWindow *ui;
};

#endif // IIWINDOW_H
