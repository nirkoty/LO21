#include "litteralereelle.h"
#include "litteraleentiere.h"
#include <QtDebug>

LitteraleReelle::LitteraleReelle(bool neg, double nom, double denom) : Litterale(neg), nominateur(nom), denominateur(denom)
{

}

QString LitteraleReelle::toString(){

}

bool LitteraleReelle::estLitteraleReelle(QString bloc){
    if(bloc.indexOf('/')!=-1){
        if(bloc.indexOf('-')!=-1)
            bloc = bloc.remove('-');

        QString strNominateur =  bloc.section('/', 0, 0);
        QString strDenominateur =  bloc.section('/', 1, 1);


        qDebug() <<bloc << strNominateur << strDenominateur;
        return (LitteraleEntiere::estLitteraleEntiere(strNominateur) && LitteraleEntiere::estLitteraleEntiere(strDenominateur));

    }
    else
        return false;

}
