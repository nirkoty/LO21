#ifndef LITTERALEENTIERE_H
#define LITTERALEENTIERE_H

#include "QString"
#include "litterale.h"

class LitteraleEntiere :  public Litterale
{
public:
    LitteraleEntiere();
    LitteraleEntiere(int s, int val);
    LitteraleEntiere(QString exp);
    int getValeur() const {return valeur;}
    QString toString();
    static bool estLitteraleEntiere(QString bloc);
    Litterale* operator+(Litterale& lit2);
    Litterale* operator*(Litterale& lit2);
    Litterale* operator/(Litterale& lit2);
    Litterale* operator-(Litterale& lit2);


private:
    int valeur;
};

#endif // LITTERALEENTIERE_H
