#ifndef LITTERALE_H
#define LITTERALE_H

#include <QString>
#include "operande.h"

class Litterale : public Operande
{

public:
    Litterale();
    Litterale(int s);
    int getSigne(){return signe;}
    virtual Litterale* operator+(Litterale& lit2) = 0;

protected:
    int signe;
};

#endif // LITTERALE_H
