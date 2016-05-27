#ifndef OPERATEUR_H
#define OPERATEUR_H


#include "QString"
#include "operande.h"

class Operateur : public Operande
{
public:
    Operateur(QString op);
    QString getType() const {return type;}
    int getArite() const {return arite;}
    static bool estOperateur(QString type);
    QString toString(){return type;}

private:
    QString type;
    int arite;
};

#endif // OPERATEUR_H
