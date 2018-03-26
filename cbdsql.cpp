#include "cbdsql.h"

CBdSql::CBdSql()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sdvk");
    db.setUserName("andrey");
    db.setHostName("");
    db.setPassword("12");
    db.open();
}
bool CBdSql::Run(QDate d)
{
    date = d;
    QSqlQuery query;
    QString str = "CREATE TABLE sdvk ( "
                  "number INTEGER PRIMARY KEY NOT NULL, "
                    "name VARCHAR[100] "
                    ");";
    return query.exec(str);
}
