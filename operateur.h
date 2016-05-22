#ifndef OPERATEUR_H
#define OPERATEUR_H


class Operateur
{
public:
    Operateur();
    QString getType() const {return type;}
    int getArite() const {return arite;}
    static bool estOperateur(QString type);

private:
    QString type;
    int arite;
};

#endif // OPERATEUR_H
