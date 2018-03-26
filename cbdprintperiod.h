#ifndef CBDPRINTPERIOD_H
#define CBDPRINTPERIOD_H

#include <QWidget>
#include "CWheel.h"
#include "CStack.h"
#include "cbuttons.h"
#include "ctable.h"
#include "cparam.h"
#include "cprintthread.h"

class CBdPrintPeriod : public QWidget
{
    Q_OBJECT

    QCalendarWidget calendar1, calendar2;
    QDate date1, date2;
    CButtons buttons;
    CStack <CWheel> wheels;
    QImage image_back;
    QPrinter printer, printer_pdf;
    CTable table_defectoskopist;
    QLabel label_date;
    CPrintThread *print_thread;

    void SetButtons(const bool all);
    void PrintDiallog();
    void PrintWheels();
    void PrintPdfWheels();
    void Print(QPrinter *printer, const bool pdf = false);
    void PaintCells(QPainter &painter, const int kind, const double &y1, const double &y2, const double &mmpole, const double &mmw, const double &mmh);

public:
    explicit CBdPrintPeriod(QWidget *parent = 0);
    ~CBdPrintPeriod();
    void resizeEvent(QResizeEvent *r);
    void paintEvent(QPaintEvent *p);
    void Run();
    void SetImageBack(const QImage &ib, const QRect &r);
signals:
     void OnPressButton(unsigned n);
     void IAmReSize();

public slots:
     void OnButtonsClick(unsigned v, bool b);
     void OnClickLineTablet(unsigned n);
     void CalendarChanged();
     void OnPrintThreadState(unsigned n);
};

#endif // CBDPRINTPERIOD_H
