#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QListView"
#include "QPushButton"
#include "QLineEdit"
#include "QWidget"
#include "QtGui"
#include "QGridLayout"
#include "QTextEdit"
#include "QTabWidget"
#include "QErrorMessage"

MainWindow::MainWindow(Manager *man, QWidget *parent) : QMainWindow(parent), manager(man)
{

    pile = manager->getPile();


    // Général
    QHBoxLayout *mainLayout= new QHBoxLayout();
    tabWidget = new QTabWidget();
    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QGridLayout *layoutClavier = new QGridLayout;

    //Vue de la pile (gauche)
    QListView *vuePile = new QListView();
    vuePile->setGeometry(0,0,100,300);

    //Vue de l'historique de commandes (droite)
    QTextEdit *vueHistoriqueCommandes = new QTextEdit();
    inputLine = new QLineEdit();

    //Clavier numérique
    QPushButton *bouton1= new QPushButton();
    bouton1->setText("1");
    QPushButton *bouton2= new QPushButton();
    bouton2->setText("2");
    QPushButton *bouton3= new QPushButton();
    bouton3->setText("3");
    QPushButton *bouton4= new QPushButton();
    bouton4->setText("4");
    QPushButton *bouton5= new QPushButton();
    bouton5->setText("5");
    QPushButton *bouton6= new QPushButton();
    bouton6->setText("6");
    QPushButton *bouton7= new QPushButton();
    bouton7->setText("7");
    QPushButton *bouton8= new QPushButton();
    bouton8->setText("8");
    QPushButton *bouton9= new QPushButton();
    bouton9->setText("9");

    //Crée un layout contenant le clavier numérique
    layoutClavier->addWidget(bouton1, 0,0);
    layoutClavier->addWidget(bouton2, 0,1);
    layoutClavier->addWidget(bouton3, 0,2);
    layoutClavier->addWidget(bouton4, 1,0);
    layoutClavier->addWidget(bouton5, 1,1);
    layoutClavier->addWidget(bouton6, 1,2);
    layoutClavier->addWidget(bouton7, 2,0);
    layoutClavier->addWidget(bouton8, 2,1);
    layoutClavier->addWidget(bouton9, 2,2);

    //Crée un layout avec l'historique de commandes, la zone d'entrée et le clavier
    verticalLayout->addWidget(vueHistoriqueCommandes);
    verticalLayout->addWidget(inputLine);
    verticalLayout->addLayout(layoutClavier);

    //Assemble les layouts
    mainLayout->addWidget(vuePile);
    mainLayout->addLayout(verticalLayout);


    QWidget* tab1 = new QWidget();
    tab1->setLayout(mainLayout);
    tabWidget->addTab(tab1, "Principal");

    QObject::connect(inputLine, SIGNAL(textChanged(QString)), this, SLOT(interpreter(QString))) ;
    QObject::connect(inputLine,SIGNAL(returnPressed()), this, SLOT(returnPressedStr()));

    pile->setView(vuePile);









    //---------------------------------TAB2--------------------------------------------


    QHBoxLayout *layoutProgramme = new QHBoxLayout();
    QVBoxLayout *layoutEditionProgramme = new QVBoxLayout();
    QHBoxLayout *layoutBoutonsProgramme = new QHBoxLayout();

    listeProgrammes = new QListView();

    zoneProgramme = new QTextEdit();
    zoneIdentifiant = new QLineEdit();
    boutonValider = new QPushButton("Ajouter");
    boutonEffacer = new QPushButton("Effacer");
    boutonModifier = new QPushButton("Modifier");
    boutonSupprimer = new QPushButton("Supprimer");
    boutonSupprimer->setEnabled(false);
    boutonModifier->setEnabled(false);



   layoutBoutonsProgramme->addWidget(boutonValider);
   layoutBoutonsProgramme->addWidget(boutonEffacer);
   layoutBoutonsProgramme->addWidget(boutonModifier);
   layoutBoutonsProgramme->addWidget(boutonSupprimer);


   layoutEditionProgramme->addWidget(zoneProgramme);
   layoutEditionProgramme->addWidget(zoneIdentifiant);
   layoutEditionProgramme->addLayout(layoutBoutonsProgramme);

   layoutProgramme->addLayout(layoutEditionProgramme);
   layoutProgramme->addWidget(listeProgrammes);

   QWidget* tab2 = new QWidget();

   tab2->setLayout(layoutProgramme);

   tabWidget->addTab(tab2, "Programmes");



   QXmlStreamReader xmlReader;
   QFile fileProgramme("programmes.xml");
   fileProgramme.open(QFile::ReadOnly);
   xmlReader.setDevice(&fileProgramme);



   xmlReader.readNext();
   QString strIdentifiant;
   QString str;
   while(!xmlReader.atEnd() && !xmlReader.hasError()) {

           QXmlStreamReader::TokenType token = xmlReader.readNext();

           if(token == QXmlStreamReader::StartDocument) {
                   continue;
           }

           if(token == QXmlStreamReader::StartElement) {

                   if(xmlReader.name() == "identifiant") {
                           strIdentifiant= xmlReader.readElementText();
                   }

                   if(xmlReader.name() == "string") {
                        str= xmlReader.readElementText();
                        manager->insererProgramme(strIdentifiant, str);
                   }
           }
   }

   QStringList* listeProgrammesStr = manager->getListProgrammes();

   modeleProgrammes = new QStringListModel(*listeProgrammesStr, this);

   listeProgrammes->setEditTriggers(QAbstractItemView::NoEditTriggers);
   listeProgrammes->setModel(modeleProgrammes);



   fileProgramme.close();

   QObject::connect(boutonValider, SIGNAL(clicked(bool)), this, SLOT(ajouterProgramme()));
   QObject::connect(listeProgrammes, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(afficherProgrammeListe(QModelIndex)));
   QObject::connect(boutonEffacer, SIGNAL(clicked(bool)), this, SLOT(effacerChampsProgramme()));
   QObject::connect(boutonSupprimer, SIGNAL(clicked(bool)), this, SLOT(supprimerProgramme()));
   QObject::connect(boutonModifier, SIGNAL(clicked(bool)), this, SLOT(modifierProgramme()));




   //---------------------------------TAB3--------------------------------------------


   QHBoxLayout *layoutVariable = new QHBoxLayout();
   QVBoxLayout *layoutEditionVariable = new QVBoxLayout();
   QHBoxLayout *layoutBoutonsVariable = new QHBoxLayout();

   listeVariables = new QListView();

   zoneVariable = new QTextEdit();
   zoneIdentifiantVariable = new QLineEdit();
   boutonValiderVariable = new QPushButton("Ajouter");
   boutonEffacerVariable = new QPushButton("Effacer");
   boutonModifierVariable = new QPushButton("Modifier");
   boutonSupprimerVariable = new QPushButton("Supprimer");
   boutonSupprimerVariable->setEnabled(false);
   boutonModifierVariable->setEnabled(false);



  layoutBoutonsVariable->addWidget(boutonValiderVariable);
  layoutBoutonsVariable->addWidget(boutonEffacerVariable);
  layoutBoutonsVariable->addWidget(boutonModifierVariable);
  layoutBoutonsVariable->addWidget(boutonSupprimerVariable);


  layoutEditionVariable->addWidget(zoneVariable);
  layoutEditionVariable->addWidget(zoneIdentifiantVariable);
  layoutEditionVariable->addLayout(layoutBoutonsVariable);

  layoutVariable->addLayout(layoutEditionVariable);
  layoutVariable->addWidget(listeVariables);

  QWidget* tab3 = new QWidget();

  tab3->setLayout(layoutVariable);

  tabWidget->addTab(tab3, "Variables");



  QXmlStreamReader xmlReader2;
  QFile fileVariable("variables.xml");
  fileVariable.open(QFile::ReadOnly);
  xmlReader2.setDevice(&fileVariable);



  xmlReader2.readNext();

  while(!xmlReader2.atEnd() && !xmlReader2.hasError()) {

          QXmlStreamReader::TokenType token = xmlReader2.readNext();

          if(token == QXmlStreamReader::StartDocument) {
                  continue;
          }

          if(token == QXmlStreamReader::StartElement) {

                  if(xmlReader2.name() == "identifiant") {
                          strIdentifiant= xmlReader2.readElementText();
                  }

                  if(xmlReader2.name() == "string") {
                       str= xmlReader2.readElementText();
                       manager->insererVariable(strIdentifiant, str);
                  }
          }
  }

  QStringList* listeVariablesStr = manager->getListVariables();

  modeleVariables = new QStringListModel(*listeVariablesStr, this);

  listeVariables->setEditTriggers(QAbstractItemView::NoEditTriggers);
  listeVariables->setModel(modeleVariables);



  fileVariable.close();

  QObject::connect(boutonValiderVariable, SIGNAL(clicked(bool)), this, SLOT(ajouterVariable()));
  QObject::connect(listeVariables, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(afficherVariableListe(QModelIndex)));
  QObject::connect(boutonEffacerVariable, SIGNAL(clicked(bool)), this, SLOT(effacerChampsVariable()));
  QObject::connect(boutonSupprimerVariable, SIGNAL(clicked(bool)), this, SLOT(supprimerVariable()));
  QObject::connect(boutonModifierVariable, SIGNAL(clicked(bool)), this, SLOT(modifierVariable()));

  QObject::connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(updateTab(int)));


   setCentralWidget(tabWidget);


}



