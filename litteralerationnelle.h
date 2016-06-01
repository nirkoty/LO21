#ifndef LITTERALERATIONNELLE_H
#define LITTERALERATIONNELLE_H

#include "litteralenumerique.h"
#include "litteraleentiere.h"

class LitteraleRationnelle : public LitteraleNumerique
{
public:
    LitteraleRationnelle(int s, LitteraleEntiere nom, LitteraleEntiere denom);
    LitteraleRationnelle(QString input);
    LitteraleEntiere getNominateur(){return nominateur;}
    LitteraleEntiere getDenominateur(){return denominateur;}
    QString toString();
    static bool estLitteraleRationnelle(QString bloc);
    Litterale* operator+(Litterale& lit2){}
    Litterale* operator*(Litterale& lit2){}
    Litterale* operator/(Litterale& lit2){}
    Litterale* operator-(Litterale& lit2){}

private:
    LitteraleEntiere nominateur;
    LitteraleEntiere denominateur;
};

#endif // LITTERALERATIONNELLE_H
