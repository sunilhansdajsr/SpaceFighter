#ifndef CLASS1_H
#define CLASS1_H

#include <QObject>

class class1 : public QObject
{
    Q_OBJECT
public:
    class1();


signals:
    void printIt();

};

#endif // CLASS1_H
