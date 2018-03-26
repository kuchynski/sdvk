#include "cinput.h"

CInput::CInput(QWidget *parent) : CAllWindows(parent), block_first(this), block_scan(this)
{
    SAllWindowsInit init_st;
    init_st.direction_widget = SAllWindowsInit::edHorizontal;
    init_st.direction_frame = SAllWindowsInit::edNone;
    init_st.rewindow_time_all = 100;
    init_st.rewindow_kol_step = 5;
    init_st.frame_width = 0;
    SetInitStruct(init_st);

    QPixmap pix1;
    AddWidget(&block_first, "", pix1);
    AddWidget(&block_scan, "", pix1);
    QObject::connect(&block_first, SIGNAL(PressButtonStart(CWheel &)), this, SLOT(OnPressButton1(CWheel &)));
    QObject::connect(&block_scan, SIGNAL(PressButton(unsigned)), this, SLOT(OnPressButton2(unsigned)));
    QObject::connect(&block_scan, SIGNAL(NewWheel(const CWheel &)), parent, SLOT(OnNewWheel(const CWheel &)));
    QObject::connect(&block_first, SIGNAL(IAmResize()), this, SLOT(OnReSizeBlockFirst()));
    QObject::connect(&block_scan, SIGNAL(IAmResize()), this, SLOT(OnReSizeBlockScan()));
    Run();
}
void CInput::Run()
{
    init_struct.rewindow_time_all = 0;
    init_struct.rewindow_kol_step = 1;
//    SetInitStruct(init_struct);
    block_first.Run();
    SetVisibleWidget(0);
    init_struct.rewindow_time_all = 100;
    init_struct.rewindow_kol_step = 5;
  //  SetInitStruct(init_struct);
}
void CInput::Stop()
{
    block_first.Stop();
}
void CInput::OnPressButton1(CWheel &w)
{
    block_first.Begin(w.GetThicknessOfRimLeft());
    block_scan.Run(w);
    SetVisibleWidget(1);
}
void CInput::OnPressButton2(unsigned n)
{
    SetVisibleWidget(0);
    block_first.Run();
    Stop();
}
void CInput::OnBlockState(unsigned type, unsigned w, unsigned l)
{
    if(type == 0x10)
    {// ошибка подвода датчиков
        QList<QString> str;
        str << QString::fromLocal8Bit("Ошибка подвода преобразователей!");
        str << QString::fromLocal8Bit("Вероятно неправильно установлена");
        str << QString::fromLocal8Bit("колёсная пара.");
        QList<QString> but;
        but << QString::fromLocal8Bit("продолжить") << QString::fromLocal8Bit("отменить");
        CQuestionDialog *td = new CQuestionDialog(str, but, 650, param.GetSizeX(), param.GetSizeY(), this);
        td->exec();
        unsigned res = td->GetResult();
        delete td;
        if(res == 0)
            block_first.Stop(true);
        else
            OnPressButton2(0);
    }
    else if(GetVisibleWidget() == 1)
        block_scan.OnBlockState(type, w, l);
}
void CInput::OnReSizeBlockFirst()
{
    block_first.SetImageBack(image_back, rect());
}
void CInput::OnReSizeBlockScan()
{
    block_scan.SetImageBack(image_back, rect());
}
void CInput::SetImageBack(const QImage &ib, const QRect &r)
{
    image_back = QImage(width(), height(), QImage::Format_RGB32);
    QPainter painter(&image_back);
    painter.drawImage(rect(), ib, r);
    painter.end();
}
