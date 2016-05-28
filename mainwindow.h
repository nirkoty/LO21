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
#include <QMessageBox>

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
    QPushButton *boutonModifier;

public slots :
    void interpreter(QString exp);
    void ajouterProgramme();
    void supprimerProgramme();
    void afficherProgrammeListe(QModelIndex modelIndex);
    void modifierProgramme();
    void effacerChampsProgramme();
    void ecrireFichierProgramme();


};

#endif // MAINWINDOW_H
