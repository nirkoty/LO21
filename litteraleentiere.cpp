#include "litteraleentiere.h"
#include <typeinfo>

LitteraleEntiere::LitteraleEntiere(bool neg, int val) : Litterale(neg), valeur(val)
{

}

QString LitteraleEntiere::toString(){

}


bool LitteraleEntiere::estLitteraleEntiere(QString bloc){
     return bloc.toInt();
}

