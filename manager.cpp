#include "manager.h"
#include <typeinfo>

Manager::Manager(Pile &p) : pile(p), mapProgramme(new QMap<QString, QString>), stringListProgrammes(new QStringList)
{
}


bool Manager::interpreter(QString input){

    QStringList litteralesStr = input.split(" ");
    std::vector<Litterale*>litterales;
    if(input.right(1)=="+" || input.right(1)=="-" || input.right(1)=="*" || input.right(1)=="/" ){
        for(unsigned int i=0; i<litteralesStr.size(); i++){

            if(LitteraleReelle::estLitteraleReelle(litteralesStr.at(i)))
                pile.empiler(new LitteraleReelle(litteralesStr.at(i)));
            else if (LitteraleEntiere::estLitteraleEntiere(litteralesStr.at(i)))
                pile.empiler(new LitteraleEntiere(litteralesStr.at(i)));
            else if (Operateur::estOperateur(litteralesStr.at(i))){
                executer(Operateur(litteralesStr.at(i)));
                return true;
            }
        }
    }
    else
        return false;
}

void Manager::executer(Operateur operateur){
    std::vector<Litterale*> litterales;
    qDebug()<<pile.taille();
    for(unsigned int i=0; i<operateur.getArite(); i++){
        litterales.push_back(pile.depiler());
    }

    if(operateur.getType()=="+"){
        qDebug()<<typeid(*litterales.at(0)).name();

        Litterale* newLit = *litterales.at(0)+*litterales.at(1);

        pile.empiler(newLit);
    }
    delete litterales.at(0);
    delete litterales.at(1);
}

void Manager::insererProgramme(QString id, QString str){
    mapProgramme->insert(id, str);
    stringListProgrammes->append(id);
}


void Manager::supprimerProgramme(QString id){
    mapProgramme->remove(id);
    stringListProgrammes->removeOne(id);
}
