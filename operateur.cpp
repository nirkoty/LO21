#include "operateur.h"

Operateur::Operateur()
{

}


bool Operateur::estOperateur(QString type){
    return (type=="+" || type=="-" || type=="*" || type="/");
}
