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

MainWindow::MainWindow(Pile& pile, Manager *man, QWidget *parent) : QMainWindow(parent), manager(man)
{



    QHBoxLayout *mainLayout= new QHBoxLayout();
    QListView *vuePile = new QListView();
    vuePile->setGeometry(0,0,100,300);

    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QTextEdit *vueHistoriqueCommandes = new QTextEdit();
    inputLine = new QLineEdit();

    QTabWidget *tabWidget = new QTabWidget();


    QGridLayout *layoutClavier = new QGridLayout;


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


    layoutClavier->addWidget(bouton1, 0,0);
    layoutClavier->addWidget(bouton2, 0,1);
    layoutClavier->addWidget(bouton3, 0,2);
    layoutClavier->addWidget(bouton4, 1,0);
    layoutClavier->addWidget(bouton5, 1,1);
    layoutClavier->addWidget(bouton6, 1,2);
    layoutClavier->addWidget(bouton7, 2,0);
    layoutClavier->addWidget(bouton8, 2,1);
    layoutClavier->addWidget(bouton9, 2,2);

    verticalLayout->addWidget(vueHistoriqueCommandes);
    verticalLayout->addWidget(inputLine);
    verticalLayout->addLayout(layoutClavier);



    mainLayout->addWidget(vuePile);
    mainLayout->addLayout(verticalLayout);

    //QWidget *zoneCentrale = new QWidget;
    //zoneCentrale->setLayout(mainLayout);

    QWidget* tab1 = new QWidget();
    tab1->setLayout(mainLayout);
    tabWidget->addTab(tab1, "Principal");

    QObject::connect(inputLine, SIGNAL(textChanged(QString)), this, SLOT(interpreter(QString))) ;

    pile.setView(vuePile);









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



        ecrireFichierProgramme();

    }
    else{
        qDebug()<<"erreur ajout";
        QMessageBox boiteErreur;
        boiteErreur.setText("Un programme à ce nom existe déja");
        boiteErreur.exec();
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

    ecrireFichierProgramme();
}


void MainWindow::supprimerProgramme(){
    boutonSupprimer->setEnabled(false);
    boutonModifier->setEnabled(false);
    QMap<QString, QString>* mapProgramme=manager->getMapProgramme();
    mapProgramme->remove(zoneIdentifiant->text());
    QStringList programmesStr= modeleProgrammes->stringList();
    int indexToDelete = programmesStr.indexOf(zoneIdentifiant->text());
    modeleProgrammes->removeRow(indexToDelete);

    ecrireFichierProgramme();

}

void MainWindow::effacerChampsProgramme(){
    zoneProgramme->clear();
    zoneIdentifiant->clear();
    boutonSupprimer->setDisabled(true);
}

void MainWindow::ecrireFichierProgramme(){


    QMap<QString, QString>* mapProgramme=manager->getMapProgramme();
    QMapIterator<QString, QString> it(*mapProgramme);

    QString path("programmes.xml");
    QFile file(path);
    file.open(QFile::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setAutoFormattingIndent(2);
    xmlWriter.writeStartDocument();




    xmlWriter.writeStartElement("programmes");
    while(it.hasNext()){

        it.next();
        xmlWriter.writeStartElement("programme");
        xmlWriter.writeTextElement("identifiant",it.key());
        xmlWriter.writeTextElement("string", it.value());
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    zoneIdentifiant->clear();
    zoneProgramme->clear();
}
