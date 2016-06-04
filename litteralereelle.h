#ifndef LITTERALEREELLE_H
#define LITTERALEREELLE_H

#include "litteralenumerique.h"

class LitteraleReelle : public LitteraleNumerique
{
private:
    double valeur;
public:
    LitteraleReelle(int s, double val);
    LitteraleReelle(QString exp);
    LitteraleReelle(){}
    double getValeur() const {return valeur;}
    QString toString();
    static bool estLitteraleReelle(QString bloc);
    Litterale* operator+(Litterale& lit2);
    Litterale* operator*(Litterale& lit2);
    Litterale* operator/(Litterale& lit2);
    Litterale* operator-(Litterale& lit2);
};


#endif // LITTERALEREELLE_H
