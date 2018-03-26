#ifndef CBDPRINTDAY_H
#define CBDPRINTDAY_H

#include <QWidget>
#include "CWheel.h"
#include "CStack.h"
#include "cbuttons.h"
#include "ctable.h"
#include "cparam.h"

class CBdPrintDay : public QWidget
{
    Q_OBJECT

    QDate date;
    CButtons buttons;
    CStack <CWheel> wheels;
    QImage image_back;
    QPrinter printer;
    CTable table_defectoskopist;
    QLabel label_date, label_def;

    void SetButtons();
    void PrintDiallog();
    void PrintWheels();
    void PrintPdfWheels();
    void Print(QPrinter *printer, const bool pdf = false);
    void PaintCells(QPainter &painter, const int kind, const double &y1, const double &y2, const double &mmpole, const double &mmw, const double &mmh);
public:
    explicit CBdPrintDay(QWidget *parent = 0);

    void resizeEvent(QResizeEvent *r);
    void paintEvent(QPaintEvent *p);
     void Run(QDate d, CStack <CWheel> &w);
     void SetImageBack(const QImage &ib, const QRect &r);
signals:
     void OnPressButton(unsigned n);
     void IAmReSize();

public slots:
     void OnButtonsClick(unsigned v, bool b);
     void OnClickLineTablet(unsigned n);
};

#endif // CBDPRINTDAY_H
