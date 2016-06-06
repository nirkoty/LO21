#ifndef LITTERALE_H
#define LITTERALE_H

#include <QString>
#include "operande.h"

class Litterale : public Operande
{
public:
    Litterale();
    virtual Litterale* operator+(Litterale& lit2) = 0;
    virtual Litterale* operator*(Litterale& lit2) = 0;
    virtual Litterale* operator-(Litterale& lit2) = 0;
    virtual Litterale* operator/(Litterale& lit2) = 0;
};

#endif // LITTERALE_H
