#include "cinputdatadialog.h"
#define kol_step 10

CInputDataDialog::CInputDataDialog(const QDate date, const unsigned size_x, const unsigned size_y, QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint), calendar(this), buttons(this), timer_id(0), max_x(size_x), max_y(size_y)
{
    setVisible(false);

    calendar.setSelectedDate(date);
    calendar.setMaximumHeight(400);
    calendar.setMinimumHeight(400);
    calendar.setMinimumWidth(600);
    calendar.setMaximumWidth(600);
    calendar.setFirstDayOfWeek(Qt::Monday);
    calendar.setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    QPalette palette = calendar.palette();
    palette.setColor(QPalette::Base, QColor(0, 30, 185, 100));
    palette.setColor(QPalette::Text, QColor(255, 255, 255, 255));
    palette.setColor(QPalette::AlternateBase, QColor(0, 0, 200, 155));
    calendar.setPalette(palette);
    QFont font = this->font();
    font.setPixelSize(35);
    calendar.setFont(font);
//    QObject::connect(&calendar, SIGNAL(selectionChanged()), this, SLOT(CalendarChanged()));
    //calendar.show();

    CButtons::SButtonsInit but_init;
    but_init.direction = CButtons::SButtonsInit::edHorizontal;
    but_init.font = this->font();
    but_init.font.setPixelSize(30);
    but_init.color_backgraund = QColor(25, 60, 100, 255);//0, 30, 185, 255);
    but_init.color_backgraund_checked = QColor(100, 100, 255, 255);
    but_init.sglaz_const = 20;
    but_init.color_text = Qt::white;
    but_init.color_text_checked = Qt::white;
    buttons.SetInitStruct(but_init);
    buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("ok")));
    buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("cancel")));
    QObject::connect(&buttons, SIGNAL(PressButton(unsigned, bool)), this, SLOT(OnButtonsClick(unsigned, bool)));
    buttons.SetFocusAll(true);

  //  calendar.setGeometry((width()-600)/2 , (height()-500)/2, 600, 400);
  //  buttons.setGeometry((width()-600)/2 , (height()-500)/2 + 400, 600, 100);

    QRect rect1(0, 0, size_x, size_y);
    image_my = QImage(size_x, size_y, QImage::Format_RGB32);
    QPainter painter;
    painter.begin(&image_my);
    QLinearGradient gradient(0, 0, 0, height());
    painter.setBrush(Qt::gray);
    painter.drawRect(rect1);
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
    painter.end();

    calendar.setVisible(false);
    buttons.setVisible(false);
    timer_st = kol_step;
    timer_id = QObject::startTimer(20);
}
void CInputDataDialog::timerEvent(QTimerEvent *event)
{
    timer_st --;

    const unsigned x0 = max_x/2/kol_step * timer_st;
    const unsigned y0 = max_y/2/kol_step * timer_st;
    const unsigned xsize = max_x * (kol_step - timer_st) / (kol_step);
    const unsigned ysize = max_y * (kol_step - timer_st) / (kol_step);
    rect_my = QRect(x0, y0, xsize, ysize);

    setGeometry(rect_my);
    setVisible(true);
   // setGeometry(x0, y0, xsize, ysize);

    if(timer_st == 0)
    {
        QObject::killTimer(timer_id);
        calendar.setGeometry((width()-600)/2 , (height()-500)/2, 600, 400);
        buttons.setGeometry((width()-600)/2 , (height()-500)/2 + 400, 600, 100);
        calendar.setVisible(true);
        buttons.setVisible(true);
    }
}
void CInputDataDialog::OnButtonsClick(unsigned n, bool b)
{
    if(n == 0)
        accept();
    else
        reject();
}
QDate CInputDataDialog::GetDate() const
{
    return calendar.selectedDate();
}
void CInputDataDialog::paintEvent(QPaintEvent *p)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(rect(), image_my, rect_my);
    painter.end();
}
