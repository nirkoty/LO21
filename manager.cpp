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
    bool ok=true;
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
        else{
            qDebug()<<"not found";
            ok=false;
        }
        if(ok && tmp!="UNDO" && tmp!="REDO")
            pile.savePile();


    }

}


void Manager::operer(QString op){

    if((getArite(op) <= pile.taille()) || getArite(op)==-1){
        if(op!="LASTOP")
            lastOp=op;

        std::vector<Litterale*> litterales;
        std::vector<QString> newLastArgs;

        if(op !="DUP" && op!="SWAP" && op!="LASTOP" && op!="CLEAR" && op!="UNDO" && op!="REDO" && op!="LASTARGS" && op!="DROP"){
                    for(unsigned int i=0; i<getArite(op); i++){
                        Litterale* tmp = pile.depiler();
                        newLastArgs.push_back(tmp->toString());
                        litterales.push_back(dynamic_cast<Litterale*> (tmp));
                    }
                    pile.setLastArgs(newLastArgs);
        }

        Litterale* newLit;



        if(op=="+")
            newLit = *litterales.at(0)+ *litterales.at(1);
        else if(op=="*")
            newLit = *litterales.at(0)*(*litterales.at(1));
        else if(op=="-"){
            qDebug() << "Test -";
            newLit = *litterales.at(0)-*litterales.at(1);}
        else if(op=="/")
            newLit = *litterales.at(0)/(*litterales.at(1));
        else if(op=="$"){
            LitteraleEntiere *lit1 = dynamic_cast<LitteraleEntiere*> (litterales.at(0));
            LitteraleEntiere *lit2 = dynamic_cast<LitteraleEntiere*> (litterales.at(1));
            newLit = new LitteraleComplexe(lit2, lit1);
        }
        else if(op=="NEG"){

        }
        else if(op=="DUP"){
            pile.dupliquer();
        }

        else if(op=="DROP"){
            pile.depiler();
        }
        else if(op=="SWAP"){
            pile.swap();



        }
        else if(op=="CLEAR"){
            pile.clear();


        }
        else if(op=="UNDO"){
            pile.undo();
        }
        else if(op=="REDO"){

            pile.redo();
        }
        else if(op=="LASTOP"){
            operer(lastOp);
        }
        else if(op=="LASTARGS"){
            pile.empilerLastArgs();
        }


        if(op!="DUP" && op!="DROP" && op!="SWAP" && op!="CLEAR" && op!="UNDO" && op!="REDO" && op!="LASTOP"  && op!="LASTARGS"){
         pile.empiler(newLit);
        }
    }
    else
        qDebug()<<"Erreur execution commande";

}




int Manager::getArite(QString op){
    if(op=="+" || op=="-" || op=="*" || op=="/" || op=="$")
        return 2;
    if(op=="NEG" || op=="DUP" || op=="DROP")
        return 1;
    return -1;
}


bool Manager::estUnOperateur(QString op){
    return (op=="+" || op=="-" || op=="*" || op=="/" || op=="$" || op=="DUP" || op=="DROP" || op=="SWAP" || op=="LASTOP"
            || op=="CLEAR" || op=="UNDO" || op=="REDO" || op=="LASTARGS");
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
