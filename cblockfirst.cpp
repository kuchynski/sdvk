#include "cblockfirst.h"

CBlockFirst::CBlockFirst(QWidget *parent) : QWidget(parent), com_port(0), check_port(this),
    now_exit(false), dir_path(QDir::current().absolutePath()), label_com_state(this),
    button_run(this), timer_new_second(0), //button_set_motor_end(this),
    spin_box_diametr(this), table_defectoskopist(this), line_edit_number(this)
{
    QPalette palette7;
    QBrush brush7(QColor(245, 245, 255, 255));
    brush7.setStyle(Qt::SolidPattern);
    palette7.setBrush(QPalette::Active, QPalette::WindowText, brush7);
    palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
    palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush7);
    QFont font4;
    font4.setPointSize(30);
    label_com_state.setGeometry(QRect(50, 50, 300, 51));
    label_com_state.setFont(font4);
    label_com_state.setPalette(palette7);
    //QBrush brush1(QColor(245, 245, 100, 255));
   // brush1.setStyle(Qt::SolidPattern);
  //  palette7.setBrush(QPalette::Active, QPalette::WindowText, brush1);
//    font4.setPointSize(60);

    CChecks::SButtonsInit chek_init;
    chek_init.direction = CChecks::SButtonsInit::edHorizontal;
    chek_init.font = this->font();
    chek_init.font.setPixelSize(25);
    chek_init.color_backgraund = QColor(25, 80, 100, 255);//0, 30, 185, 255);
    chek_init.color_backgraund_checked = QColor(100, 100, 255, 255);
    chek_init.color_text = Qt::white;
    chek_init.sglaz_const = 20;
    on_checked_portChanged(param.GetComNumber(), true);
    check_port.SetInitStruct(chek_init);
    check_port.AddButton(CChecks::SButton(QString::fromLocal8Bit("выкл")));
    check_port.AddButton(CChecks::SButton(QString::fromLocal8Bit("COM1")));
    check_port.AddButton(CChecks::SButton(QString::fromLocal8Bit("COM2")));
    check_port.AddButton(CChecks::SButton(QString::fromLocal8Bit("COM3")));
    check_port.AddButton(CChecks::SButton(QString::fromLocal8Bit("COM4")));
    check_port.AddButton(CChecks::SButton(QString::fromLocal8Bit("COM5")));
    check_port.AddButton(CChecks::SButton(QString::fromLocal8Bit("COM6")));
    check_port.AddButton(CChecks::SButton(QString::fromLocal8Bit("COM7")));
    check_port.AddButton(CChecks::SButton(QString::fromLocal8Bit("COM8")));
    check_port.AddButton(CChecks::SButton(QString::fromLocal8Bit("COM9")));
    check_port.SetFocusAll(true);
    check_port.SetChecked(param.GetComNumber());
    QObject::connect(&check_port, SIGNAL(PressButton(unsigned,bool)), this, SLOT(on_checked_portChanged(unsigned,bool)));
    QObject::connect(&com_port, SIGNAL(NewBlockState(unsigned, unsigned, unsigned)), parent, SLOT(OnBlockState(unsigned, unsigned, unsigned)));
    QObject::connect(&com_port, SIGNAL(NewState(unsigned)), this, SLOT(OnNewComPortState(unsigned)));
    com_port.SetNumberPort(param.GetComNumber());
    com_port.start(QThread::NormalPriority);

    button_run.SetInitStruct(chek_init);
    button_run.AddButton(CChecks::SButton(QString::fromLocal8Bit("Поднять блок")));
    button_run.AddButton(CChecks::SButton(QString::fromLocal8Bit("Опустить блок")));
    button_run.AddButton(CChecks::SButton(QString::fromLocal8Bit("Сканирование >>")));
    button_run.SetFocusAll(true);
    QObject::connect(&button_run, SIGNAL(PressButton(unsigned,bool)), this, SLOT(OnPressButtonStart(unsigned,bool)));

    process_reload = new QProcess(this);
    QObject::connect(process_reload, SIGNAL(finished(int)), this, SLOT(OnEndReload(int)));

    chek_init.font = this->font();
    chek_init.font.setPixelSize(25);
    chek_init.color_backgraund = QColor(25, 80, 100, 255);//0, 30, 185, 255);
    chek_init.color_backgraund_checked = QColor(100, 100, 255, 255);
    chek_init.color_text = Qt::white;
    chek_init.sglaz_const = 20;

