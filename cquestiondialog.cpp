#include "cquestiondialog.h"
#define kol_step 10

CQuestionDialog::CQuestionDialog(const QList<QString> str, const QList<QString> but, const unsigned wid, const unsigned size_x, const unsigned size_y, QWidget *parent) :
    QDialog(parent, Qt::FramelessWindowHint), buttons(this), label(this), timer_id(0), max_x(size_x), max_y(size_y),
    wid_my(wid)
{
    setVisible(false);

    CButtons::SButtonsInit but_init;
    but_init.direction = CButtons::SButtonsInit::edHorizontal;
    but_init.font = this->font();
    but_init.font.setPixelSize(30);
    but_init.color_backgraund = QColor(25, 60, 100, 255);//0, 30, 185, 255);
    but_init.color_backgraund_checked = QColor(100, 100, 255, 255);
    but_init.sglaz_const = 20;
    but_init.color_text = Qt::white;
    buttons.SetInitStruct(but_init);
    for(unsigned i = 0; i < but.size(); i++)
        buttons.AddButton(CButtons::SButton(but[i]));
    QObject::connect(&buttons, SIGNAL(PressButton(unsigned, bool)), this, SLOT(OnButtonsClick(unsigned, bool)));
    buttons.SetFocusAll(true);
    buttons.Paint();

    QPalette palette7;
    QBrush brush7(QColor(255, 255, 255, 255));
    brush7.setStyle(Qt::SolidPattern);
    palette7.setBrush(QPalette::Active, QPalette::WindowText, brush7);
    palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
    palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush7);
    QFont fontl;
    fontl.setPointSize(24);
    fontl.setBold(true);
    fontl.setWeight(75);
   // label.setAlignment(Qt::AlignHCenter);
    label.setFont(fontl);
    label.setPalette(palette7);

    QString str_label;
    unsigned kol = 1;
    for(unsigned i = 0; i < str.size(); i++, kol ++)
    {
        str_label += str[i];
        if(i < (str.size() - 1))
            str_label += "\n";
    }
    label.setText(str_label);
    height_label = kol * 40;

//    label.setGeometry((width()-wid)/2 , (height()-height_label-100)/2, wid, height_label);
  //  buttons.setGeometry((width()-wid)/2 , (height()-height_label-100)/2 + height_label, wid, 100);
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

    label.setVisible(false);
    buttons.setVisible(false);
    timer_st = kol_step;
    timer_id = QObject::startTimer(20);

}
void CQuestionDialog::timerEvent(QTimerEvent *event)
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
        label.setGeometry((width()-wid_my)/2 , (height()-height_label-100)/2, wid_my, height_label);
        buttons.setGeometry((width()-wid_my)/2 , (height()-height_label-100)/2 + height_label, wid_my, 100);
        label.setVisible(true);
        buttons.setVisible(true);
    }
}
void CQuestionDialog::OnButtonsClick(unsigned n, bool b)
{
    ret = n;
    if(n == 0)
        accept();
    else
        reject();
}
void CQuestionDialog::paintEvent(QPaintEvent *p)
{
    QPainter painter;
    painter.begin(this);
    QLinearGradient gradient(0, 0, 0, height());
    QRect rect1(0, 0, width(), height());
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
    painter.drawRect(rect());
    painter.end();
}
