#ifndef CINPUTPS_H
#define CINPUTPS_H

#include <QWidget>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include "cbuttons.h"
#include "cparam.h"
#include "ctable.h"


class CEditPs : public QWidget
{
    Q_OBJECT

    QLineEdit *line_edit;
    CChecks *check;
    CTable *table;

    QImage image_back;
public:
    explicit CEditPs(QString str, int spb, QWidget *parent = 0);

    QString GetStr() const;
    int GetCheck() const;

    void SetImageBack(const QImage &ib, const QRect &r);
    void paintEvent(QPaintEvent *p);
    void resizeEvent(QResizeEvent *r);
    void Clear();
signals:

public slots:
    void OnTableClickLine(unsigned n);
};

#endif // CINPUTPS_H
