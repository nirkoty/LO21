#include "manager.h"
#include "litteraleexpression.h"
#include "litteralecomplexe.h"
#include "litteralerationnelle.h"
#include <QLineEdit>
#include <typeinfo>

Manager::Manager() :mapProgramme(new QMap<QString, QString>), mapVariable(new QMap<QString, QString>), stringListProgrammes(new QStringList),  stringListVariables(new QStringList), pile(new Pile(this))
{

}


bool Manager::interpreter(QString input){

   if(!input.contains("'")){
       if(input.right(1)=="+" || input.right(1)=="-" || input.right(1)=="*" ||  input.right(1)=="$"){
            executer(input);
            return true;
       }
       return false;
   }
   else
       return false;

}


void Manager::executer(QString input){

    QString tmp;
    bool ok=true;
    try{
        while(input.length()>0){
            qDebug()<<input;
            tmp = input.left(input.indexOf(" "));
            qDebug()<<"tmp "<<tmp;
            if(input.indexOf(" ")!=-1)
                input=input.remove(0, input.indexOf(" ")+1);
            else
                input="";

            if(LitteraleReelle::estLitteraleReelle(tmp))
                pile->empiler(new LitteraleReelle(tmp));
            else if (LitteraleEntiere::estLitteraleEntiere(tmp))
                pile->empiler(new LitteraleEntiere(tmp));
            else if (estUnOperateur(tmp)){
                try{
                    operer(tmp);
                }catch(ComputerException ce){
                    ce.what();
                    ok=false;
                }


            }
            else if(LitteraleRationnelle::estLitteraleRationnelle(tmp)){
                pile->empiler(new LitteraleRationnelle(tmp));
            }
            else if (LitteraleProgramme::estLitteraleProgramme(tmp))
                pile->empiler(new LitteraleProgramme(tmp));
            else if (LitteraleExpression::estLitteraleExpression(tmp))
                pile->empiler(new LitteraleExpression(tmp, this));
            else if(estLitteraleAtome(tmp)){
                Litterale* prog = getAtome(tmp);
                executer(prog->toString());
                delete prog;
            }
            else{
                throw ComputerException(QString("Impossible d'identifier l'opérande "+tmp));
                ok=false;
            }
            if(ok && tmp!="UNDO" && tmp!="REDO")
                pile->savePile();
        }
    }catch(ComputerException ce){
        ce.what();
    }



}


void Manager::operer(QString op){

    if((getArite(op) <= pile->taille()) || getArite(op)==-1){
        if(op!="LASTOP")
            lastOp=op;

        std::vector<Litterale*> litterales;
        std::vector<QString> newLastArgs;

        if(op !="DUP" && op!="SWAP" && op!="LASTOP" && op!="CLEAR" && op!="UNDO" && op!="REDO" && op!="LASTARGS" && op!="DROP"){
                    for(unsigned int i=0; i<getArite(op); i++){
                        Litterale* tmp = pile->depiler();
                        newLastArgs.push_back(tmp->toString());
                        litterales.push_back(dynamic_cast<Litterale*> (tmp));
                    }
                    pile->setLastArgs(newLastArgs);
        }

        Litterale* newLit=NULL;



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
            pile->dupliquer();
        }

        else if(op=="DROP"){
            pile->depiler();
        }
        else if(op=="SWAP"){
            pile->swap();



        }
        else if(op=="CLEAR"){
            pile->clear();


        }
        else if(op=="UNDO"){
            pile->undo();
        }
        else if(op=="REDO"){

            pile->redo();
        }
        else if(op=="LASTOP"){
            operer(lastOp);
        }
        else if(op=="LASTARGS"){
            pile->empilerLastArgs();
        }
        else if(op=="STO"){
            if(LitteraleProgramme::estLitteraleProgramme(litterales.at(0)->toString())){
                Litterale* lit1=litterales.at(1);
                Litterale* lit0=litterales.at(0);
                insererProgramme(lit0->toString(), lit1->toString());
                ecrireFichierProgramme(mapProgramme);
            }
            else{
                Litterale* lit1=litterales.at(1);
                Litterale* lit0=litterales.at(0);
                insererVariable(lit0->toString(), lit1->toString());
                ecrireFichierVariable(mapVariable);
            }

        }

        else if(op=="FORGET"){
            Litterale* lit0=litterales.at(0);
            if(mapProgramme->contains(lit0->toString())){
                supprimerProgramme(lit0->toString());
                ecrireFichierProgramme(mapProgramme);
            }
            else if(mapVariable->contains(lit0->toString())){
                supprimerVariable(lit0->toString());
                ecrireFichierVariable(mapVariable);
            }

        }

        else if(op=="EVAL"){
            try{
                LitteraleExpression* litExpression;
                if(litExpression=dynamic_cast<LitteraleExpression*> (litterales.at(0))){
                    newLit=litExpression->evaluer();
                    delete litExpression;
                }
                else
                    throw ComputerException(QString("La littérale n'est pas un programme ou une expression"));
            }catch(ComputerException ce){
                ce.what();
                pile->empiler(litterales.at(0));
            }
        }


        if(op!="DUP" && op!="DROP" && op!="SWAP" && op!="CLEAR" && op!="UNDO" && op!="REDO" && op!="LASTOP"  && op!="LASTARGS" && op!="STO" && op!="FORGET" && newLit!= NULL){
         pile->empiler(newLit);
        }
    }
    else{
        throw ComputerException(QString("Pas assez d'élements dans la pile pour appliquer cet opérateur"));

    }
}




