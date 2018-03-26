#include "cmainwindow.h"

CMainWindow::CMainWindow(QWidget *parent): CBaseWindow(QString::fromLocal8Bit("выход"), "", parent), buttons(this),
    bd_window(this), options_window(this), input_window(this)
{
    CButtons::SButtonsInit but_init;
    but_init.direction = CButtons::SButtonsInit::edHorizontal;
    but_init.font = this->font();
    but_init.font.setPixelSize(25);
    but_init.color_backgraund = QColor(25, 80, 100, 255);//0, 30, 185, 255);
    but_init.color_backgraund_checked = QColor(100, 100, 255, 255);
    but_init.sglaz_const = 20;
//    but_init.color_backgraund2 = QColor(0, 30, 185, 255);
  //  but_init.color_backgraund_checked2 = QColor(100, 100, 255, 255);
    but_init.color_text = Qt::white;
    buttons.SetInitStruct(but_init);
    buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("Сканирование")));
    buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("База данных")));
    buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("Настройки")));
    QObject::connect(&buttons, SIGNAL(PressButton(unsigned, bool)), this, SLOT(OnButtonsClick(unsigned, bool)));
    buttons.setGeometry((width()-buttons.width())/2, (height()-buttons.height())/2, buttons.width(), buttons.height());
   // pbx->addWidget(&buttons, 3);
    buttons.SetFocusAll(true);
   // buttons.Paint();

    options_window.setVisible(false);
    QObject::connect(&options_window, SIGNAL(BaseSignal(int)), this, SLOT(OnOkCancelOptionsWindow(int)));
    bd_window.setVisible(false);
    QObject::connect(&bd_window, SIGNAL(BaseSignal(int)), this, SLOT(OnOkCancelBdWindow(int)));
    input_window.setVisible(false);
    QObject::connect(&input_window, SIGNAL(BaseSignal(int)), this, SLOT(OnOkCancelInputWindow(int)));
    QObject::connect(&input_window, SIGNAL(NewWheel(const CWheel&)), &bd_window, SLOT(OnNewWheel(const CWheel &)));
}
void CMainWindow::SetVisible(const bool vis)
{
    buttons.setVisible(vis);
    CBaseWindow::SetVisible(vis);
}
void CMainWindow::OnButtonsClick(unsigned n, bool s)
{
    int center_x, center_y;
    QRect rect = buttons.geometry();
    switch(n)
    {
        case 0: center_x = rect.x() + (rect.width() * 1 / 6);
                center_y = rect.y() + (rect.height() / 2);
                input_window.Run();
                SetChild(&input_window, center_x, center_y, 10);
                break;
        case 1: center_x = rect.x() + (rect.width() * 3 / 6);
                center_y = rect.y() + (rect.height() / 2);
                bd_window.Run();
                SetChild(&bd_window, center_x, center_y, 1);
                break;
        case 2: center_x = rect.x() + (rect.width() * 5 / 6);
                center_y = rect.y() + (rect.height() / 2);
                options_window.ReadDataFromParam();
                SetChild(&options_window, center_x, center_y, 1);
                break;
    }
}
void CMainWindow::OnOkCancelOptionsWindow(int)
{
    CloseChild();
}
void CMainWindow::OnOkCancelBdWindow(int)
{
    CloseChild();
}
void CMainWindow::OnOkCancelInputWindow(int res)
{
    CloseChild();
    if(res)
    {

    }
}
void CMainWindow::OnButtonsBaseClick(unsigned n, bool s)
{
    exit(0);
}
void CMainWindow::mouseDoubleClickEvent(QMouseEvent *pe)
{
    if(pe->button() == Qt::MidButton)
    {
        options_window.SetMouseEnabled(!param.GetMouseEnabled());
        return;
    }
    QWidget::mouseDoubleClickEvent(pe);
}

void CMainWindow::paintEvent(QPaintEvent *p)
{
    if(!QWidget::isVisible())
        return;
    QPainter painter;
    painter.begin(this);
    painter.drawImage(p->rect(), image_my, p->rect());
    painter.end();
    CBaseWindow::paintEvent(p);
}
void CMainWindow::resizeEvent(QResizeEvent *r)
{
    QPainter painter;
    image_my = QImage(width(), height(), QImage::Format_RGB32);
    painter.begin(&image_my);
    QLinearGradient gradient(0, 0, 0, height());
    QRect rect1(0, 0, width(), height());
    painter.setBrush(Qt::gray);
    painter.drawRect(rect1);
//    QColor cg = QColor(0, 0, 0, 255);
    QColor cg = QColor(50, 150, 200, 255);
    int stap_gr[8] = {100, 150, 200, 220, 220, 220, 255};
    for(int i = 0; i < 7; i ++)
    {
        cg.setAlpha(stap_gr[i]);
        gradient.setColorAt((double)i / 6.0, cg);
    }
    painter.setPen(QPen(cg));
    painter.setBrush(gradient);
    painter.drawRect(rect1);
    painter.setPen(QPen(Qt::white));
    painter.setBrush(Qt::NoBrush);
    painter.drawRoundedRect(QRect(0, 0, width()-1, height()-1), 5, 5);
 //   painter.drawRoundedRect(QRect(1, 1, width()-2, height()-2), 5, 5);
 //   painter.drawRoundedRect(QRect(2, 2, width()-4, height()-4), 5, 5);
    painter.end();

    buttons.resize(width()/3*2, 150);
    buttons.setGeometry((width()-buttons.width())/2, (height()-buttons.height())/2, buttons.width(), buttons.height());
    buttons.SetImageBack(image_my, buttons.geometry());

    CBaseWindow::resizeEvent(r);

    param.SetSizeXY(width(), height());
}
