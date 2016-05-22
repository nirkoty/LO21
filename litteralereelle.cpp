#include "litteralereelle.h"
#include "litteraleentiere.h"
#include <QtDebug>

LitteraleReelle::LitteraleReelle(bool neg, double val) : Litterale(neg), valeur(val)
{

}

QString LitteraleReelle::toString(){

}

bool LitteraleReelle::estLitteraleReelle(QString bloc){
    if(bloc.indexOf('.')==-1)
        return false;

    QString strEntiere =  bloc.section('.', 0, 0);
    QString strDecimale =  bloc.section('.', 1, 1);


    if((LitteraleEntiere::estLitteraleEntiere(strEntiere) || (strEntiere.length()==0 && strDecimale.length()>0)) &&
            (LitteraleEntiere::estLitteraleEntiere(strDecimale)  || (strDecimale.length()==0 && strEntiere.length()==0)))
        return true;
    else
        return false;
}
