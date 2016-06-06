#ifndef MANAGER_H
#define MANAGER_H


#include <QString>
#include "litteraleprogramme.h"
#include "litteraleentiere.h"
#include "litteralereelle.h"
#include "pile.h"
#include <vector>
#include <QDebug>
#include <QObject>
#include <QMap>
#include <QFile>
#include <QXmlStreamWriter>
#include "computerexception.h"

class Manager : public QObject
{

public:
    Manager();
    bool interpreter(QString input);
    void executer(QString input);
    QMap<QString, QString>* getMapProgramme() const {return mapProgramme;}
    QMap<QString, QString>* getMapVariables() const {return mapVariable;}
    void insererProgramme(QString id, QString str);
    void insererVariable(QString id, QString str);
    QStringList* getListProgrammes() const{return stringListProgrammes;}
    QStringList* getListVariables() const{return stringListVariables;}
    void supprimerProgramme(QString id);
    void supprimerVariable(QString id);
    bool estLitteraleAtome(QString input) const;
    Litterale* getAtome(QString input);
    void operer(QString op);
    int getArite(QString op);
    static bool estUnOperateur(QString op);

    void ecrireFichierVariable(QMap<QString, QString>* mapVariable, QLineEdit* zoneIdentifiantVariable=0, QTextEdit* zoneVariable=0);
    void ecrireFichierProgramme(QMap<QString, QString>* mapVariable, QLineEdit* zoneIdentifiant=0, QTextEdit* zoneProgramme=0);

    Pile* getPile(){return pile;}

private:
    Pile* pile;
    QMap<QString, QString>* mapProgramme;
    QMap<QString, QString>* mapVariable;
    QStringList *stringListProgrammes;
    QStringList *stringListVariables;
    QString lastOp;



};

#endif // MANAGER_H
