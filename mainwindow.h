#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "pile.h"
#include "manager.h"
#include <QLineEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Pile& pile, Manager* man,  QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Manager* manager;
    QLineEdit *inputLine;

public slots :
    void interpreter(QString exp);


};

#endif // MAINWINDOW_H
