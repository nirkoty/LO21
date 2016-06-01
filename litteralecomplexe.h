#ifndef LITTERALECOMPLEXE_H
#define LITTERALECOMPLEXE_H


#include "litteralereelle.h"
#include "litteralenumerique.h"
#include "litteraleentiere.h"

class LitteraleComplexe : public LitteraleNumerique
{
public:
    LitteraleComplexe(int s, LitteraleEntiere re, LitteraleEntiere im);
    LitteraleComplexe(QString input);
    LitteraleEntiere getReelle() const {return partieRelle;}
    LitteraleEntiere getImaginaire() const {return partieImaginaire;}
    QString toString();
    static bool estLitteraleComplexe(QString bloc);
    Litterale* operator+(Litterale& lit2){}
    Litterale* operator*(Litterale& lit2){}
    Litterale* operator/(Litterale& lit2){}
    Litterale* operator-(Litterale& lit2){}

private :
    LitteraleEntiere partieRelle;
    LitteraleEntiere partieImaginaire;
};

#endif // LITTERALECOMPLEXE_H
