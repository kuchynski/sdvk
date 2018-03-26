#include "cbdprintday.h"

CBdPrintDay::CBdPrintDay(QWidget *parent) : QWidget(parent), buttons(this), table_defectoskopist(this),
    label_date(this), label_def(this)
{
    CButtons::SButtonsInit but_init;
    but_init.direction = CButtons::SButtonsInit::edHorizontal;
    but_init.font = this->font();
    but_init.color_backgraund = QColor(25, 80, 100, 255);//0, 30, 185, 255);
    but_init.color_backgraund_checked = QColor(100, 100, 255, 255);
    but_init.sglaz_const = 20;
    but_init.color_text = Qt::white;
    but_init.color_text_checked = Qt::white;
    but_init.font.setPixelSize(15);
    buttons.SetInitStruct(but_init);
    QObject::connect(&buttons, SIGNAL(PressButton(unsigned, bool)), this, SLOT(OnButtonsClick(unsigned, bool)));

    CTable::STableInit table_init;
    table_init.color_backgraund = QColor(50, 150, 200, 255);
    table_init.color_backgraund_checked = QColor(200, 200, 200, 255);
    table_init.color_backgraund_title = QColor(50, 100, 200, 255);
    table_init.color_backgraund_button = QColor(25, 80, 100, 255);
    table_init.color_line_checked = QColor(200, 200, 255, 255);
    table_init.color_text_checked = QColor(250, 250, 250, 255);
    table_init.color_text_title = QColor(255, 255, 255, 255);
    table_init.color_text = QColor(250, 250, 250, 255);
    table_init.font = this->font();
    table_init.font.setPixelSize(18);
    table_init.hieght_line = 29;
    QList<unsigned> width_line;
    width_line << 200 << 50;//table.width();
    table_init.width_line = width_line;
    table_defectoskopist.SetInitStruct(table_init);
    table_defectoskopist.setGeometry(QRect(50, 200, 250, 200));
    QObject::connect(&table_defectoskopist, SIGNAL(ClickLine(unsigned)), this, SLOT(OnClickLineTablet(unsigned)));


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
    label_date.setAlignment(Qt::AlignHCenter);
    label_date.setFont(fontl);
    label_date.setPalette(palette7);
    label_date.setText(QString::fromLocal8Bit(""));
    fontl.setPointSize(16);
    label_def.setFont(fontl);
    label_def.setPalette(palette7);
    label_def.setGeometry(55, 170, 190, 20);
    label_def.setText(QString::fromLocal8Bit("Дефектоскопист"));
}
void CBdPrintDay::Run(QDate d, CStack <CWheel> &w)
{
    date = d;
    label_date.setText(QString::fromLocal8Bit("Отчёт за ") + date.toString("dd.MM.yyyy") + QString::fromLocal8Bit(" г."));
    wheels = w;
    table_defectoskopist.Clear();
    if(wheels.GetSize())
    {
        label_def.setVisible(true);
        QList<QString> line;
        line << QString::fromLocal8Bit("Все") <<  QString::number(wheels.GetSize());
        table_defectoskopist.AddLine(line);
        QList<QString> l = param.GetListDefectoskopist();
        for(unsigned i = 0; i < l.size(); i++)
        {
            unsigned kol = 0;
            for(unsigned j = 0; j < wheels.GetSize(); j ++)
                if(wheels[j].GetOperating() == l[i])
                    kol ++;
            QList<QString> line;
            line << l[i] << QString::number(kol);
            table_defectoskopist.AddLine(line);
        }
        table_defectoskopist.SetChecked(param.GetSelectDefectoskopist(1));
        table_defectoskopist.Paint();
    }
    else
        label_def.setVisible(false);
    SetButtons();
}
void CBdPrintDay::SetButtons()
{
    buttons.SubButton();
    buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("<< Назад")));
    const QString str_kol = table_defectoskopist.GetPoleText(table_defectoskopist.GetNumberActivLine(), 1);
    if(wheels.GetSize() && str_kol != "" && str_kol != "0")
    {
        buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("Настройка принтера")));
        buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("Печать")));
        buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("Создать pdf")));
    }
    buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("Отчёт за период >>")));
    buttons.SetFocusAll(true);
    buttons.Paint();
}
void CBdPrintDay::OnClickLineTablet(unsigned n)
{
    param.SetSelectDefectoskopist(1, n);
    SetButtons();
}
void CBdPrintDay::OnButtonsClick(unsigned n, bool b)
{
    if(buttons.GetSize() == 2 && n == 1)
        n = 4;
    switch(n)
    {
        case 0: case 4: emit OnPressButton(n); break;
        case 1: PrintDiallog(); break;
        case 2: PrintWheels(); break;
        case 3: PrintPdfWheels(); break;
    }
}
void CBdPrintDay::PrintDiallog()
{
    QPrintDialog print_diallog(&printer, this);
    print_diallog.setMinMax(1, 1);
    printer.setOrientation(QPrinter::Landscape);
    printer.setPageSize(QPrinter::A4);
    print_diallog.exec();
}
void CBdPrintDay::PrintWheels()
{
    printer.setOrientation(QPrinter::Landscape);
    printer.setPageSize(QPrinter::A4);
    printer.setDocName("SDVK " + date.toString("yyyy.MM.dd"));
    Print(&printer);
}
void CBdPrintDay::PrintPdfWheels()
{
    QPrinter printer_pdf;
    printer_pdf.setOrientation(QPrinter::Landscape);
    printer_pdf.setPageSize(QPrinter::A4);
    printer_pdf.setOutputFormat(QPrinter::PdfFormat);
    printer_pdf.setOutputFileName("SDVK " + date.toString("yyyy.MM.dd") + ".pdf");
    printer_pdf.setDocName("SDVK " + date.toString("yyyy.MM.dd"));
    Print(&printer_pdf, true);
}
void CBdPrintDay::Print(QPrinter *printer, const bool pdf)
{
    QPainter painter(printer);
    QRect rect(painter.viewport());

    const double bw = rect.width();// GetDeviceCaps(prn->Handle, HORZRES);
    const double bh = rect.height();// GetDeviceCaps(prn->Handle, VERTRES);
    const double width = 290;//GetDeviceCaps(prn->Handle, HORZSIZE);
    const double height = 210;//GetDeviceCaps(prn->Handle, VERTSIZE);
    const double mmw = bw / width;
    const double mmh = bh / height;
    const double mmpole = width / 290;
    QFont font(painter.font());

    painter.setBrush(Qt::white);
    QPen pen(Qt::black);
    if(pdf)
        pen.setWidth(1);
    painter.setPen(pen);

    unsigned kol_whell = wheels.GetSize();
    int y_line = 20;
    const double y_step = 7;
    bool new_page = true;
    int kol_page = 1;
    font.setPointSize(14); painter.setFont(font);
    QString defectoskopist = table_defectoskopist.GetPoleText(table_defectoskopist.GetNumberActivLine(), 0);
    QString str_def = QString::fromLocal8Bit("Дата ") + date.toString("dd.MM.yyyy")
            + QString::fromLocal8Bit("г.     Дефектоскопист ");
    if(defectoskopist != QString::fromLocal8Bit("Все"))
        str_def += defectoskopist;
    painter.drawText(mmpole*0*mmw, 7*mmh, str_def);
    font.setPointSize(10); painter.setFont(font);
    const int xd[2][8] = {{60, 68, 80, 92, 100, 108, 116, 128},
                          {140, 148, 160, 172, 180, 188, 196, 208}};
    unsigned i2 = 0;
    for(unsigned i = 0; i < kol_whell; i ++)
    {        
        if((defectoskopist != QString::fromLocal8Bit("Все")) && (defectoskopist != wheels[i].GetOperating()))
            continue;
        i2 ++;
        if(new_page)//шапка
        {
            painter.drawText(mmpole*3*mmw, (y_line+8)*mmh, QString::fromLocal8Bit("№"));
            painter.drawText(mmpole*2*mmw, (y_line+14)*mmh, QString::fromLocal8Bit("п/п"));
            painter.drawText(mmpole*14*mmw, (y_line+4)*mmh, QString::fromLocal8Bit("Номер"));
            painter.drawText(mmpole*11*mmw, (y_line+10)*mmh, QString::fromLocal8Bit("колёсной"));
            painter.drawText(mmpole*15*mmw, (y_line+16)*mmh, QString::fromLocal8Bit("пары"));
            painter.drawText(mmpole*30*mmw, (y_line+10)*mmh, QString::fromLocal8Bit("время"));
            painter.drawText(mmpole*42*mmw, (y_line+4)*mmh, QString::fromLocal8Bit("Диаметр"));
            painter.drawText(mmpole*43*mmw, (y_line+10)*mmh, QString::fromLocal8Bit("колеса,"));
            painter.drawText(mmpole*47*mmw, (y_line+16)*mmh, QString::fromLocal8Bit("мм"));
            painter.drawText(mmpole*85*mmw, (y_line+1)*mmh, QString::fromLocal8Bit("Левая сторона"));
            painter.drawText(mmpole*164*mmw, (y_line+1)*mmh, QString::fromLocal8Bit("Правая сторона"));
            painter.drawText(mmpole*74*mmw, (y_line+8)*mmh, QString::fromLocal8Bit("1 оборот"));
            painter.drawText(mmpole*114*mmw, (y_line+8)*mmh, QString::fromLocal8Bit("2 оборот"));
            painter.drawText(mmpole*154*mmw, (y_line+8)*mmh, QString::fromLocal8Bit("1 оборот"));
            painter.drawText(mmpole*194*mmw, (y_line+8)*mmh, QString::fromLocal8Bit("2 оборот"));
            painter.drawText(mmpole*61*mmw, (y_line+15)*mmh, QString::fromLocal8Bit("Обод"));
            painter.drawText(mmpole*74*mmw, (y_line+15)*mmh, QString::fromLocal8Bit("Гребень"));
            painter.drawText(mmpole*93*mmw, (y_line+15)*mmh, QString::fromLocal8Bit("Диск"));
            painter.drawText(mmpole*109*mmw, (y_line+15)*mmh, QString::fromLocal8Bit("Обод"));
            painter.drawText(mmpole*122*mmw, (y_line+15)*mmh, QString::fromLocal8Bit("Гребень"));
            painter.drawText(mmpole*141*mmw, (y_line+15)*mmh, QString::fromLocal8Bit("Обод"));
            painter.drawText(mmpole*154*mmw, (y_line+15)*mmh, QString::fromLocal8Bit("Гребень"));
            painter.drawText(mmpole*173*mmw, (y_line+15)*mmh, QString::fromLocal8Bit("Диск"));
            painter.drawText(mmpole*189*mmw, (y_line+15)*mmh, QString::fromLocal8Bit("Обод"));
            painter.drawText(mmpole*202*mmw, (y_line+15)*mmh, QString::fromLocal8Bit("Гребень"));
            painter.drawText(mmpole*xd[0][0]*mmw, (y_line+22)*mmh, "1");
            painter.drawText(mmpole*xd[0][1]*mmw, (y_line+22)*mmh, "2");
            painter.drawText(mmpole*xd[0][2]*mmw, (y_line+22)*mmh, "3");
            painter.drawText(mmpole*xd[0][3]*mmw, (y_line+22)*mmh, "4");
            painter.drawText(mmpole*xd[0][4]*mmw, (y_line+22)*mmh, "5");
            painter.drawText(mmpole*xd[0][5]*mmw, (y_line+22)*mmh, "1");
            painter.drawText(mmpole*xd[0][6]*mmw, (y_line+22)*mmh, "2");
            painter.drawText(mmpole*xd[0][7]*mmw, (y_line+22)*mmh, "3");
            painter.drawText(mmpole*xd[1][0]*mmw, (y_line+22)*mmh, "1");
            painter.drawText(mmpole*xd[1][1]*mmw, (y_line+22)*mmh, "2");
            painter.drawText(mmpole*xd[1][2]*mmw, (y_line+22)*mmh, "3");
            painter.drawText(mmpole*xd[1][3]*mmw, (y_line+22)*mmh, "4");
            painter.drawText(mmpole*xd[1][4]*mmw, (y_line+22)*mmh, "5");
            painter.drawText(mmpole*xd[1][5]*mmw, (y_line+22)*mmh, "1");
            painter.drawText(mmpole*xd[1][6]*mmw, (y_line+22)*mmh, "2");
            painter.drawText(mmpole*xd[1][7]*mmw, (y_line+22)*mmh, "3");
            painter.drawText(mmpole*219*mmw, (y_line+8)*mmh, QString::fromLocal8Bit("Заклю-"));
            painter.drawText(mmpole*220*mmw, (y_line+14)*mmh, QString::fromLocal8Bit("чение"));
            painter.drawText(mmpole*240*mmw, (y_line+10)*mmh, QString::fromLocal8Bit("Примечание"));
            painter.drawText(mmpole*272*mmw, (y_line+10)*mmh, QString::fromLocal8Bit("Подпись"));

            PaintCells(painter, 3, y_line-y_step/2, y_line+y_step/2, mmpole, mmw, mmh);
            y_line+=y_step;
            PaintCells(painter, 2, y_line-y_step/2, y_line+y_step/2, mmpole, mmw, mmh);
            y_line+=y_step;
            PaintCells(painter, 1, y_line-y_step/2, y_line+y_step/2, mmpole, mmw, mmh);
            y_line+=y_step;
            PaintCells(painter, 0, y_line-y_step/2, y_line+y_step/2, mmpole, mmw, mmh);
            y_line+=y_step;
            new_page = false;
        }
        painter.drawText(mmpole*2*mmw, (y_line+1)*mmh, QString::number(i2));
        painter.drawText(mmpole*10*mmw, (y_line+1)*mmh, wheels[i].GetNumberKP());
        painter.drawText(mmpole*30*mmw, (y_line+1)*mmh, wheels[i].GetTime());
        painter.drawText(mmpole*46*mmw, (y_line+1)*mmh, QString::number(wheels[i].GetDiameterLeft()));

        for(unsigned s = 0; s <= 1; s++)
        {
            for(unsigned d = 0; d < 5; d++)
                if(wheels[i].IsDefect(s, d, 0))
                    painter.drawText(mmpole*xd[s][d]*mmw, (y_line+1)*mmh, "+");
            for(unsigned d = 0; d < 3; d++)
                if(wheels[i].IsDefect(s, d, 1))
                    painter.drawText(mmpole*xd[s][d+5]*mmw, (y_line+1)*mmh, "+");
        }

        QString str_defect = (wheels[i].GetDefect())? QString::fromLocal8Bit(" брак") : QString::fromLocal8Bit("годен");
        painter.drawText(mmpole*220*mmw, (y_line+1)*mmh, str_defect);
        painter.drawText(mmpole*233*mmw, (y_line+1)*mmh, wheels[i].GetPS());

        PaintCells(painter, 0, y_line-y_step/2, y_line+y_step/2, mmpole, mmw, mmh);
        y_line+=y_step;
        if(y_line > 200)
        {
            font.setPointSize(8); painter.setFont(font);
            painter.drawText(mmpole*2*mmw, (y_line+1)*mmh, QString::fromLocal8Bit("Примечание: \"+\" - превышение уровня браковочной чувствительности"));
            font.setPointSize(10); painter.setFont(font);
            printer->newPage();
            y_line = 10;
            new_page = true;
        }
    }
    if(!new_page)
    {
        font.setPointSize(8); painter.setFont(font);
        painter.drawText(mmpole*2*mmw, (y_line+1)*mmh, QString::fromLocal8Bit("Примечание: \"+\" - превышение уровня браковочной чувствительности"));
    }
}