//_
    CSpinBox::SSpinBoxInit spin_init;
    spin_init.height_buttons = 20;
    spin_init.color_backgraund = QColor(50, 150, 200, 255);
    spin_init.color_backgraund_buttons = QColor(75, 110, 150, 255);
    spin_init.color_text = Qt::white;
    QFont fo;
    fo.setBold(true);
    fo.setPointSize(30);
    fo.setWeight(30);
    spin_init.font = fo;
    spin_init.height_buttons = 30;
    spin_box_diametr.SetInitStruct(spin_init);
    spin_box_diametr.setGeometry(400, 270, 100, 100);
    spin_box_diametr.SetMinMax(845, 965);

    QFont fontl;
    fontl.setPointSize(30);
    fontl.setBold(true);
    line_edit_number.setGeometry(50, 280, 250, 50);
    line_edit_number.setFont(fontl);


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
    table_defectoskopist.SetInitStruct(table_init);
    table_defectoskopist.setGeometry(650, 280, 200, 250);
    QObject::connect(&table_defectoskopist, SIGNAL(ClickLine(unsigned)), this, SLOT(OnClickLineTablet(unsigned)));

/*    chek_init.direction = CChecks::SButtonsInit::edVertical;
    button_set_motor_end.SetInitStruct(chek_init);
    button_set_motor_end.AddButton(CChecks::SButton(QString::fromLocal8Bit("Поднять преобразователи")));
    button_set_motor_end.AddButton(CChecks::SButton(QString::fromLocal8Bit("Опустить преобразователи")));
    button_set_motor_end.SetFocusAll(true);
    QObject::connect(&button_set_motor_end, SIGNAL(PressButton(unsigned,bool)), this, SLOT(OnPressButtonSetMotor(unsigned,bool)));
    button_set_motor_end.setGeometry(50, 450, 400, 150);*/

    Run();
}
CBlockFirst::~CBlockFirst()
{
    now_exit = true;
    com_port.SetNumberPort(100);
    com_port.wait();
}
void CBlockFirst::Run()
{
    spin_box_diametr.SetValue(param.GetLastDiametr(0));
    table_defectoskopist.Clear();
    //line_edit_number.setText(str);
    QList<QString> l = param.GetListDefectoskopist();
    for(unsigned i = 0; i < l.size(); i++)
    {
        QList<QString> line;
        line << l[i];
        table_defectoskopist.AddLine(line);
    }
    table_defectoskopist.SetChecked(param.GetSelectDefectoskopist(0));
    table_defectoskopist.Paint();
}
void CBlockFirst::setVisibleStart(const bool s)
{
  //  button_set_motor_end.setVisible(s);
    button_run.setVisible(s);
//    spin_box_diametr.setVisible(s);
  //  table_defectoskopist.setVisible(s);
    //line_edit_number.setVisible(s);
}
void CBlockFirst::OnNewComPortState(unsigned s)
{
    if(now_exit)
        return;
    bool state = false;
    switch(s)
    {
        case CComPort::cpsDisConnect:
            label_com_state.setText(QString::fromLocal8Bit("порт отключён"));
            if(timer_new_second)
                QObject::killTimer(timer_new_second);
            break;
        case CComPort::cpsConnect:
            label_com_state.setText(QString::fromLocal8Bit("подключение"));
            if(timer_new_second)
                QObject::killTimer(timer_new_second);
            timer_new_second = QObject::startTimer(1000);
            break;
        case CComPort::cpsConnect1:
            label_com_state.setText(QString::fromLocal8Bit("связь"));
            state = true;
            break;
        case CComPort::cpsConnect2:
            label_com_state.setText(QString::fromLocal8Bit("нет данных"));
            break;
        case CComPort::cpsReload:
            label_com_state.setText(QString::fromLocal8Bit("перезагрузка порта"));
            process_reload->start(dir_path + "/usb_reload.bat");
            break;
        case CComPort::cpsError:
            label_com_state.setText(QString::fromLocal8Bit("ошибка порта"));
            break;
        case CComPort::cpsNoState:
            label_com_state.setText(QString::fromLocal8Bit(""));
            break;
        default:
            label_com_state.setText(QString(""));
    }
    setVisibleStart(state);
}
void CBlockFirst::OnEndReload(int res)
{
    on_checked_portChanged(param.GetComNumber()+100, true);
}
void CBlockFirst::on_checked_portChanged(unsigned n, bool tmp)
{
    int n2 = (n > 100)? n - 100 : n;
    com_port.SetNumberPort(n);
    param.SetComNumber(n2);
}
void CBlockFirst::OnClickLineTablet(unsigned n)
{
    param.SetSelectDefectoskopist(0, n);
}
void CBlockFirst::OnPressButtonStart(unsigned n, bool v)
{
    if(n == 0)
    {
        const unsigned d = spin_box_diametr.GetValue();
        const unsigned t = (d - 800) / 2;
        com_port.Begin(2, t);
    }
    else if(n == 1)
    {
        com_port.Begin(3, 0);
    }
    else if(n == 2)
    {
        param.SetLastDiametr(0, spin_box_diametr.GetValue());
        const unsigned d = spin_box_diametr.GetValue();
        const unsigned t = (d - 800) / 2;
        const QString number = line_edit_number.text();
        const QString name = table_defectoskopist.GetPoleText(table_defectoskopist.GetNumberActivLine(), 0);
        CWheel wheel(number, t, d, name);
        emit PressButtonStart(wheel);
    }
}
/*void CBlockFirst::OnPressButtonSetMotor(unsigned n, bool v)
{
    if(n == 0)
    {
        const unsigned d = spin_box_diametr.GetValue();
        const unsigned t = (d - 800) / 2;
        com_port.Begin(2, t);
    }
    else if(n == 1)
    {
        com_port.Begin(3, 0);
    }
}*/
void CBlockFirst::paintEvent(QPaintEvent *p)
{
    if(!QWidget::isVisible())
        return;
    QPainter painter;
    painter.begin(this);
    painter.drawImage(rect(), image_back, rect());
    //painter.drawImage(p->rect(), image_back, p->rect());
    painter.end();
}
void CBlockFirst::SetImageBack(const QImage &ib, const QRect &r)
{
    image_back = QImage(width(), height(), QImage::Format_RGB32);
    QPainter painter(&image_back);
    painter.drawImage(rect(), ib, r);
    painter.setPen(QPen(Qt::white));
    painter.setBrush(Qt::NoBrush);
    QFont font;
    font.setPointSize(16);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QPoint(50, 250), QString::fromLocal8Bit("Номер колёсной пары"));
    painter.drawText(QPoint(400, 250), QString::fromLocal8Bit("Диаметр колеса"));
    painter.drawText(QPoint(650, 250), QString::fromLocal8Bit("Дефектоскопист"));
    painter.end();
    check_port.setGeometry(QRect(50, 120, width() - 100, 70));
    button_run.setGeometry(QRect(50, height() - 120, width() - 100, 70));
    check_port.SetImageBack(image_back, check_port.geometry());
    button_run.SetImageBack(image_back, button_run.geometry());
 //   button_set_motor_end.SetImageBack(image_back, button_set_motor_end.geometry());
    spin_box_diametr.SetImageBack(image_back, spin_box_diametr.geometry());
    table_defectoskopist.SetImageBack(image_back, table_defectoskopist.geometry());
}
void CBlockFirst::resizeEvent(QResizeEvent *r)
{
    emit IAmResize();
}
