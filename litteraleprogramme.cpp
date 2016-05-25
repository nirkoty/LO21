#include "litteraleprogramme.h"
#include "litteraleentiere.h"
#include "litteralerationnelle.h"
#include "litteralereelle.h"
#include "litteralecomplexe.h"
#include "operateur.h"

LitteraleProgramme::LitteraleProgramme(QString programme) : Litterale()
{
    nbOperandes=0;
    QString exp;
    programme = programme.remove(0,1).remove(programme.length()-1,1); //enlève [ et ]
    /*for(unsigned int i=0; i< programme.count(' ')+1; i++){
        exp = programme.section(programme, ' ', 0, 0);
        programme = programme.section(programme, 1);
        if(Operateur::estOperateur(exp))
            operandes[i]=Operateur(exp);
        else if(LitteraleComplexe::estLitteraleComplexe(exp))
            operandes[i]=LitteraleComplexe(exp);
        else if(LitteraleRationnelle::estLitteraleRationnelle(exp))
            operandes[i]=LitteraleRationnelle(exp);
        else if(LitteraleReelle::estLitteraleReelle(exp))
            operandes[i]=LitteraleReelle(exp);
        else if(LitteraleEntiere::estLitteraleEntiere(exp))
            operandes[i]=LitteraleEntiere(exp);
        else throw Exception("type non valide");
        nbOperandes++;
    }*/
}

bool LitteraleProgramme::estLitteraleProgramme(QString bloc){
    if(bloc.at(0)!='[' || bloc.at(bloc.length()-1)!=']')
        return false;

    return true;
}

QString LitteraleProgramme::toString(){

}