MainWindow::~MainWindow()
{

}

void MainWindow::interpreter(QString exp){
   if(manager->interpreter(exp))
    inputLine->clear();

}

void MainWindow::ajouterProgramme(){
    QMap<QString, QString>* mapProgramme=manager->getMapProgramme();
    QMapIterator<QString, QString> it(*mapProgramme);

    if(zoneIdentifiant->text()!="" && !mapProgramme->contains(zoneIdentifiant->text())){

        LitteraleProgramme newProgramme(zoneProgramme->toPlainText());




        manager->insererProgramme(zoneIdentifiant->text(), newProgramme.toString());


        modeleProgrammes->insertRow(modeleProgrammes->rowCount());
        QModelIndex index = modeleProgrammes->index(modeleProgrammes->rowCount()-1);
        modeleProgrammes->setData(index, zoneIdentifiant->text());



        manager->ecrireFichierProgramme(mapProgramme, zoneIdentifiant, zoneProgramme);

    }
    else{
        qDebug()<<"erreur ajout";

    }
 }



void MainWindow::afficherProgrammeListe(QModelIndex modelIndex){

    boutonSupprimer->setEnabled(true);
    boutonModifier->setEnabled(true);
    QMap<QString, QString>* mapProgramme=manager->getMapProgramme();
    zoneProgramme->setText(mapProgramme->value(manager->getListProgrammes()->at(modelIndex.row())));
    zoneIdentifiant->setText(manager->getListProgrammes()->at(modelIndex.row()));

}


