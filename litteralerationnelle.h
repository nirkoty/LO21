#ifndef LITTERALERATIONNELLE_H
#define LITTERALERATIONNELLE_H

#include "litteralenumerique.h"
#include "litteraleentiere.h"

class LitteraleRationnelle : public LitteraleNumerique
{
private:
    LitteraleEntiere numerateur; // pourquoi ne pas utiliser des unsigned int plutôt que des litterales entieres ? Le signe est attribué à la fraction , le denominateur et le nominateur ne doivent pas être signés
    LitteraleEntiere denominateur;

public:
    LitteraleRationnelle(int s, LitteraleEntiere nom, LitteraleEntiere denom);
    LitteraleRationnelle(QString input);
    LitteraleEntiere getNumerateur(){return numerateur;}
    LitteraleEntiere getDenominateur(){return denominateur;}
    void simplifier();
    //LitteraleReelle toReelle();
    QString toString();
    static bool estLitteraleRationnelle(QString bloc);
    Litterale* operator+(Litterale& lit2);
    Litterale* operator*(Litterale& lit2);
    Litterale* operator/(Litterale& lit2);
    Litterale* operator-(Litterale& lit2);

};

#endif // LITTERALERATIONNELLE_H
