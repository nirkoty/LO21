#ifndef LITTERALECOMPLEXE_H
#define LITTERALECOMPLEXE_H


#include "litteralereelle.h"
#include "litteralenumerique.h"
#include "litteraleentiere.h"

class LitteraleComplexe : public Litterale
{
public:
    LitteraleComplexe(LitteraleNumerique* re, LitteraleNumerique* im);
    LitteraleComplexe(QString input);
    LitteraleNumerique* getReelle() const {return partieReelle;}
    LitteraleNumerique* getImaginaire() const {return partieImaginaire;}
    QString toString();
    static bool estLitteraleComplexe(QString bloc);
    Litterale* operator+(Litterale& lit2);
    Litterale* operator*(Litterale& lit2);
    Litterale* operator/(Litterale& lit2);
    Litterale* operator-(Litterale& lit2);

private :
    LitteraleNumerique* partieReelle;
    LitteraleNumerique* partieImaginaire;

};

#endif // LITTERALECOMPLEXE_H
