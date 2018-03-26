#include "cbd.h"

CBd::CBd(QWidget *parent) : CAllWindows(parent), bdtable(this), print_day(this), print_period(this)
{
    SAllWindowsInit init_st;
    init_st.direction_widget = SAllWindowsInit::edHorizontal;
    init_st.direction_frame = SAllWindowsInit::edNone;
    init_st.rewindow_time_all = 100;
    init_st.rewindow_kol_step = 5;
    init_st.frame_width = 0;
    SetInitStruct(init_st);

    QPixmap pix1;
    AddWidget(&bdtable, "", pix1);
    AddWidget(&print_day, "", pix1);
    AddWidget(&print_period, "", pix1);
    QObject::connect(&bdtable, SIGNAL(OnPressButton(QDate, CStack <CWheel> &)), this, SLOT(OnPressButton1(QDate, CStack <CWheel> &)));
    QObject::connect(&print_day, SIGNAL(OnPressButton(unsigned)), this, SLOT(OnPressButton2(unsigned)));
    QObject::connect(&print_period, SIGNAL(OnPressButton(unsigned)), this, SLOT(OnPressButton3(unsigned)));
    QObject::connect(&bdtable, SIGNAL(IAmReSize()), this, SLOT(OnReSizeBdTabel()));
    QObject::connect(&print_day, SIGNAL(IAmReSize()), this, SLOT(OnReSizeBdPrintDay()));
    QObject::connect(&print_period, SIGNAL(IAmReSize()), this, SLOT(OnReSizeBdPrintPeriod()));
}
void CBd::Run()
{
    init_struct.rewindow_time_all = 0;
    init_struct.rewindow_kol_step = 1;
    SetVisibleWidget(0);
    init_struct.rewindow_time_all = 100;
    init_struct.rewindow_kol_step = 5;
}
void CBd::OnNewWheel(const CWheel &w)
{
    bdtable.OnNewWheel(w);
}
void CBd::OnPressButton1(QDate d, CStack <CWheel> &w)
{
    print_day.Run(d, w);
    SetVisibleWidget(1);
}
void CBd::OnPressButton2(unsigned n)
{
    if(!n)
        SetVisibleWidget(0);
    else if(n == 4)
    {
        print_period.Run();
        SetVisibleWidget(2);
    }
}
void CBd::OnPressButton3(unsigned n)
{
    if(!n)
        SetVisibleWidget(1);
   // else if(n == 1)
   //     SetVisibleWidget(0);
}
void CBd::OnReSizeBdTabel()
{
    bdtable.SetImageBack(image_back, rect());
}
void CBd::OnReSizeBdPrintDay()
{
    print_day.SetImageBack(image_back, rect());
}
void CBd::OnReSizeBdPrintPeriod()
{
    print_period.SetImageBack(image_back, rect());
}
void CBd::SetImageBack(const QImage &ib, const QRect &r)
{
    image_back = QImage(width(), height(), QImage::Format_RGB32);
    QPainter painter(&image_back);
    painter.drawImage(rect(), ib, r);
    painter.end();
}