int Manager::getArite(QString op){
    if(op=="+" || op=="-" || op=="*" || op=="/" || op=="$" || op=="STO")
        return 2;
    if(op=="NEG" || op=="DUP" || op=="DROP" | op=="FORGET" || op=="EVAL")
        return 1;
    return -1;
}


bool Manager::estUnOperateur(QString op){
    return (op=="+" || op=="-" || op=="*" || op=="/" || op=="$" || op=="DUP" || op=="DROP" || op=="SWAP" || op=="LASTOP"
            || op=="CLEAR" || op=="UNDO" || op=="REDO" || op=="LASTARGS" || op=="STO" || op=="FORGET" || op=="EVAL");
}


void Manager::insererProgramme(QString id, QString str){
    mapProgramme->insert(id, str);
    stringListProgrammes->append(id);
}


void Manager::supprimerProgramme(QString id){
    mapProgramme->remove(id);
    stringListProgrammes->removeOne(id);
}

void Manager::insererVariable(QString id, QString str){
    mapVariable->insert(id, str);
    stringListVariables->append(id);
}


void Manager::supprimerVariable(QString id){
    mapVariable->remove(id);
    stringListVariables->removeOne(id);
}

bool Manager::estLitteraleAtome(QString input) const{
    return (mapProgramme->contains(input) || mapVariable->contains(input));
}

Litterale* Manager::getAtome(QString input){
    if(mapProgramme->contains(input)){
        LitteraleProgramme* prog = new LitteraleProgramme(mapProgramme->value(input));
        qDebug()<<prog->toString();
        return prog;
    }
    else{
        if(LitteraleReelle::estLitteraleReelle(mapVariable->value(input)))
            return new LitteraleReelle(mapVariable->value(input));

        else if (LitteraleEntiere::estLitteraleEntiere(mapVariable->value(input)))
            return new LitteraleEntiere(mapVariable->value(input));

        else if(LitteraleRationnelle::estLitteraleRationnelle(mapVariable->value(input))){
            return new LitteraleRationnelle(mapVariable->value(input));
        }

    }
}


void Manager::ecrireFichierVariable(QMap<QString, QString>* mapVariable, QLineEdit *zoneIdentifiantVariable, QTextEdit *zoneVariable){



    QMapIterator<QString, QString> it(*mapVariable);

    QString path("variables.xml");
    QFile file(path);
    file.open(QFile::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setAutoFormattingIndent(2);
    xmlWriter.writeStartDocument();

    xmlWriter.writeStartElement("variables");
    while(it.hasNext()){

        it.next();
        xmlWriter.writeStartElement("variable");
        xmlWriter.writeTextElement("identifiant",it.key());
        xmlWriter.writeTextElement("string", it.value());
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
    if(zoneIdentifiantVariable!=0){
        zoneIdentifiantVariable->clear();
        zoneVariable->clear();
    }
}

void Manager::ecrireFichierProgramme(QMap<QString, QString>* mapProgramme, QLineEdit *zoneIdentifiant, QTextEdit *zoneProgramme){



    QMapIterator<QString, QString> it(*mapProgramme);

    QString path("programmes.xml");
    QFile file(path);
    file.open(QFile::WriteOnly);
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.setAutoFormattingIndent(2);
    xmlWriter.writeStartDocument();




    xmlWriter.writeStartElement("programmes");
    while(it.hasNext()){

        it.next();
        xmlWriter.writeStartElement("programme");
        xmlWriter.writeTextElement("identifiant",it.key());
        xmlWriter.writeTextElement("string", it.value());
        xmlWriter.writeEndElement();
    }

    xmlWriter.writeEndElement();
    xmlWriter.writeEndDocument();
    file.close();
    if(zoneIdentifiant!=0){
        zoneIdentifiant->clear();
        zoneProgramme->clear();
    }

}
