#ifndef LITTERALEREELLE_H
#define LITTERALEREELLE_H

#include "litterale.h"

class LitteraleReelle : public Litterale
{
public:
    LitteraleReelle(bool neg, double val);
    LitteraleReelle(QString exp);
    double getValeur() const {return valeur;}
    QString toString();
    static bool estLitteraleReelle(QString bloc);

private:
    double valeur;
};

#endif // LITTERALEREELLE_H
