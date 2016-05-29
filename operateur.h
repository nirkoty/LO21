#ifndef OPERATEUR_H
#define OPERATEUR_H


#include "QString"
#include "operande.h"
#include "litterale.h"
#include "pile.h"

class Operateur : public Operande
{
public:
    Operateur(QString op, Pile* p);
    QString getType() const {return type;}
    int getArite() const {return arite;}
    static bool estOperateur(QString type);
    QString toString(){return type;}
    void executer();

private:
    QString type;
    int arite;
    Pile* pile;

};

#endif // OPERATEUR_H
