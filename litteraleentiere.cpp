#include "litteraleentiere.h"
#include <typeinfo>

LitteraleEntiere::LitteraleEntiere(bool neg, int val) : Litterale(neg), valeur(val)
{

}

LitteraleEntiere::LitteraleEntiere(QString exp){
    if(exp.at(0)=='-'){
        negative=true;
        exp.remove(0,1);
    }
    valeur=exp.toInt();
}

QString LitteraleEntiere::toString(){
    return QString::number(valeur);
}


bool LitteraleEntiere::estLitteraleEntiere(QString bloc){
     return bloc.toInt();
}

