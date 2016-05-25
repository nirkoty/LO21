#include "mainwindow.h"
#include "litteraleentiere.h"
#include "litteralereelle.h"
#include "litteralerationnelle.h"
#include "manager.h"
#include "litteralecomplexe.h"
#include "pile.h"
#include <QApplication>
#include <iostream>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pile pile;
    Manager *manager = new Manager(pile);
    MainWindow w(pile, manager);
    w.show();


     //qDebug()<<LitteraleReelle::estLitteraleReelle("63.");
    //qDebug()<<LitteraleComplexe::estLitteraleComplexe("2$2.2");

    return a.exec();
}
