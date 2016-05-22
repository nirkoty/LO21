#ifndef LITTERALE_H
#define LITTERALE_H

#include "QString"
#include "operande.h"

class Litterale : public Operande
{

public:
    Litterale();
    Litterale(bool neg);
    bool estNegative(){return negative;}
    //virtual QString toString() = 0;

private:
    bool negative;
};

#endif // LITTERALE_H
