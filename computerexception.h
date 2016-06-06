#ifndef COMPUTEREXCEPTION_H
#define COMPUTEREXCEPTION_H


#include <stdexcept>
#include <QDebug>
#include <QMessageBox>
#include <QString>

using namespace std;
class ComputerException
{
public:
    QString info;
    public:
    ComputerException(const QString& i) throw():info(i){}
    virtual ~ComputerException() throw(){}
    const void what() const throw();
};

#endif // COMPUTEREXCEPTION_H