void MainWindow::modifierProgramme(){
    QMap<QString, QString>* mapProgramme=manager->getMapProgramme();
    mapProgramme->remove(zoneIdentifiant->text());
    manager->insererProgramme(zoneIdentifiant->text(), zoneProgramme->toPlainText());

    manager->ecrireFichierProgramme(mapProgramme, zoneIdentifiant, zoneProgramme);
}


void MainWindow::supprimerProgramme(){
    boutonSupprimer->setEnabled(false);
    boutonModifier->setEnabled(false);
    QMap<QString, QString>* mapProgramme=manager->getMapProgramme();
    mapProgramme->remove(zoneIdentifiant->text());
    QStringList programmesStr= modeleProgrammes->stringList();
    int indexToDelete = programmesStr.indexOf(zoneIdentifiant->text());
    modeleProgrammes->removeRow(indexToDelete);

    manager->ecrireFichierProgramme(mapProgramme, zoneIdentifiant, zoneProgramme);

}

void MainWindow::effacerChampsProgramme(){
    zoneProgramme->clear();
    zoneIdentifiant->clear();
    boutonSupprimer->setDisabled(true);
}



void MainWindow::ajouterVariable(){

    QMap<QString, QString>* mapVariable=manager->getMapVariables();
    QMapIterator<QString, QString> it(*mapVariable);


    if(zoneIdentifiantVariable->text()!="" && !mapVariable->contains(zoneIdentifiantVariable->text())){

        manager->insererVariable(zoneIdentifiantVariable->text(), zoneVariable->toPlainText());


        modeleVariables->insertRow(modeleVariables->rowCount());
        QModelIndex index = modeleVariables->index(modeleVariables->rowCount()-1);
        modeleVariables->setData(index, zoneIdentifiantVariable->text());



        manager->ecrireFichierVariable(mapVariable, zoneIdentifiantVariable, zoneVariable );

    }
    else{
        qDebug()<<"erreur ajout";
        QMessageBox boiteErreur;
        boiteErreur.setText("Une variable à ce nom existe déja");
        boiteErreur.exec();
    }
 }



