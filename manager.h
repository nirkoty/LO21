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

class Manager : public QObject
{

public:
    Manager(Pile& p);
    bool interpreter(QString input);
    void executer(Operateur operateur);

private:
    Pile& pile;


};

#endif // MANAGER_H
