#include "cbasewindow.h"

CBaseWindow::CBaseWindow(const QString name_but_ok, const QString name_but_cancel, QWidget *parent) :
    QWidget(parent), buttons(this), child(0), timer_up(0), timer_down(0)
{
    //setupUi(this);
    if((name_but_ok != "") || (name_but_cancel != ""))
    {
        CButtons::SButtonsInit but_init;
        but_init.direction = CButtons::SButtonsInit::edVertical;
        but_init.font = this->font();
        but_init.font.setPixelSize(15);
        but_init.color_backgraund = QColor(185, 180, 35, 255);
        but_init.color_backgraund_checked = QColor(100, 100, 255, 255);
        but_init.sglaz_const = 20;
//    but_init.color_backgraund2 = QColor(0, 30, 185, 255);
  //  but_init.color_backgraund_checked2 = QColor(100, 100, 255, 255);
        but_init.color_text = Qt::white;
        buttons.SetInitStruct(but_init);
        int h = 0;
        if(name_but_ok != "")
        {
            buttons.AddButton(CButtons::SButton(name_but_ok));
            h += 50;
        }
        if(name_but_cancel != "")
        {
            buttons.AddButton(CButtons::SButton(name_but_cancel));
            h += 50;
        }
        QObject::connect(&buttons, SIGNAL(PressButton(unsigned, bool)), this, SLOT(OnButtonsBaseClick(unsigned, bool)));
        buttons.setGeometry(width()-60, 10, 100, h);
        buttons.SetFocusAll(true);
        buttons.Paint();
    }
}
void CBaseWindow::SetVisible(const bool vis)
{
    buttons.setVisible(vis);
}
void CBaseWindow::SetChild(QWidget *ch, unsigned cx, unsigned cy, const unsigned tms)
{
    child = ch;
   // child->setVisible(true);
   // child->setVisible(false);
    child->setGeometry(rect());
    child->setVisible(true);
    return;
    if(timer_down)
    {
        child->setVisible(false);
        QObject::killTimer(timer_down);
        timer_down = 0;
    }
    timer_max_step = tms;
    timer_step = 0;
    center_x = cx;
    center_y = cy;
  //  timer_up = QObject::startTimer(2);
}
void CBaseWindow::CloseChild()
{child->setVisible(false);return;
    if(timer_up)
    {
        QObject::killTimer(timer_up);
        timer_up = 0;
    }
    if(child)
    {
        SetVisible(true);
        timer_down = QObject::startTimer(2);
    }
}
void CBaseWindow::timerEvent(QTimerEvent *event)
{
    if(timer_up)
        timer_step ++;
    else if(timer_down)
        timer_step --;
    if(timer_up)
    {
        child->setVisible(true);
        child->setGeometry(center_x - center_x*timer_step/timer_max_step, center_y - center_y*timer_step/timer_max_step,
                           width()*timer_step/timer_max_step, height()*timer_step/timer_max_step);
        if(timer_step == timer_max_step)
        {
            SetVisible(false);
            QObject::killTimer(timer_up);
            timer_up = 0;
        }
    }
    else if(timer_down)
    {
        if(!timer_step)
        {
            child->setVisible(false);
            SetVisible(true);
            QObject::killTimer(timer_down);
            timer_down = 0;
            child = 0;
        }
        else
        {
            child->setGeometry(center_x - center_x*timer_step/timer_max_step, center_y - center_y*timer_step/timer_max_step,
                               width()*timer_step/timer_max_step, height()*timer_step/timer_max_step);
        }
    }
}
void CBaseWindow::OnButtonsBaseClick(unsigned n, bool s)
{
    emit BaseSignal(n);
}
void CBaseWindow::paintEvent(QPaintEvent *p)
{}
void CBaseWindow::resizeEvent(QResizeEvent *r)
{
     buttons.setGeometry(width()-buttons.width()-10, 10, buttons.width(), buttons.height());
}
