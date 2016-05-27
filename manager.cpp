#include "manager.h"

Manager::Manager(Pile &p) : pile(p), mapProgramme(new QMap<QString, QString>), stringListProgrammes(new QStringList)
{
}


bool Manager::interpreter(QString input){

    QStringList litteralesStr = input.split(" ");
    std::vector<Litterale*>litterales;
    for(unsigned int i=0; i<litteralesStr.size(); i++){
        if(LitteraleReelle::estLitteraleReelle(litteralesStr.at(i)))
            litterales.push_back(new LitteraleReelle(litteralesStr.at(i)));
        else if (LitteraleEntiere::estLitteraleEntiere(litteralesStr.at(i)))
            litterales.push_back(new LitteraleEntiere(litteralesStr.at(i)));
    }

}

void Manager::executer(Operateur operateur){
    std::vector<Litterale*> litterales;
    for(unsigned int i=0; i<operateur.getArite(); i++){
    }
}

void Manager::insererProgramme(QString id, QString str){
    mapProgramme->insert(id, str);
    stringListProgrammes->append(id);
}
