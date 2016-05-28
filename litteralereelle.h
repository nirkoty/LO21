#ifndef LITTERALEREELLE_H
#define LITTERALEREELLE_H

#include "litterale.h"

class LitteraleReelle : public Litterale
{
public:
    LitteraleReelle(int s, double val);
    LitteraleReelle(QString exp);
    double getValeur() const {return valeur;}
    QString toString();
    static bool estLitteraleReelle(QString bloc);
    Litterale* operator+(Litterale& lit2){}

private:
    double valeur;
};

#endif // LITTERALEREELLE_H
