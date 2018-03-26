#include "cinputtextdialog.h"
#define kol_step 10

CInputTextDialog::CInputTextDialog(const QString str, const unsigned size_x, const unsigned size_y, QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint), line_edit(this), buttons(this), timer_id(0), max_x(size_x), max_y(size_y)
{
    setVisible(false);

    QFont fontl;
    fontl.setPointSize(40);
    fontl.setBold(true);
    line_edit.setFont(fontl);
    line_edit.setText(str);

    CButtons::SButtonsInit but_init;
    but_init.direction = CButtons::SButtonsInit::edHorizontal;
    but_init.font = this->font();
    but_init.font.setPixelSize(30);
    but_init.color_backgraund = QColor(25, 60, 100, 255);//0, 30, 185, 255);
    but_init.color_backgraund_checked = QColor(100, 100, 255, 255);
    but_init.sglaz_const = 20;
    but_init.color_text = Qt::white;
    buttons.SetInitStruct(but_init);
    buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("ok")));
    buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("cancel")));
    QObject::connect(&buttons, SIGNAL(PressButton(unsigned, bool)), this, SLOT(OnButtonsClick(unsigned, bool)));
    buttons.SetFocusAll(true);
    buttons.Paint();

  //  line_edit.setGeometry((width()-700)/2 , (height()-200)/2 - 0, 700, 100);
  //  buttons.setGeometry((width()-700)/2 , (height()-200)/2 + 100, 700, 100);
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

    line_edit.setVisible(false);
    buttons.setVisible(false);
    timer_st = kol_step;
    timer_id = QObject::startTimer(20);
}
void CInputTextDialog::timerEvent(QTimerEvent *event)
{
    timer_st --;

    const unsigned x0 = max_x/2/kol_step * timer_st;
    const unsigned y0 = max_y/2/kol_step * timer_st;
    const unsigned xsize = max_x * (kol_step - timer_st) / (kol_step);
    const unsigned ysize = max_y * (kol_step - timer_st) / (kol_step);
    rect_my = QRect(x0, y0, xsize, ysize);

    setGeometry(rect_my);
    setVisible(true);

    if(timer_st == 0)
    {
        QObject::killTimer(timer_id);
        line_edit.setGeometry((width()-700)/2 , (height()-200)/2 - 0, 700, 100);
        buttons.setGeometry((width()-700)/2 , (height()-200)/2 + 100, 700, 100);
        line_edit.setVisible(true);
        buttons.setVisible(true);
    }
}
void CInputTextDialog::OnButtonsClick(unsigned n, bool b)
{
    if(n == 0)
        accept();
    else
        reject();
}
QString CInputTextDialog::GetStr() const
{
    return line_edit.text();
}
void CInputTextDialog::paintEvent(QPaintEvent *p)
{
    QPainter painter;
    painter.begin(this);
    painter.drawImage(rect(), image_my, rect_my);
    painter.end();
}
