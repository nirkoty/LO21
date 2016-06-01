#include "litteralerationnelle.h"
#include "litteraleentiere.h"
#include "QDebug"


LitteraleRationnelle::LitteraleRationnelle(int s, LitteraleEntiere nom, LitteraleEntiere denom) : LitteraleNumerique(s), nominateur(nom), denominateur(denom)
{

}

LitteraleRationnelle::LitteraleRationnelle(QString input){
    if(input.left(1)=="-"){
        signe=1;
        input=input.remove(0,1);
    }
    QStringList reels = input.split("/");
    qDebug()<<reels.at(0);
    qDebug()<<reels.at(1);
    nominateur=LitteraleEntiere(reels.at(0));
    denominateur=LitteraleEntiere(reels.at(1));
}



QString LitteraleRationnelle::toString(){
    if(signe==1)
        return QString(nominateur.toString()+"/"+denominateur.toString());
    else
        return QString("-"+nominateur.toString()+"/"+denominateur.toString());
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
