#include "litteralecomplexe.h"
#include "litteralerationnelle.h"
#include "litteralereelle.h"
#include "litteraleentiere.h"
#include "QStringList"
#include <QDebug>

LitteraleComplexe::LitteraleComplexe(LitteraleNumerique* re, LitteraleNumerique* im) : partieReelle(re), partieImaginaire(im){}

LitteraleComplexe::LitteraleComplexe(QString input){

    QStringList elements = input.split("$");
    qDebug()<<elements.at(0);
    if (LitteraleEntiere::estLitteraleEntiere(elements.at(0))) partieReelle = new LitteraleEntiere(elements.at(0));
    else if (LitteraleReelle::estLitteraleReelle(elements.at(0))) partieReelle = new LitteraleReelle(elements.at(0));
    else if (LitteraleRationnelle::estLitteraleRationnelle(elements.at(0))) partieReelle = new LitteraleRationnelle(elements.at(0));

    if (LitteraleEntiere::estLitteraleEntiere(elements.at(1))) partieImaginaire = new LitteraleEntiere(elements.at(1));
    else if (LitteraleReelle::estLitteraleReelle(elements.at(1))) partieImaginaire = new LitteraleReelle(elements.at(1));
    else if (LitteraleRationnelle::estLitteraleRationnelle(elements.at(1))) partieImaginaire = new LitteraleRationnelle(elements.at(1));

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
    if (partieImaginaire->getSigne() == -1)    return(partieReelle->toString()+"-"+partieImaginaire->toString()+"i");
    if (partieImaginaire->getSigne() == 1)    return(partieReelle->toString()+"+"+partieImaginaire->toString()+"i");

}
