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
    qDebug()<<"coucou";

    QApplication a(argc, argv);
    Manager *manager = new Manager();
    MainWindow w(manager);
    w.show();

    return a.exec();
}
