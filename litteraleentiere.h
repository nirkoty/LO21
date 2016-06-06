#ifndef LITTERALEENTIERE_H
#define LITTERALEENTIERE_H

#include "QString"
#include "litteralenumerique.h"

class LitteraleEntiere :  public LitteraleNumerique
{

private:
    unsigned int valeur;

public:
    LitteraleEntiere();
    LitteraleEntiere(int s, unsigned int val);
    LitteraleEntiere(QString exp);
    unsigned int getValeur() const {return valeur;}
    QString toString();
    static bool estLitteraleEntiere(QString bloc);
    Litterale* operator+(Litterale& lit2);
    Litterale* operator*(Litterale& lit2);
    Litterale* operator/(Litterale& lit2);
    Litterale* operator-(Litterale& lit2);


};

#endif // LITTERALEENTIERE_H
