#include "cimagedefect.h"

#define image_width 340
#define image_height 225
#define buttons_height 40

CImageDefect::CImageDefect(QWidget *parent) : QWidget(parent)// Qt::FramelessWindowHint),
{
    setMinimumSize(image_width + image_height*2, 225 + buttons_height);
    CButtonsCheck::SButtonsInit but_init;
    but_init.direction = CButtonsCheck::SButtonsInit::edHorizontal;
    but_init.font = this->font();
    but_init.font.setPixelSize(30);
    but_init.style_background = CButtonsCheck::SButtonsInit::ebColor;
    but_init.color_backgraund = QColor(25, 60, 100, 255);//0, 30, 185, 255);
    but_init.color_backgraund_checked = QColor(100, 100, 255, 255);
    but_init.sglaz_const = 20;
    but_init.color_text = Qt::white;
    buttons = new CButtonsCheck(this);
    buttons->SetInitStruct(but_init);
    buttons->AddButton(CButtonsCheck::SButton(QString::fromLocal8Bit("1-9")));
    buttons->AddButton(CButtonsCheck::SButton(QString::fromLocal8Bit("1")));
    buttons->AddButton(CButtonsCheck::SButton(QString::fromLocal8Bit("2")));
    buttons->AddButton(CButtonsCheck::SButton(QString::fromLocal8Bit("3")));
    buttons->AddButton(CButtonsCheck::SButton(QString::fromLocal8Bit("4")));
    buttons->AddButton(CButtonsCheck::SButton(QString::fromLocal8Bit("5")));
    buttons->AddButton(CButtonsCheck::SButton(QString::fromLocal8Bit("6")));
    buttons->AddButton(CButtonsCheck::SButton(QString::fromLocal8Bit("7")));
    buttons->AddButton(CButtonsCheck::SButton(QString::fromLocal8Bit("8")));
    buttons->AddButton(CButtonsCheck::SButton(QString::fromLocal8Bit("9")));
    QObject::connect(buttons, SIGNAL(PressButton(unsigned, bool)), this, SLOT(OnButtonsClick(unsigned, bool)));
//    buttons->setMinimumSize(600, 50);
    buttons->setGeometry(0, 0, width(), buttons_height);
    buttons->SetFocusAll(true);
    buttons->Paint();

    buttons->SetChecked(0);
    OnButtonsClick(0, true);
}
void CImageDefect::SetMapOfDatchik(CMapOfDatchik l, CMapOfDatchik r)
{
    left = l;
    right = r;
    Paint();
}
void CImageDefect::Paint()
{
    const int datchik = (buttons->GetChecked())? buttons->GetChecked() - 1 : 9;
    image = QImage(QSize(width(), height()), QImage::Format_RGB32);
    QPainter painter(&image);
    painter.drawImage(QRect(0, 0, width(), height()), image_back, QRect(0, 0, width(), height()));
/*    QLinearGradient gradient(0, 0, 0, height());
    QRect rect1(0, 0, image.width(), image.height());
    painter.setBrush(Qt::gray);
    painter.drawRect(rect1);
    QColor cg = QColor(50, 150, 200, 255);
    int stap_gr[8] = {200, 100, 150, 220, 220, 255, 100};
    for(int i = 0; i < 7; i ++)
    {
        cg.setAlpha(stap_gr[i]);
        gradient.setColorAt((double)i / 6.0, cg);
    }
    painter.setPen(QPen(cg));
    painter.setBrush(gradient);
    painter.drawRect(rect1);*/

    QImage image_dat;
    switch(datchik)
    {
        case 0: image_dat = QImage("k1.png"); break;
        case 1: image_dat = QImage("k2.png"); break;
        case 2: image_dat = QImage("k3.png"); break;
        case 3: image_dat = QImage("k4.png"); break;
        case 4: image_dat = QImage("k5.png"); break;
        case 5: image_dat = QImage("k6.png"); break;
        case 6: image_dat = QImage("k7.png"); break;
        case 7: image_dat = QImage("k8.png"); break;
        case 8: image_dat = QImage("k9.png"); break;
        case 9: image_dat = QImage("k0.png"); break;
    }
    painter.drawImage(QRect(image_height, buttons->height(), image_width, image_height), image_dat);
    painter.end();
    QRect rect_left(0, buttons->height(), image_height, image_height);
    left.PaintOnScreen(image, rect_left, datchik, 0);
    QRect rect_right(image_height + image_width, buttons->height(), image_height, image_height);
    right.PaintOnScreen(image, rect_right, datchik, 0);
    repaint();
}
void CImageDefect::OnButtonsClick(unsigned n, bool b)
{
    Paint();
}
void CImageDefect::resizeEvent(QResizeEvent *r)
{
    emit IAmReSize();
}
void CImageDefect::SetImageBack(const QImage &ib, const QRect &r)
{
    image_back = QImage(width(), height(), QImage::Format_RGB32);
    QPainter painter(&image_back);
    painter.drawImage(rect(), ib, r);
    painter.end();
    Paint();
}
void CImageDefect::paintEvent(QPaintEvent *p)
{
    if(!QWidget::isVisible())
        return;
    QPainter painter(this);
    painter.drawImage(p->rect(), image, p->rect());
    painter.end();
}
