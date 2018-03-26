#include "cenableddatchik.h"

CEnabledDatchik::CEnabledDatchik(QWidget *parent) :
    QWidget(parent)
{
    CChecks::SButtonsInit chek_init;
    chek_init.style_background = CChecks::SButtonsInit::ebPicture;
    chek_init.direction = CChecks::SButtonsInit::edVertical;
//    chek_init.font = this->font();
  //  chek_init.font.setPixelSize(15);
    chek_init.color_backgraund = QColor(255, 255, 255, 0);
   // chek_init.color_backgraund_checked = QColor(100, 100, 255, 255);
   // chek_init.color_text = Qt::white;
    QImage imagea1("OK1.png");
    QImage imagea2("OK2.png");
    for(unsigned i = 0; i < 2; i ++)
    {
        checks[i] = new CChecks(this);
        checks[i]->AddButton(QString(""), imagea1, imagea2);
        checks[i]->AddButton(QString(""), imagea1, imagea2);
        checks[i]->AddButton(QString(""), imagea1, imagea2);
        checks[i]->AddButton(QString(""), imagea1, imagea2);
        checks[i]->AddButton(QString(""), imagea1, imagea2);
        checks[i]->AddButton(QString(""), imagea1, imagea2);
        checks[i]->AddButton(QString(""), imagea1, imagea2);
        checks[i]->AddButton(QString(""), imagea1, imagea2);
        checks[i]->AddButton(QString(""), imagea1, imagea2);
        for(unsigned j = 0; j < 9; j++)
            checks[i]->SetChecked(j, (param.GetEnabledDat(i, i)));
        checks[i]->SetInitStruct(chek_init);
       // checks[i]->SetFocusAll(true);
    }
    checks[0]->setGeometry(155, 70, 45, 405);
    checks[1]->setGeometry(305, 70, 45, 405);
}
void CEnabledDatchik::SetImageBack(const QImage &ib, const QRect &r)
{
    image_back = QImage(width(), height(), QImage::Format_RGB32);
    QPainter painter(&image_back);
    painter.drawImage(rect(), ib, r);
    painter.setPen(QPen(Qt::white));
    painter.setBrush(Qt::NoBrush);
    QRect rect2(0, 0, width()-1, height()-1);
    painter.drawRoundedRect(rect2, 5, 5);
    QFont font;
    font.setPointSize(16);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QPoint(15, 25), QString::fromLocal8Bit("датчик"));
    painter.drawText(QPoint(210, 25), QString::fromLocal8Bit("оборот"));
    painter.drawText(QPoint(170, 50), QString::fromLocal8Bit("1"));
    painter.drawText(QPoint(320, 50), QString::fromLocal8Bit("2"));
    for(unsigned i = 1; i <= 9; i++)
        painter.drawText(QPoint(45, 50 + i*45), QString::number(i));
    painter.setPen(QPen(QColor(150, 150, 255, 255)));
    painter.drawLine(75, 60, width() - 6, 60);
    painter.drawLine(100, 5, 100,  height() - 6);
    painter.drawLine(250, 40, 250, height() - 6);
    painter.end();

    checks[0]->SetImageBack(image_back, checks[0]->geometry());
    checks[1]->SetImageBack(image_back, checks[1]->geometry());
    repaint();
}
void CEnabledDatchik::paintEvent(QPaintEvent *p)
{
   // if(!QWidget::isVisible())
     //   return;
    QPainter painter;
    painter.begin(this);
    painter.drawImage(p->rect(), image_back, p->rect());
    painter.end();
    QWidget::paintEvent(p);
}
void CEnabledDatchik::resizeEvent(QResizeEvent *r)
{
    IAmResize();
}
void CEnabledDatchik::SetData(const unsigned dat, const unsigned oborot, const unsigned state)
{
    if(dat > 9 | oborot > 1)
        return;
    checks[oborot]->SetChecked(dat, state > 0);
}
unsigned CEnabledDatchik::GetData(const unsigned dat, const unsigned oborot) const
{
    if(dat > 9 | oborot > 1)
        return 0;
    return (checks[oborot]->GetChecked(dat))? 1 : 0;
}
