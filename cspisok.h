#ifndef CSPISOK_H
#define CSPISOK_H

#include <QWidget>
#include "ctable.h"
#include "cbuttons.h"
#include "cinputtextdialog.h"
#include "cparam.h"

class CSpisok : public QWidget
{
private:
    Q_OBJECT

    QString name;
    CTable table;
    CButtons buttons;
    QImage image_back;
   // QLineEdit line_edit;

public:
    explicit CSpisok(QString n, QString nt, QWidget *parent = 0);

    void paintEvent(QPaintEvent *p);
    void resizeEvent(QResizeEvent *r);
    void SetImageBack(const QImage &ib, const QRect &r);
    void SetList(QList<QString> l);
    QList<QString> GetList();
signals:
    void IAmResize();

public slots:
    void OnButtonsClick(unsigned n, bool b);

};

#endif // CSPISOK_H
