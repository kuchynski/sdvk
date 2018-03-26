#include "cspisok.h"

CSpisok::CSpisok(QString n, QString nt, QWidget *parent) : QWidget(parent), name(n), table(this),
    buttons(this)
{
    CTable::STableInit table_init;
    table_init.color_backgraund = QColor(50, 150, 200, 255);
    table_init.color_backgraund_checked = QColor(200, 200, 200, 255);
    table_init.color_backgraund_title = QColor(50, 100, 200, 255);
    table_init.color_backgraund_button = QColor(25, 80, 100, 255);
    table_init.color_line_checked = QColor(200, 200, 255, 255);
    table_init.color_text_checked = QColor(30, 30, 150, 255);
    table_init.color_text_title = QColor(255, 255, 255, 255);
    table_init.color_text = QColor(250, 250, 250, 255);
    table_init.font = this->font();
    table_init.font.setPixelSize(18);
    table_init.hieght_line = 29;
    QList<unsigned> width_line;
    width_line << 1000;//table.width();
    table_init.width_line = width_line;
    table.SetInitStruct(table_init);
    if(nt != "")
    {
        QList<QString> t;
        t << nt;
        table.SetTitle(t);
    }
   // QObject::connect(&table, SIGNAL(IAmReSize()), this, SLOT(OnButtonsClick(unsigned, bool)));

    CButtons::SButtonsInit but_init;
    but_init.direction = CButtons::SButtonsInit::edVertical;
    but_init.font = this->font();
    but_init.font.setPixelSize(25);
    but_init.color_backgraund = QColor(25, 60, 100, 255);//0, 30, 185, 255);
    but_init.color_backgraund_checked = QColor(100, 100, 255, 255);
    but_init.sglaz_const = 20;
    but_init.color_text = Qt::white;
    buttons.SetInitStruct(but_init);
    buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("+")));
    buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("ред.")));
    buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("-")));
    QObject::connect(&buttons, SIGNAL(PressButton(unsigned, bool)), this, SLOT(OnButtonsClick(unsigned, bool)));
    buttons.setGeometry(width() - 80, 40, 70, 150);
    buttons.SetFocusAll(true);
    buttons.Paint();
}
void CSpisok::OnButtonsClick(unsigned n, bool b)
{
    if(n == 2)
    {
        table.SubLine(table.GetNumberActivLine(), true);
    }
    else
    {
        if(n == 1 && !table.GetSize())
            return;
        QString str = (n == 1)? table.GetLineText(table.GetNumberActivLine())[0] : "";
        CInputTextDialog *td = new CInputTextDialog(str, param.GetSizeX(), param.GetSizeY(), this);
        if(td->exec() == QDialog::Accepted)
        {
            QList<QString> line;
            line << td->GetStr();
            if(n)
                table.SetLine(line, table.GetNumberActivLine(), true);
            else
                table.AddLine(line, true);
        }
        delete td;
    }
}
void CSpisok::paintEvent(QPaintEvent *p)
{
   // if(!QWidget::isVisible())
   //     return;
    QPainter painter;
    painter.begin(this);
    painter.drawImage(p->rect(), image_back, p->rect());
    painter.end();
}
void CSpisok::SetImageBack(const QImage &ib, const QRect &r)
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
    painter.drawText(QPoint(15, 25), name);
    painter.end();
    table.SetImageBack(image_back, table.geometry());
    repaint();
}
void CSpisok::resizeEvent(QResizeEvent *r)
{
    buttons.setGeometry(width() - 80, 40, 70, 100);
    table.setGeometry(10, 40, width() - 100, height() - 50);
    emit IAmResize();
}
void CSpisok::SetList(QList<QString> l)
{
    table.Clear();
    for(unsigned i = 0; i < l.size(); i++)
    {
        QList<QString> line;
        line << l[i];
        table.AddLine(line);
    }
    table.Paint();
}
QList<QString> CSpisok::GetList()
{
    QList<QString> ret;
    for(unsigned i = 0; i < table.GetSize(); i ++)
    {
        ret << table.GetLineText(i)[0];
    }
    return ret;
}
