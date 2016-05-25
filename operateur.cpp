#include "operateur.h"

Operateur::Operateur(QString op) : type(op)
{
    if(type=="+" || type=="-" || type=="*" || type=="/")
        arite=2;
}


bool Operateur::estOperateur(QString type){
    return (type=="+" || type=="-" || type=="*" || type=="/");
}
