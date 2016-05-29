#include "operateur.h"
#include "litteralenumerique.h"

Operateur::Operateur(QString op, Pile *p) : type(op), pile(p)
{
    if(type=="+" || type=="-" || type=="*" || type=="/")
        arite=2;
    if(type=="NEG")
        arite=1;
}


bool Operateur::estOperateur(QString type){
    return (type=="+" || type=="-" || type=="*" || type=="/" || type=="NEG");
}

void Operateur::executer(){
    std::vector<LitteraleNumerique*> litterales;
    qDebug()<<pile->taille();
    for(unsigned int i=0; i<arite; i++){
        litterales.push_back(dynamic_cast<LitteraleNumerique*> (pile->depiler()));
    }

    Litterale* newLit;


    if(type=="+")
        newLit = *litterales.at(0)+ *litterales.at(1);
    else if(type=="*")
        newLit = *litterales.at(0)*(*litterales.at(1));
    else if(type=="-")
        newLit = *litterales.at(0)-*litterales.at(1);
    else if(type=="/")
        newLit = *litterales.at(0)/(*litterales.at(1));

    else if(type=="NEG"){
        //newLit =
    }

    pile->empiler(newLit);

    for(unsigned int i=0; i<arite; i++){
         delete litterales.at(i);
    }


}
