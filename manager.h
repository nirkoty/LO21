#ifndef MANAGER_H
#define MANAGER_H


#include <QString>
#include "litteraleprogramme.h"
#include "litteraleentiere.h"
#include "litteralereelle.h"
#include "pile.h"
#include <vector>
#include "operateur.h"
#include <QDebug>
#include <QObject>
#include <QMap>

class Manager : public QObject
{

public:
    Manager(Pile& p);
    bool interpreter(QString input);
    void executer(QString input);
    QMap<QString, QString>* getMapProgramme() const {return mapProgramme;}
    void insererProgramme(QString id, QString str);
    QStringList* getListProgrammes() const{return stringListProgrammes;}
    void supprimerProgramme(QString id);
    bool estLitteraleAtome(QString input) const;
    Litterale* getAtome(QString input);

private:
    Pile& pile;
    QMap<QString, QString>* mapProgramme;
    QStringList *stringListProgrammes;


};

#endif // MANAGER_H
