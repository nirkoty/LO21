#include "manager.h"
#include "litteraleexpression.h"
#include <typeinfo>

Manager::Manager(Pile &p) : pile(p), mapProgramme(new QMap<QString, QString>), stringListProgrammes(new QStringList)
{
}


bool Manager::interpreter(QString input){

   if(input.right(1)=="+" || input.right(1)=="-" || input.right(1)=="*" || input.right(1)=="/" || input.right(1)=="$"){
        executer(input);
        return true;
   }
   return false;

}

/*void Manager::executer(Operateur operateur){
    std::vector<Litterale*> litterales;
    qDebug()<<pile.taille();
    for(unsigned int i=0; i<operateur.getArite(); i++){
        litterales.push_back(pile.depiler());
    }

    Litterale* newLit;


    if(operateur.getType()=="+")
        newLit = *litterales.at(0)+*litterales.at(1);
    else if(operateur.getType()=="*")
        newLit = *litterales.at(0)*(*litterales.at(1));
    else if(operateur.getType()=="-")
        newLit = *litterales.at(0)-*litterales.at(1);
    else if(operateur.getType()=="/")
        newLit = *litterales.at(0)/(*litterales.at(1));

    pile.empiler(newLit);

    delete litterales.at(0);
    delete litterales.at(1);
}*/

void Manager::executer(QString input){

    QString tmp;
    while(input.length()>0){
        qDebug()<<input;
        tmp = input.left(input.indexOf(" "));
        qDebug()<<"tmp "<<tmp;
        if(input.indexOf(" ")!=-1)
            input=input.remove(0, input.indexOf(" ")+1);
        else
            input="";

        if(LitteraleReelle::estLitteraleReelle(tmp))
            pile.empiler(new LitteraleReelle(tmp));
        else if (LitteraleEntiere::estLitteraleEntiere(tmp))
            pile.empiler(new LitteraleEntiere(tmp));
        else if (Operateur::estOperateur(tmp)){
            qDebug()<<"estUnOperateur";
            Operateur op(tmp, &pile);
            op.executer();
        }
        else if (LitteraleProgramme::estLitteraleProgramme(tmp))
            pile.empiler(new LitteraleProgramme(tmp));
        else if (LitteraleExpression::estLitteraleExpression(tmp))
            pile.empiler(new LitteraleExpression(tmp));
        else if(estLitteraleAtome(tmp)){
            qDebug()<<"estLitteraleAtome";
            Litterale* prog = getAtome(tmp);
            qDebug()<<" TEST "<<prog->toString();
            executer(prog->toString());
            delete prog;
        }
        else
            qDebug()<<"not found";


    }

}

void Manager::insererProgramme(QString id, QString str){
    mapProgramme->insert(id, str);
    stringListProgrammes->append(id);
}


void Manager::supprimerProgramme(QString id){
    mapProgramme->remove(id);
    stringListProgrammes->removeOne(id);
}

bool Manager::estLitteraleAtome(QString input) const{
    return (mapProgramme->contains(input));
}

Litterale* Manager::getAtome(QString input){
    LitteraleProgramme* prog = new LitteraleProgramme(mapProgramme->value(input));
    qDebug()<<prog->toString();
    return prog;
}
