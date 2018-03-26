#include "coptionswindow.h"

COptionsWindow::COptionsWindow(QWidget *parent) : CBaseWindow(QString::fromLocal8Bit("применить"), QString::fromLocal8Bit("отменить"), parent),
    label_change(this), spinbox_rast1(this), spinbox_rast2(this), spinbox_rast0(this),
    spisok_defectoskopist(QString::fromLocal8Bit("Список дефектоскопистов"), "", this),
    spisok_ps(QString::fromLocal8Bit("Список примечаний"), "", this), enabled_datchik(this),
    check_mouse(this)
{
    CLabelChange::SLabelInit struct_label;
    struct_label.color_text = QColor(255, 255, 255, 255);
    QFont font2;
    font2.setPointSize(12);
    font2.setBold(true);
    font2.setWeight(75);
    struct_label.font = font2;
    label_change.SetInitStruct(struct_label);
    label_change.AddString(QString::fromLocal8Bit("СДВК версия 2.0"));
    label_change.AddString(QString::fromLocal8Bit("Полоцкое вагонное депо"));
    label_change.AddString("kuchynski@tut.by");
    label_change.AddString("+375 447302607");
    label_change.setGeometry(QRect(0, height() - 40, width(), 20));
    label_change.Start();


    CSpinBox::SSpinBoxInit spin_init;
    spin_init.height_buttons = 20;
    spin_init.color_backgraund = QColor(50, 150, 200, 255);
    spin_init.color_backgraund_buttons = QColor(75, 110, 150, 255);
    QFont fo;
    fo.setBold(true);
    fo.setPointSize(30);
    fo.setWeight(30);
    spin_init.font = fo;
    spin_init.height_buttons = 30;
    spinbox_rast0.setGeometry(QRect(20, 80, 100, 100));
    spinbox_rast0.SetInitStruct(spin_init);
    spinbox_rast0.SetMinMax(150, 600);
    spinbox_rast1.setGeometry(QRect(140, 80, 100, 100));
    spinbox_rast1.SetInitStruct(spin_init);
    spinbox_rast1.SetMinMax(50, 83);
    spinbox_rast2.setGeometry(QRect(310, 80, 100, 100));
    spinbox_rast2.SetInitStruct(spin_init);
    spinbox_rast2.SetMinMax(0, 9);
//    QObject::connect(&spinbox_rast2, SIGNAL(NewValue(int)), this, SLOT(OnChangedRast2(int)));

    QPalette palette7;
    QBrush brush7(QColor(255, 255, 255, 255));
    brush7.setStyle(Qt::SolidPattern);
    palette7.setBrush(QPalette::Active, QPalette::WindowText, brush7);
    palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
    palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush7);
    QFont fontl;
    fontl.setPointSize(16);
    fontl.setBold(true);
    fontl.setWeight(75);
    QLabel *label_r0 =  new QLabel(this);
    label_r0->setGeometry(QRect(20, 20, 130, 50));
    label_r0->setFont(fontl);
    label_r0->setPalette(palette7);
    label_r0->setText(QString::fromLocal8Bit("Отсчётов\nна круг"));
    QLabel *label_r1 =  new QLabel(this);
    label_r1->setGeometry(QRect(140, 20, 170, 50));
    label_r1->setFont(fontl);
    label_r1->setPalette(palette7);
    label_r1->setText(QString::fromLocal8Bit("Поз. конечная\nвертикальная"));
    QLabel *label_r2 =  new QLabel(this);
    label_r2->setGeometry(QRect(310, 20, 130, 50));
    label_r2->setFont(fontl);
    label_r2->setPalette(palette7);
    label_r2->setText(QString::fromLocal8Bit("Мёртвая\nзона"));

    ReadDataFromParam();

    spisok_defectoskopist.setGeometry(440, 140, 560, 210);
    spisok_ps.setGeometry(440, 370, 560, 320);
    enabled_datchik.setGeometry(20, 200, 390, 490);
    QObject::connect(&spisok_defectoskopist, SIGNAL(IAmResize()), this, SLOT(OnReSizeSpisokD()));
    QObject::connect(&spisok_ps, SIGNAL(IAmResize()), this, SLOT(OnReSizeSpisokPs()));


    CChecks::SButtonsInit chek_init;
    chek_init.style_background = CChecks::SButtonsInit::ebPicture;
    chek_init.direction = CChecks::SButtonsInit::edVertical;
    chek_init.color_backgraund = QColor(255, 255, 255, 0);
    QImage imagea1("OK1.png");
    QImage imagea2("OK2.png");
    check_mouse.AddButton(QString(""), imagea1, imagea2);
    check_mouse.SetChecked(0, (param.GetMouseEnabled()));
    check_mouse.SetInitStruct(chek_init);
    check_mouse.setGeometry(440, 60, 50, 50);
    QObject::connect(&check_mouse, SIGNAL(PressButton(unsigned, bool)), this, SLOT(OnCheckMouseClick(unsigned,bool)));
}
void COptionsWindow::ReadDataFromParam()
{
    spinbox_rast0.SetValue(param.GetRast(0));
    spinbox_rast1.SetValue(param.GetRast(1));
    spinbox_rast2.SetValue(param.GetRast(2));
    spisok_defectoskopist.SetList(param.GetListDefectoskopist());
    spisok_ps.SetList(param.GetListPs());
    for(unsigned i = 0; i < 9; i++)
        for(unsigned j = 0; j < 2; j++)
            enabled_datchik.SetData(i, j, param.GetEnabledDat(i, j));
}
void COptionsWindow::OnButtonsBaseClick(unsigned n, bool s)
{
    if(n == 0)
    {
        param.SetRast(0, spinbox_rast0.GetValue());
        param.SetRast(1, spinbox_rast1.GetValue());
        param.SetRast(2, spinbox_rast2.GetValue());
        param.SetListDefectoskopist(spisok_defectoskopist.GetList());
        param.SetListPs(spisok_ps.GetList());
        for(unsigned i = 0; i < 9; i++)
            for(unsigned j = 0; j < 2; j++)
                param.SetEnabledDat(i, j, enabled_datchik.GetData(i, j));
        param.SetSettings();
    }
    CBaseWindow::OnButtonsBaseClick(n, s);
}
void COptionsWindow::SetMouseEnabled(const bool s)
{
    check_mouse.SetChecked(0, s);
    check_mouse.Paint();
    param.SetMouseEnabled(s);
}
void COptionsWindow::OnCheckMouseClick(unsigned n, bool s)
{
    param.SetMouseEnabled(s);
}
void COptionsWindow::paintEvent(QPaintEvent *p)
{
    if(!QWidget::isVisible())
        return;
    QPainter painter;
    painter.begin(this);
    painter.drawImage(p->rect(), image_my, p->rect());
    painter.end();
    CBaseWindow::paintEvent(p);
}
void COptionsWindow::OnReSizeSpisokD()
{
    spisok_defectoskopist.SetImageBack(image_my, spisok_defectoskopist.geometry());
}
void COptionsWindow::OnReSizeSpisokPs()
{
    spisok_ps.SetImageBack(image_my, spisok_ps.geometry());
}
void COptionsWindow::OnReSizeEnabledD()
{
    enabled_datchik.SetImageBack(image_my, enabled_datchik.geometry());
}
void COptionsWindow::resizeEvent(QResizeEvent *r)
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
    font.setPointSize(16);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(QPoint(440, 40), QString::fromLocal8Bit("курсор мыши"));
    painter.end();

    label_change.setGeometry(QRect(0, height() - 40, width(), 20));
    label_change.SetImageBack(image_my, label_change.geometry());
    spinbox_rast0.SetImageBack(image_my, spinbox_rast0.geometry());
    spinbox_rast1.SetImageBack(image_my, spinbox_rast1.geometry());
    spinbox_rast2.SetImageBack(image_my, spinbox_rast2.geometry());
    check_mouse.SetImageBack(image_my, check_mouse.geometry());
    OnReSizeSpisokD();
    OnReSizeSpisokPs();
    OnReSizeEnabledD();
}
