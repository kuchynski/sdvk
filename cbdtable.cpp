#include "cbdtable.h"

CBdTable::CBdTable(QWidget *parent) : QWidget(parent), label_date(this),
    table(this), buttons_main(this), buttons(this), file_path(QDir::current().absolutePath()), image_defect(this)
{
    QBoxLayout *pbx = new QBoxLayout(QBoxLayout::TopToBottom);
    QBoxLayout *pbx1 = new QBoxLayout(QBoxLayout::TopToBottom);
    pbx1->setMargin(0);
    pbx1->setSpacing(0);
    setLayout(pbx);
    wid1 = new QWidget();
    wid1->setLayout(pbx1);


    CButtons::SButtonsInit but_init;
    but_init.direction = CButtons::SButtonsInit::edHorizontal;
    but_init.font = this->font();
    but_init.font.setPixelSize(25);
    but_init.color_backgraund = QColor(25, 80, 100, 255);//0, 30, 185, 255);
    but_init.color_backgraund_checked = QColor(100, 100, 255, 255);
    but_init.sglaz_const = 20;
    but_init.color_text = Qt::white;
    but_init.color_text_checked = Qt::white;
    buttons_main.SetInitStruct(but_init);
    buttons_main.setMaximumSize(100, 50);
    buttons_main.AddButton(CButtons::SButton(QString::fromLocal8Bit("Дата")));
    buttons_main.SetFocusAll(true);
    QObject::connect(&buttons_main, SIGNAL(PressButton(unsigned, bool)), this, SLOT(OnButtonsMainClick(unsigned, bool)));
    pbx->addWidget(&buttons_main);
    but_init.font.setPixelSize(15);
    buttons.SetInitStruct(but_init);
    buttons.setMaximumHeight(50);
    buttons.SetFocusAll(true);
    QObject::connect(&buttons, SIGNAL(PressButton(unsigned, bool)), this, SLOT(OnButtonsClick(unsigned, bool)));
    pbx->addWidget(&buttons);
    pbx->addWidget(wid1);


    CTable::STableInit table_init;
    table_init.color_backgraund = QColor(50, 150, 200, 255);
//    table_init.color_backgraund_checked = QColor(150, 155, 255, 255);
    table_init.color_backgraund_checked = QColor(200, 200, 200, 255);
    table_init.color_backgraund_title = QColor(50, 100, 200, 255);
    table_init.color_backgraund_button = QColor(25, 80, 100, 255);
    table_init.color_line = QColor(200, 200, 255, 255);
    table_init.color_line_checked = QColor(200, 200, 255, 255);
    table_init.color_text_checked = QColor(30, 30, 150, 255);
    table_init.color_text_title = QColor(255, 255, 255, 255);
    table_init.color_text = QColor(250, 250, 250, 255);
//    table_init.color_backgraund_button = QColor(50, 100, 255, 255);
    table_init.font = this->font();
    table_init.font.setPixelSize(18);
    table_init.hieght_line = 39;
    QList<unsigned> width_line;
    width_line << 65 << 120 << 110 << 70 << 90 << 150 << 1000;//table.width();
    table_init.width_line = width_line;
    table.SetInitStruct(table_init);
    QList<QString> t;
    t << QString::fromLocal8Bit("Время") << QString::fromLocal8Bit("Номер") << QString::fromLocal8Bit("Состояние")
      << QString::fromLocal8Bit("Обод") << QString::fromLocal8Bit("Диаметр") << QString::fromLocal8Bit("Дефектоскопист")
      << QString::fromLocal8Bit("Примечание");
    table.SetTitle(t);
    QObject::connect(&table, SIGNAL(ClickLine(unsigned)), this, SLOT(OnTableClick(unsigned)));
    QObject::connect(&table, SIGNAL(ClickDoubleLine(unsigned)), this, SLOT(OnTableClickDouble(unsigned)));
    QObject::connect(&table, SIGNAL(IAmReSize()), this, SLOT(OnReSizeTable()));
    QObject::connect(&image_defect, SIGNAL(IAmReSize()), this, SLOT(OnReSizeImageDefect()));
    table.setMinimumWidth(770);
    pbx1->addWidget(&table);
    pbx1->addWidget(&image_defect);
    image_defect.setMinimumSize(790, 265);
    image_defect.setMaximumSize(790, 265);

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
   // label_date.setGeometry(QRect(200, 10, width() - 400, 30));
    label_date.setAlignment(Qt::AlignHCenter);
    label_date.setFont(fontl);
    label_date.setPalette(palette7);
    label_date.setText(QString::fromLocal8Bit(""));

    date = QDate::currentDate();
    SetDate();

   // buttons_main.setVisible(false);
   // buttons.setVisible(false);
   // label_date.setVisible(false);

}
void CBdTable::OnNewWheel(const CWheel &w)
{
    QDir dir_s;
    CDateTime date_time = w.GetDateTime();
    int year = date_time.GetYear();
    int mon = date_time.GetMon();
    int day = date_time.GetDay();
    if(!dir_s.cd(file_path))
        return;
    QString dir_name1(QString("%1_%2").arg(year, 4, 10, QLatin1Char('0')).arg(mon, 2, 10, QLatin1Char('0')));
    QString dir_name2(QString("%1").arg(day, 2, 10, QLatin1Char('0')));
    if(!dir_s.cd(dir_name1))
    {
        if(!dir_s.mkdir(dir_name1))
            return;
        if(!dir_s.cd(dir_name1))
            return;
    }
    if(!dir_s.cd(dir_name2))
    {
        if(!dir_s.mkdir(dir_name2))
            return;
        if(!dir_s.cd(dir_name2))
            return;
    }
    QString file_name = dir_s.absolutePath() + "/" + date_time.GetTime2();
    CWheel new_wheel(w);
    bool ret_save = new_wheel.SaveToFile(file_name + ".kp");

    if(ret_save && date == new_wheel.GetQDate())
    {
        try
        {
            CWheel wheel(file_name + ".kp");
            wheels.Push(wheel);
            QList<QString> l;
            wheels[wheels.GetSize()-1].PaintOnGrid(l);
            table.AddLine(l);
            table.SetChecked(table.GetSize()-1);
            if(wheels.GetSize() == 1)
                OnTableClick(0);
        }
        catch(CWheel *cs){}
    }
    return;
}
void CBdTable::CloseSostav(const bool del)
{
    QString file_name = wheels[table.GetNumberActivLine()].GetFileName();
    wheels.Erase(table.GetNumberActivLine());
    table.SubLine(table.GetNumberActivLine());
    OnTableClick(table.GetNumberActivLine());
    table.SetChecked(table.GetNumberActivLine());
    if(del)
        QFile::remove(file_name);
}
void CBdTable::ShowEditPS()
{
    CEditPsDialog *td = new CEditPsDialog(wheels[table.GetNumberActivLine()].GetPS(), wheels[table.GetNumberActivLine()].GetDefect(),
                                          param.GetSizeX(), param.GetSizeY(), this);
    if(td->exec() == QDialog::Accepted)
    {
        wheels[table.GetNumberActivLine()].SetPS(td->GetStr());
        wheels[table.GetNumberActivLine()].SetDefect(td->GetCheck());
        wheels[table.GetNumberActivLine()].SaveToFile();
        QList<QString> l;
        wheels[table.GetNumberActivLine()].PaintOnGrid(l);
        table.SetLine(l, table.GetNumberActivLine(), true);
    }
    delete td;
    repaint();
}
void CBdTable::SetButtons()
{
    buttons.SubButton();
    if(wheels.GetSize())
    {
        buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("Скрыть")));
        buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("Удалить")));
        buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("Редактировать")));
    }
    buttons.AddButton(CButtons::SButton(QString::fromLocal8Bit("Отчёт >>")));
    buttons.SetFocusAll(true);
    buttons.Paint();
}
void CBdTable::OnButtonsClick(unsigned n, bool b)
{
    if(buttons.GetSize() == 1)
        n = 3;
    switch(n)
    {
        case 0: CloseSostav(); break;
        case 1: CloseSostav(true); break;
        case 2: ShowEditPS(); break;
        case 3: emit OnPressButton(date, wheels); break;
    }
}
void CBdTable::OnButtonsMainClick(unsigned, bool)
{
    CInputDataDialog *td = new CInputDataDialog(date, param.GetSizeX(), param.GetSizeY(), this);
   // repaint();
    if(td->exec() == QDialog::Accepted)
    {
        date = td->GetDate();
        SetDate();
    }
    delete td;
    repaint();
}
bool CBdTable::SetDir(const QDate &_date)
{
    int year = _date.year();
    int mon = _date.month();
    int day = _date.day();
    if(!dir.cd(file_path))
          return false;
    QString dir_name1(QString("%1_%2").arg(year, 4, 10, QLatin1Char('0')).arg(mon, 2, 10, QLatin1Char('0')));
    QString dir_name2(QString("%1").arg(day, 2, 10, QLatin1Char('0')));
    if(!dir.cd(dir_name1))
      return false;
    if(!dir.cd(dir_name2))
      return false;
    tek_file_path = dir.absolutePath();
    return true;
}
void CBdTable::SetDate()
{
    wheels.Clear();
    if(SetDir(date))
    {
        QStringList list(QString("*.kp"));
        QStringList sr = dir.entryList(list, QDir::Files);
        for(int i = 0; i < sr.size(); i ++)
        {
            QString file_name = tek_file_path + "/" + sr[i];
            try
            {
                CWheel s(file_name);
                // if(s.GetQDate() == date)
                wheels.Push(s);
            }
            catch(CWheel *cs){}
        }
    }
   // if(wheels.GetSize())
    label_date.setText(QString::fromLocal8Bit("Список колёсных пар за ") + date.toString("dd.MM.yyyy") + QString::fromLocal8Bit(" г."));
  //  else
     //   label_date.setText(date.toString("dd.MM.yyyy") + QString::fromLocal8Bit(" Рі."));
    PaintTable();
    SetButtons();
    resize(size());
}
void CBdTable::PaintTable()
{
    table.Clear();
    for(unsigned i = 0; i < wheels.GetSize(); i ++)
    {
        QList<QString> l;
        wheels[i].PaintOnGrid(l);
        table.AddLine(l);
    }
  //  table.SetChecked(0);
    OnTableClick(0);
    table.Paint();
}
void CBdTable::OnTableClick(unsigned line)
{
    if(!wheels.GetSize())
    {
        //Clear();
        image_defect.setVisible(false);
        return;
    }
    image_defect.setVisible(true);
    image_defect.SetMapOfDatchik(wheels[table.GetNumberActivLine()].GetMapLeft(), wheels[table.GetNumberActivLine()].GetMapRight());
}
void CBdTable::OnTableClickDouble(unsigned line)
{
    ShowEditPS();
}
void CBdTable::paintEvent(QPaintEvent *p)
{
    return;
//    if(!QWidget::isVisible())
  //      return;
    QPainter painter;
    painter.begin(this);
    painter.drawImage(rect(), image_back, rect());
    painter.drawImage(p->rect(), image_back, p->rect());
    painter.end();
}
void CBdTable::OnReSizeTable()
{
    QRect re(table.geometry());
    re.setY(table.y() + wid1->y());
    re.setX(table.x() + wid1->x());
    table.SetImageBack(image_back, re);
}
void CBdTable::OnReSizeImageDefect()
{
    QRect re(table.geometry());
    re.setY(image_defect.y() + wid1->y());
    re.setX(image_defect.x() + wid1->x());
    image_defect.SetImageBack(image_back, re);
}
void CBdTable::SetImageBack(const QImage &ib, const QRect &r)
{
    image_back = QImage(width(), height(), QImage::Format_RGB32);
    QPainter painter(&image_back);
    painter.drawImage(rect(), ib, r);
    painter.end();
}
void CBdTable::resizeEvent(QResizeEvent *r)
{
    emit IAmReSize();
    label_date.setGeometry(QRect(200, 15, width() - 400, 40));
//    CBaseWindow::resizeEvent(r);
}
