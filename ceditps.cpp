#include "ceditps.h"

CEditPs::CEditPs(QString str, int spb, QWidget *parent) : QWidget(parent), check(0)
{
    QFont fontl;
    fontl.setPointSize(30);
    fontl.setBold(true);
    line_edit = new QLineEdit(this);
    line_edit->setFont(fontl);
    line_edit->setText(str);

    CChecks::SButtonsInit chek_init;
    chek_init.style_background = CChecks::SButtonsInit::ebPicture;
    check = new CChecks(this);
    QImage imagea1("OK1.png");
    QImage imagea2("OK2.png");
    check->AddButton(QString(""), imagea2, imagea1);
    check->SetChecked(0, spb == 1);
    check->SetInitStruct(chek_init);

    CTable::STableInit table_init;
    table_init.color_backgraund = QColor(50, 150, 200, 255);
//    table_init.color_backgraund = QColor(50, 150, 200, 255);
//    table_init.color_backgraund_checked = QColor(150, 155, 255, 255);
    table_init.color_backgraund_checked = QColor(50, 150, 200, 255);
//    table_init.color_backgraund_checked = QColor(200, 200, 200, 255);
    table_init.color_backgraund_title = QColor(50, 100, 200, 255);
    table_init.color_backgraund_button = QColor(25, 80, 100, 255);
    table_init.color_line_checked = QColor(50, 150, 200, 255);
    table_init.color_text_checked = QColor(50, 50, 100, 255);
    table_init.color_text_title = QColor(200, 200, 200, 255);
    table_init.color_text = QColor(50, 50, 100, 255);
//    table_init.color_backgraund_button = QColor(50, 100, 255, 255);
    table_init.font = this->font();
    table_init.font.setPixelSize(18);
    table_init.hieght_line = 29;
    QList<unsigned> width_line;
    width_line << 1000;//table.width();
    table_init.width_line = width_line;
    table = new CTable(this);
    table->SetInitStruct(table_init);
    QList<QString> t;
    t << QString::fromLocal8Bit("стандартное примечание");
    table->SetTitle(t);
    QObject::connect(table, SIGNAL(ClickLine(unsigned)), this, SLOT(OnTableClickLine(unsigned)));
    //table->Clear();
    QList<QString> list_ps = param.GetListPs();
    for(unsigned i = 0; i < list_ps.size(); i++)
    {
        QList<QString> line;
        line << list_ps[i];
        table->AddLine(line);
    }

    check->setGeometry(5, 30, 50, 50);
    line_edit->setGeometry(5, 135, 500, 50);
    table->setGeometry(510, 55, 300, 200);
}
void CEditPs::OnTableClickLine(unsigned n)
{
    QList<QString> list = table->GetLineText(n);
    line_edit->setText(list[0]);
}
int CEditPs::GetCheck() const
{
    return (check->GetChecked(0))? 1 : 0;
}
QString CEditPs::GetStr() const
{
    return line_edit->text();
}
void CEditPs::SetImageBack(const QImage &ib, const QRect &r)
{
    image_back = QImage(width(), height(), QImage::Format_RGB32);
    QPainter painter(&image_back);
    painter.drawImage(rect(), ib, r);
    painter.end();
}
void CEditPs::Clear()
{
    line_edit->setText("");
    check->SetChecked(0, false);
}
void CEditPs::resizeEvent(QResizeEvent *r)
{
    table->setGeometry(line_edit->width() + 15, 5, width() - 15 - line_edit->width(), height() - 10);
    table->SetImageBack(image_back, table->geometry());
    check->SetImageBack(image_back, check->geometry());
}
void CEditPs::paintEvent(QPaintEvent *p)
{
   // if(!QWidget::isVisible())
   //     return;
    QPainter painter(this);
    painter.drawImage(p->rect(), image_back, p->rect());
    painter.setPen(QPen(Qt::white));
    painter.setBrush(Qt::NoBrush);
    QFont font;
    font.setPointSize(16);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QPoint(5, 20), QString::fromLocal8Bit("состояние"));
    painter.drawText(QPoint(5, 110), QString::fromLocal8Bit("примечание"));
    painter.end();
}
