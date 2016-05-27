#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "pile.h"
#include "manager.h"
#include <QLineEdit>
#include <QTextEdit>
#include <QMap>
#include <QListView>
#include <QStringListModel>
#include <QPushButton>

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
    QTextEdit *zoneProgramme;
    QLineEdit *zoneIdentifiant;
    QListView* listeProgrammes;
    QStringListModel *modeleProgrammes;
    QPushButton *boutonValider;
    QPushButton *boutonEffacer;
    QPushButton *boutonSupprimer;
    bool modificationProgramme;

public slots :
    void interpreter(QString exp);
    void ajouterProgramme();
    void modifierProgramme(QModelIndex modelIndex);
    void effacerChampsProgramme();


};

#endif // MAINWINDOW_H
