#ifndef LITTERALEPROGRAMME_H
#define LITTERALEPROGRAMME_H


#include "QString"
#include "operande.h"
#include <vector>
#include "litterale.h"

class LitteraleProgramme : public Litterale
{
public:
    LitteraleProgramme(QString programme);
    bool static estLitteraleProgramme(QString bloc);
    QString toString();

private:
    std::vector<Operande*> operandes;
    int nbOperandes;

};

#endif // LITTERALEPROGRAMME_H
