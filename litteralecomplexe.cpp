#include "litteralecomplexe.h"
#include "litteralerationnelle.h"
#include "litteralereelle.h"
#include "litteraleentiere.h"
#include "QStringList"

LitteraleComplexe::LitteraleComplexe(int s, LitteraleEntiere re, LitteraleEntiere im) : LitteraleNumerique(s), partieRelle(re), partieImaginaire(im)
{

}

LitteraleComplexe::LitteraleComplexe(QString input){
    if(input.left(1)=="-"){
        signe=-1;
        input=input.remove(0,1);
    }
    QStringList elements = input.split("$");
    partieRelle= LitteraleEntiere(elements.at(0));
    partieImaginaire = LitteraleEntiere(elements.at(1));
}

bool LitteraleComplexe::estLitteraleComplexe(QString bloc){
    if(bloc.indexOf('$')==-1)
        return false;

    QString strRe =  bloc.section('$', 0, 0);
    QString strIm =  bloc.section('$', 1, 1);

    bool ok = true;
    if(!LitteraleEntiere::estLitteraleEntiere(strRe) && !LitteraleReelle::estLitteraleReelle(strRe) && !LitteraleRationnelle::estLitteraleRationnelle(strRe))
        return false;
    if(!LitteraleEntiere::estLitteraleEntiere(strIm) && !LitteraleReelle::estLitteraleReelle(strIm) && !LitteraleRationnelle::estLitteraleRationnelle(strIm))
        return false;

    return true;
}


QString LitteraleComplexe::toString(){
    if(signe==1)
        return(partieRelle.toString()+"+"+partieImaginaire.toString()+"i");
    else
        return("-"+partieRelle.toString()+"+"+partieImaginaire.toString()+"i");
}
