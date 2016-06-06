#include "manager.h"
#include "litteraleexpression.h"
#include "litteralecomplexe.h"
#include "litteralerationnelle.h"
#include <typeinfo>

Manager::Manager(Pile &p) : pile(p), mapProgramme(new QMap<QString, QString>), stringListProgrammes(new QStringList)
{
}


bool Manager::interpreter(QString input){

   if(input.right(1)=="+" || input.right(1)=="-" || input.right(1)=="*" ||  input.right(1)=="$"){
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
        else if (estUnOperateur(tmp)){
            qDebug()<<"estUnOperateur";
            operer(tmp);
        }
        else if(LitteraleRationnelle::estLitteraleRationnelle(tmp)){
            pile.empiler(new LitteraleRationnelle(tmp));
        }
        else if (LitteraleProgramme::estLitteraleProgramme(tmp))
            pile.empiler(new LitteraleProgramme(tmp));
        else if (LitteraleExpression::estLitteraleExpression(tmp))
            pile.empiler(new LitteraleExpression(tmp));
        else if(estLitteraleAtome(tmp)){
            Litterale* prog = getAtome(tmp);
            executer(prog->toString());
            delete prog;
        }
        else
            qDebug()<<"not found";


    }

}


void Manager::operer(QString op){

    if(op!="LASTOP")
        lastOp=op;

    qDebug()<<op;

    std::vector<Litterale*> litterales;


    /*if(op !="DUP" && op!="SWAP" && op!="LASTOP" && op!="CLEAR" && op=="UNDO" && op=="REDO"){
            for(unsigned int i=0; i<getArite(op); i++){
                Litterale* tmp = pile.depiler();

                if(dynamic_cast<LitteraleNumerique*> (tmp))
                    litterales.push_back(tmp);
                else{

                    litterales.push_back(dynamic_cast<LitteraleNumerique*> (pile.depiler()));
                }

            }

            pile.setLastArgs(litterales);
    }*/

    if(op !="DUP" && op!="SWAP" && op!="LASTOP" && op!="CLEAR" && op!="UNDO" && op!="REDO"){
        qDebug()<<"manager::operer test operateur different de mots cles"<<getArite(op);
                for(unsigned int i=0; i<getArite(op); i++){

                    litterales.push_back(dynamic_cast<Litterale*> (pile.depiler()));
                }
    }

    Litterale* newLit;




    qDebug() << "manager::operer Avant test + - * /";
    if(op=="+")
        newLit = *litterales.at(1)+ *litterales.at(0);
    else if(op=="*")
        newLit = *litterales.at(1)*(*litterales.at(0));
    else if(op=="-"){
        qDebug() << "manager::operer l'op est -";
        newLit = *litterales.at(1)-*litterales.at(0);}
    else if(op=="/")
        newLit = *litterales.at(1)/(*litterales.at(0));
    else if(op=="$"){
        LitteraleEntiere *lit1 = dynamic_cast<LitteraleEntiere*> (litterales.at(0));
        LitteraleEntiere *lit2 = dynamic_cast<LitteraleEntiere*> (litterales.at(1));
        newLit = new LitteraleComplexe(lit2, lit1);
    }
    else if(op=="NEG"){
        pile.savePile();
    }
    else if(op=="DUP"){
        pile.dupliquer();
    }
    else if(op=="SWAP"){
        pile.swap();
        pile.savePile();


    }
    else if(op=="CLEAR"){
        pile.clear();
        pile.savePile();

    }
    else if(op=="UNDO"){

        pile.undo();
    }
    else if(op=="REDO"){

        pile.redo();
    }
    else if(op=="LASTOP"){
        qDebug()<<"OP LASTOP "<<lastOp;
        operer(lastOp);
    }
    qDebug() << "manager::operer juste avant d'empiler " << newLit->toString();

    if(op!="DUP" && op!="DROP" && op!="SWAP" && op!="CLEAR" && op!="UNDO" && op!="REDO" && op!="LASTOP"){
     pile.empiler(newLit);
    }

}


int Manager::getArite(QString op){
    if(op=="+" || op=="-" || op=="*" || op=="/" || op=="$")
        return 2;
    if(op=="NEG" || op=="DUP" || op=="DROP")
        return 1;
}


bool Manager::estUnOperateur(QString op){
    return (op=="+" || op=="-" || op=="*" || op=="/" || op=="$" || op=="DUP" || op=="DROP" || op=="SWAP" || op=="LASTOP"
            || op=="CLEAR" || op=="UNDO" || op=="REDO");
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
