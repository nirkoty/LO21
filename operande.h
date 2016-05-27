#ifndef OPERANDE_H
#define OPERANDE_H


#include <QString>

class Operande
{
public:
    Operande();
    //virtual bool estValide() =0;
    virtual QString toString()=0;
};

#endif // OPERANDE_H
