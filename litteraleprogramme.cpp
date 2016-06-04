#include "litteraleprogramme.h"
#include "litteraleentiere.h"
#include "litteralerationnelle.h"
#include "litteralereelle.h"
#include "litteralecomplexe.h"
#include "operateur.h"
#include <QDebug>

LitteraleProgramme::LitteraleProgramme(QString input) : Litterale(), programme(input)
{
    /*if(input.left(1)=="[" && input.right(1)=="]"){

        input=input.remove(0,1);
        input=input.remove(input.length()-1,1);

        while(input.length()!=0){


            if(input.left(1)==" " || input.left(1)=="   " || input.left(1)=="\n"){
                input=input.remove(0,1);
            }


            else{
                if(input.left(1)!="["){
                    int nextSeparatorIndex=input.length();
                    if(input.indexOf(" ")<nextSeparatorIndex)
                        nextSeparatorIndex=input.indexOf(" ");
                    else if(input.indexOf(" ")<nextSeparatorIndex)
                        nextSeparatorIndex=input.indexOf("  ");
                    else if(input.indexOf("\n")<nextSeparatorIndex)
                            nextSeparatorIndex=input.indexOf("\n");


                    if(nextSeparatorIndex==-1)
                        nextSeparatorIndex=2;


                    QString exp = input.left(nextSeparatorIndex);

                    if(LitteraleReelle::estLitteraleReelle(exp))
                        operandes.push_back(new LitteraleReelle(exp));
                    else if(LitteraleEntiere::estLitteraleEntiere(exp))
                        operandes.push_back(new LitteraleEntiere(exp));
                    else if(Operateur::estOperateur(exp))
                        operandes.push_back(new Operateur(exp));
                    input=input.remove(0, nextSeparatorIndex);
                }
                else{

                    QString exp = input.left(input.lastIndexOf("]")+1);

                    if(LitteraleProgramme::estLitteraleProgramme(exp))
                        operandes.push_back(new LitteraleProgramme(exp));
                    input = input.remove(0, input.lastIndexOf("]")+1);

                }
            }
        }


    }*/


}

bool LitteraleProgramme::estLitteraleProgramme(QString bloc){
    if(bloc.at(0)!='[' || bloc.at(bloc.length()-1)!=']')
        return false;

    return true;
}

QString LitteraleProgramme::getStrProgramme(){
   return programme;

}

QString LitteraleProgramme::toString(){
    QString str=programme;
    str=str.remove(0,1);
    str=str.remove(str.length()-1,1);
    if(str.at(0)==' ')
        str=str.remove(0,1);

    return str;
}


Litterale* LitteraleProgramme::evaluer(){
    return this;
}
