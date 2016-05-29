#include "litteralerationnelle.h"
#include "litteraleentiere.h"
#include "QDebug"


LitteraleRationnelle::LitteraleRationnelle(int s, LitteraleEntiere nom, LitteraleEntiere denom) : LitteraleNumerique(s), nominateur(nom), denominateur(denom)
{

}



QString LitteraleRationnelle::toString(){
    QString q = "coucou";
    return q;
 }


bool LitteraleRationnelle::estLitteraleRationnelle(QString bloc){
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
