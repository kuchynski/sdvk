#ifndef CPRINTTHREAD_H
#define CPRINTTHREAD_H

#include <QThread>
#include <QObject>
#include "CWheel.h"
#include "CStack.h"

class CPrintThread : public QThread
{
    Q_OBJECT

    QPrinter *printer;
    bool pdf;
    QDate date1, date2;
    QString name;
    QString file_path, tek_file_path;
    QDir dir;

    bool SetDir(const QDate &_date);
public:
    CPrintThread(QPrinter *p, const bool pd, const QString n, const QDate d1, const QDate d2, QObject *parent = 0);
    ~CPrintThread();

    void run();
signals:
    void NewState(unsigned s);
};

#endif // CPRINTTHREAD_H
