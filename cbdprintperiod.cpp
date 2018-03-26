#include "cbdprintperiod.h"

CBdPrintPeriod::CBdPrintPeriod(QWidget *parent): QWidget(parent), buttons(this), table_defectoskopist(this), label_date(this),
    calendar1(this), calendar2(this), print_thread(0)
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
    SetButtons(true);
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
    width_line << 200;//table.width();
    table_init.width_line = width_line;
    table_defectoskopist.SetInitStruct(table_init);
    table_defectoskopist.setGeometry(QRect(750, 200, 250, 250));
    QObject::connect(&table_defectoskopist, SIGNAL(ClickLine(unsigned)), this, SLOT(OnClickLineTablet(unsigned)));
    table_defectoskopist.setVisible(false);


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



    QFont font = this->font();
    font.setPixelSize(15);
    QPalette palette = calendar1.palette();
    palette.setColor(QPalette::Base, QColor(0, 30, 185, 100));
    palette.setColor(QPalette::Text, QColor(255, 255, 255, 255));
    palette.setColor(QPalette::AlternateBase, QColor(0, 0, 200, 155));
    calendar1.setPalette(palette);
    calendar1.setFont(font);
    //calendar1.setSelectedDate(date);
    calendar1.setGeometry(QRect(50, 200, 250, 250));
    calendar1.setFirstDayOfWeek(Qt::Monday);
    calendar1.setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    calendar2.setPalette(palette);
    calendar2.setFont(font);
    //calendar1.setSelectedDate(date);
    calendar2.setGeometry(QRect(400, 200, 250, 250));
    calendar2.setFirstDayOfWeek(Qt::Monday);
    calendar2.setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    QObject::connect(&calendar1, SIGNAL(selectionChanged()), this, SLOT(CalendarChanged()));
    QObject::connect(&calendar2, SIGNAL(selectionChanged()), this, SLOT(CalendarChanged()));
    label_date.setText("1");
    CalendarChanged();
}
CBdPrintPeriod::~CBdPrintPeriod()
{
    if(print_thread)
    {
        print_thread->terminate();
        print_thread->wait(3000);
        delete print_thread;
        print_thread = 0;
    }
}
void CBdPrintPeriod::OnPrintThreadState(unsigned n)
{
    if(!n)
    {
        print_thread->wait(3000);
        delete print_thread;
        print_thread = 0;
        SetButtons(true);
    }
}
void CBdPrintPeriod::SetButtons(const bool all)
{
    buttons.SubButton();
    buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("<< Назад")));
    if(all)
    {
        buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("Настройка принтера")));
        buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("Печать")));
        buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("Создать pdf")));
    }
    buttons.SetFocusAll(true);
    buttons.Paint();
}
void CBdPrintPeriod::Run()
{
    table_defectoskopist.Clear();
    QList<QString> l = param.GetListDefectoskopist();
    QList<QString> line;
    line << QString::fromLocal8Bit("Все");
    table_defectoskopist.AddLine(line);
    for(unsigned i = 0; i < l.size(); i++)
    {
        QList<QString> line;
        line << l[i];
        table_defectoskopist.AddLine(line);
    }
    table_defectoskopist.SetChecked(param.GetSelectDefectoskopist(2));
    table_defectoskopist.Paint();
}
void CBdPrintPeriod::CalendarChanged()
{
    date1 = calendar1.selectedDate();
    date2 = calendar2.selectedDate();
    label_date.setText(QString::fromLocal8Bit("Отчёт за период: ") + date1.toString("dd.MM.yyyy") + QString::fromLocal8Bit(" г. - ") +
                       date2.toString("dd.MM.yyyy") + QString::fromLocal8Bit(" г."));
    SetButtons(date1 <= date2);
}
void CBdPrintPeriod::OnClickLineTablet(unsigned n)
{
    param.SetSelectDefectoskopist(2, n);
}
void CBdPrintPeriod::OnButtonsClick(unsigned n, bool b)
{
    if(buttons.GetSize() == 2 && n == 1)
        n = 4;
    switch(n)
    {
        case 0: emit OnPressButton(n); break;
        case 1: PrintDiallog(); break;
        case 2: PrintWheels(); break;
        case 3: PrintPdfWheels(); break;
    }
}
void CBdPrintPeriod::PrintDiallog()
{
    QPrintDialog print_diallog(&printer, this);
    print_diallog.setMinMax(1, 1);
    printer.setOrientation(QPrinter::Landscape);
    printer.setPageSize(QPrinter::A4);
    print_diallog.exec();
}
void CBdPrintPeriod::PrintWheels()
{
    printer.setOrientation(QPrinter::Portrait);
    printer.setPageSize(QPrinter::A4);
    printer.setDocName("SDVK " + date1.toString("yyyy.MM.dd") + "-" + date2.toString("yyyy.MM.dd"));
    Print(&printer);
}
void CBdPrintPeriod::PrintPdfWheels()
{
    printer_pdf.setOrientation(QPrinter::Portrait);
    printer_pdf.setPageSize(QPrinter::A4);
    printer_pdf.setOutputFormat(QPrinter::PdfFormat);
    printer_pdf.setOutputFileName("SDVK " + date1.toString("yyyy.MM.dd") + "-" + date2.toString("yyyy.MM.dd") + ".pdf");
    printer_pdf.setDocName("SDVK " + date1.toString("yyyy.MM.dd") + "-" + date2.toString("yyyy.MM.dd"));
    Print(&printer_pdf, true);
}
void CBdPrintPeriod::Print(QPrinter *printer, const bool pdf)
{
    SetButtons(false);
    print_thread = new CPrintThread(printer, pdf, table_defectoskopist.GetPoleText(table_defectoskopist.GetNumberActivLine(), 0),
                                    calendar1.selectedDate(), calendar2.selectedDate(), this);
    QObject::connect(print_thread, SIGNAL(NewState(unsigned)), this, SLOT(OnPrintThreadState(unsigned)));
    print_thread->start(QThread::NormalPriority);
}
void CBdPrintPeriod::SetImageBack(const QImage &ib, const QRect &r)
{
    image_back = QImage(width(), height(), QImage::Format_RGB32);
    QPainter painter(&image_back);
    painter.drawImage(rect(), ib, r);
    QFont font;
    font.setBold(true);
    painter.setPen(Qt::white);
    font.setPointSize(16);
    painter.setFont(font);
    painter.drawText(QPoint((50*2+250)/2-10, 170), QString::fromLocal8Bit("С"));
    painter.drawText(QPoint((400*2+250)/2-10, 170), QString::fromLocal8Bit("По"));
   // painter.drawText(QPoint(750, 170), QString::fromLocal8Bit("Дефектоскопист"));
    painter.end();
    buttons.setGeometry(QRect(10, 65, width() - 20, 50));
    buttons.SetImageBack(image_back, buttons.geometry());
    table_defectoskopist.SetImageBack(image_back, table_defectoskopist.geometry());
}
void CBdPrintPeriod::resizeEvent(QResizeEvent *r)
{
    emit IAmReSize();
    label_date.setGeometry(QRect(200, 15, width() - 400, 40));
}
void CBdPrintPeriod::paintEvent(QPaintEvent *p)
{
    //if(!QWidget::isVisible())
     //   return;
    QPainter painter;
    painter.begin(this);
    painter.drawImage(p->rect(), image_back, p->rect());
    painter.end();
}
