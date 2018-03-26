#include "cinputmain.h"

CInputMain::CInputMain(QWidget *parent) : CBaseWindow(QString::fromLocal8Bit("ok"), QString::fromLocal8Bit(""), parent),
    input(this)
{
}
void CInputMain::Run()
{
    input.Run();
}
void CInputMain::OnNewWheel(const CWheel &w)
{
    emit NewWheel(w);
}
void CInputMain::OnButtonsBaseClick(unsigned n, bool s)
{
    input.Stop();
    CBaseWindow::OnButtonsBaseClick(n, s);
}
void CInputMain::paintEvent(QPaintEvent *p)
{
    if(!QWidget::isVisible())
        return;
    QPainter painter;
    painter.begin(this);
    painter.drawImage(p->rect(), image_my, p->rect());
    painter.end();
    CBaseWindow::paintEvent(p);
}
void CInputMain::resizeEvent(QResizeEvent *r)
{
    CBaseWindow::resizeEvent(r);
    QPainter painter;
    image_my = QImage(width(), height(), QImage::Format_RGB32);
    painter.begin(&image_my);
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
    painter.drawRect(rect1);
    painter.setPen(QPen(Qt::white));
    painter.setBrush(Qt::NoBrush);
    QRect rect2(0, 0, width()-1, height()-1);
    painter.drawRoundedRect(rect2, 5, 5);
    QFont font;
    font.setPointSize(30);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QPoint(50, 50), QString::fromLocal8Bit("Сканирование"));
    painter.end();

    input.setGeometry(0, 70, width(), height() - 70);
    input.SetImageBack(image_my, input.geometry());
}