void MainWindow::afficherVariableListe(QModelIndex modelIndex){

    boutonSupprimerVariable->setEnabled(true);
    boutonModifierVariable->setEnabled(true);
    QMap<QString, QString>* mapVariable=manager->getMapVariables();
    zoneVariable->setText(mapVariable->value(manager->getListVariables()->at(modelIndex.row())));
    zoneIdentifiantVariable->setText(manager->getListVariables()->at(modelIndex.row()));

}


void MainWindow::modifierVariable(){
    QMap<QString, QString>* mapVariable=manager->getMapVariables();
    mapVariable->remove(zoneIdentifiantVariable->text());
    manager->insererVariable(zoneIdentifiantVariable->text(), zoneVariable->toPlainText());

    manager->ecrireFichierVariable(mapVariable, zoneIdentifiantVariable, zoneVariable );
}


void MainWindow::supprimerVariable(){
    boutonSupprimerVariable->setEnabled(false);
    boutonModifierVariable->setEnabled(false);
    QMap<QString, QString>* mapVariable=manager->getMapVariables();
    mapVariable->remove(zoneIdentifiantVariable->text());
    QStringList programmesStr= modeleVariables->stringList();
    int indexToDelete = programmesStr.indexOf(zoneIdentifiantVariable->text());
    modeleVariables->removeRow(indexToDelete);

    manager->ecrireFichierVariable(mapVariable, zoneIdentifiantVariable, zoneVariable );

}

void MainWindow::effacerChampsVariable(){
    zoneVariable->clear();
    zoneIdentifiantVariable->clear();
    boutonSupprimerVariable->setDisabled(true);
}





void MainWindow::returnPressedStr(){
    manager->executer(inputLine->text());
    inputLine->clear();
}

void MainWindow::updateTab(int index){
    if(index==1){
        delete modeleProgrammes;
        QStringList* listeProgrammesStr = manager->getListProgrammes();
        modeleProgrammes = new QStringListModel(*listeProgrammesStr, this);
        listeProgrammes->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listeProgrammes->setModel(modeleProgrammes);
    }
    else if(index==2){
        delete modeleVariables;
        QStringList* listeVariablesStr = manager->getListVariables();
        modeleVariables = new QStringListModel(*listeVariablesStr, this);
        listeVariables->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listeVariables->setModel(modeleVariables);
    }

}
