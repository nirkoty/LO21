#ifndef LITTERALEENTIERE_H
#define LITTERALEENTIERE_H

#include "QString"
#include "litterale.h"

class LitteraleEntiere :  public Litterale
{
public:
    LitteraleEntiere();
    LitteraleEntiere(bool neg, int val);
    int getValeur() const {return valeur;}
    QString toString();
    static bool estLitteraleEntiere(QString bloc);

private:
    int valeur;
};

#endif // LITTERALEENTIERE_H
