#ifndef CBDSQL_H
#define CBDSQL_H

#include <QtSql>

class CBdSql
{
private:
    QDate date;
public:
    CBdSql();

    bool Run(QDate d);
};

#endif // CBDSQL_H
