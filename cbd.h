#ifndef CBD_H
#define CBD_H

#include "CAllWindows.h"
#include "cbdtable.h"
#include "cbdprintday.h"
#include "cbdprintperiod.h"

class CBd : public CAllWindows
{
    Q_OBJECT

    SAllWindowsInit init_struct;
    CBdTable bdtable;
    CBdPrintDay print_day;
    CBdPrintPeriod print_period;
    QImage image_back;

public:
    explicit CBd(QWidget *parent = 0);

    void Run();
   // void Stop();
    void SetImageBack(const QImage &ib, const QRect &r);
    void OnNewWheel(const CWheel &w);
signals:

public slots:
    void OnPressButton1(QDate d, CStack <CWheel> &w);
    void OnPressButton2(unsigned n);
    void OnPressButton3(unsigned n);
    void OnReSizeBdTabel();
    void OnReSizeBdPrintDay();
    void OnReSizeBdPrintPeriod();
};

#endif // CBD_H
