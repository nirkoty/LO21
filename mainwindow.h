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
#include <QSignalMapper>
#include <QGridLayout>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Manager* man,  QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Manager* manager;
    QLineEdit *inputLine;
    QGridLayout *layoutClavier;
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
    QAction *actionAfficherClavier;
    QWidget* conteneurClavier;
    Pile* pile;


public slots :
    void interpreter(QString exp);
    void ajouterProgramme();
    void supprimerProgramme();
    void afficherProgrammeListe(QModelIndex modelIndex);
    void modifierProgramme();
    void effacerChampsProgramme();
    void updateTab(int index);
    void appendInputKeyboard(QString input){ inputLine->insert(input); interpreter(inputLine->text());}
    void ajouterVariable();
    void supprimerVariable();
    void afficherVariableListe(QModelIndex modelIndex);
    void modifierVariable();
    void effacerChampsVariable();
    void returnPressedStr();
    void afficherClavier(bool affichage);

};

#endif // MAINWINDOW_H