void CBdPrintDay::PaintCells(QPainter &painter, const int kind, const double &y1, const double &y2, const double &mmpole, const double &mmw, const double &mmh)
{
    const int x_vert[24] = {0, 9, 19, 13, 16, 8, 8, 16, 8, 8, 8, 8, 16, 8, 8, 16, 8, 8, 8, 8, 16, 15, 35, 22};
    const int x_en[4][24] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                             {1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
                             {1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1},
                             {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1}};
    int begin_x = 0;
    int begin_x4 = 0;
    int end_x = begin_x;
    int end_x20 = 0;
    for(unsigned i = 0; i < 24; i++)
    {
        const double x = mmpole * (end_x + x_vert[i]);
        end_x += x_vert[i];
        if(i == 4)
            begin_x4 = end_x;
        if(i == 20)
            end_x20 = end_x;
        if(!x_en[kind][i])
            continue;
        painter.drawLine(x*mmw, (y1-1)*mmh, x*mmw, (y2-1)*mmh);
    }
    if(kind == 3)
        painter.drawLine((mmpole*begin_x)*mmw,  (y1-1)*mmh, (mmpole*end_x)*mmw, (y1-1)*mmh);
    if(kind)
        painter.drawLine((mmpole*begin_x4)*mmw,  (y2-1)*mmh, (mmpole*end_x20)*mmw, (y2-1)*mmh);
    else
        painter.drawLine((mmpole*begin_x)*mmw,  (y2-1)*mmh, (mmpole*end_x)*mmw, (y2-1)*mmh);
}
void CBdPrintDay::SetImageBack(const QImage &ib, const QRect &r)
{
    image_back = QImage(width(), height(), QImage::Format_RGB32);
    QPainter painter(&image_back);
    painter.drawImage(rect(), ib, r);
   // QFont font;
  //  font.setBold(true);
  //  painter.setPen(Qt::white);
  //  font.setPointSize(16);
  //  painter.setFont(font);
  //  painter.drawText(QPoint(50, 170), QString::fromLocal8Bit("Дефектоскопист"));
    painter.end();
    buttons.setGeometry(QRect(10, 65, width() - 20, 50));
    buttons.SetImageBack(image_back, buttons.geometry());
    table_defectoskopist.SetImageBack(image_back, table_defectoskopist.geometry());
}
void CBdPrintDay::resizeEvent(QResizeEvent *r)
{
    emit IAmReSize();
    label_date.setGeometry(QRect(200, 15, width() - 400, 40));
}
void CBdPrintDay::paintEvent(QPaintEvent *p)
{
  //  if(!QWidget::isVisible())
    //    return;
    QPainter painter;
    painter.begin(this);
    painter.drawImage(p->rect(), image_back, p->rect());
    painter.end();
}
