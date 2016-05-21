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

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{



    QHBoxLayout *mainLayout= new QHBoxLayout();
    QListView *vuePile = new QListView();
    vuePile->setGeometry(0,0,100,300);

    QVBoxLayout *verticalLayout = new QVBoxLayout();
    QListView *vueHistoriqueCommandes = new QListView();
    QLineEdit *inputLine = new QLineEdit();


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

    QWidget *zoneCentrale = new QWidget;
    zoneCentrale->setLayout(mainLayout);

        setCentralWidget(zoneCentrale);


}

MainWindow::~MainWindow()
{

}
