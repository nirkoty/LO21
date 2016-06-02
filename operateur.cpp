#include "operateur.h"
#include "litteralenumerique.h"
#include "litteralecomplexe.h"

Operateur::Operateur(QString op, Pile* p) : type(op), pile(p)
{
    if(type=="+" || type=="-" || type=="*" || type=="/" || type=="$")
        arite=2;
    if(type=="NEG" || type=="DUP" || type=="DROP")
        arite=1;
}


bool Operateur::estOperateur(QString type){
    return (type=="+" || type=="-" || type=="*" || type=="/" || type=="$" || type=="DUP" || type=="DROP" || type=="SWAP" || type=="LASTOP"
            || type=="CLEAR" || type=="UNDO" || type=="REDO");
}

void Operateur::executer(){
    std::vector<LitteraleNumerique*> litterales;
    qDebug()<<pile->taille();

    /*if(type !="DUP" && type!="SWAP" && type!="LASTOP" && type!="CLEAR" && type=="UNDO" && type=="REDO"){
        for(unsigned int i=0; i<arite; i++){
            Litterale* tmp = pile->depiler();

            if(dynamic_cast<LitteraleNumerique*> (tmp))
                litterales.push_back(tmp);
            else{

                litterales.push_back(dynamic_cast<LitteraleNumerique*> (pile->depiler()));
            }

        }

        pile->setLastArgs(litterales);
    }*/


    Litterale* newLit;


    if(type=="+")
        newLit = *litterales.at(0)+ *litterales.at(1);
    else if(type=="*")
        newLit = *litterales.at(0)*(*litterales.at(1));
    else if(type=="-")
        newLit = *litterales.at(0)-*litterales.at(1);
    else if(type=="/")
        newLit = *litterales.at(0)/(*litterales.at(1));
    else if(type=="$"){
        LitteraleEntiere *lit1 = dynamic_cast<LitteraleEntiere*> (litterales.at(0));
        LitteraleEntiere *lit2 = dynamic_cast<LitteraleEntiere*> (litterales.at(1));
        newLit = new LitteraleComplexe(1, *lit2, *lit1);
    }

    else if(type=="NEG"){
        //newLit =
        pile->savePile();
    }
    else if(type=="DUP"){
        pile->dupliquer();
        pile->savePile();
    }
    else if(type=="SWAP"){
        pile->swap();
        pile->savePile();

    }
    else if(type=="CLEAR"){
        pile->clear();
        pile->savePile();
    }
    else if(type=="UNDO"){
        pile->undo();
    }
    else if(type=="REDO"){
        pile->redo();
    }


    if(type!="DUP" && type!="DROP" && type!="SWAP" && type!="CLEAR" && type!="UNDO" && type!="REDO"){
     pile->empiler(newLit);
        for(unsigned int i=0; i<arite; i++){
             delete litterales.at(i);
        }
    }



}
