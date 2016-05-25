#ifndef LITTERALEPROGRAMME_H
#define LITTERALEPROGRAMME_H


#include "QString"
#include "operande.h"
#include "litterale.h"

class LitteraleProgramme : public Litterale
{
public:
    LitteraleProgramme(QString programme);
    bool static estLitteraleProgramme(QString bloc);
    QString toString();

private:
    //Operande operandes[];
    int nbOperandes;

};

#endif // LITTERALEPROGRAMME_H
