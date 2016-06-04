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
    QTextEdit *zoneVariable;
    QLineEdit *zoneIdentifiantVariable;
    QListView* listeProgrammes;
    QListView* listeVariables;
    QStringListModel *modeleProgrammes;
    QStringListModel *modeleVariables;
    QPushButton *boutonValider;
    QPushButton *boutonEffacer;
    QPushButton *boutonSupprimer;
    QPushButton *boutonModifier;
    QPushButton *boutonValiderVariable;
    QPushButton *boutonEffacerVariable;
    QPushButton *boutonSupprimerVariable;
    QPushButton *boutonModifierVariable;
    QTabWidget *tabWidget;


public slots :
    void interpreter(QString exp);
    void ajouterProgramme();
    void supprimerProgramme();
    void afficherProgrammeListe(QModelIndex modelIndex);
    void modifierProgramme();
    void effacerChampsProgramme();
    void updateTab(int index);


    void ajouterVariable();
    void supprimerVariable();
    void afficherVariableListe(QModelIndex modelIndex);
    void modifierVariable();
    void effacerChampsVariable();


    void returnPressedStr();

};

#endif // MAINWINDOW_H
