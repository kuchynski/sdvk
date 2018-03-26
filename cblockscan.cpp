#include "cblockscan.h"

CBlockScan::CBlockScan(QWidget *parent) :  QWidget(parent), button_run(this), label_block(this),
    label_block_data1(this), label_block_data2(this), edit_ps("", 0, this), image_defect(this)
{
    QPalette palette7;
    QBrush brush7(QColor(245, 245, 255, 255));
    brush7.setStyle(Qt::SolidPattern);
    palette7.setBrush(QPalette::Active, QPalette::WindowText, brush7);
    palette7.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
    palette7.setBrush(QPalette::Disabled, QPalette::WindowText, brush7);
    QFont font4;
    font4.setPointSize(30);
    label_block.setGeometry(QRect(50, 50, 250, 400));
    label_block.setFont(font4);
    label_block.setPalette(palette7);
    label_block.setText(QString::fromLocal8Bit("оборот\n\nсторона\n\nнастройка\n\nкоордината"));
    label_block_data1.setGeometry(QRect(300, 50, 270, 300));
    label_block_data2.setGeometry(QRect(300, 350, 270, 100));
    QBrush brush1(QColor(245, 245, 100, 255));
    brush1.setStyle(Qt::SolidPattern);
    palette7.setBrush(QPalette::Active, QPalette::WindowText, brush1);
    font4.setPointSize(60);
    label_block_data1.setFont(font4);
    label_block_data1.setPalette(palette7);
    label_block_data2.setFont(font4);
    label_block_data2.setPalette(palette7);

    CChecks::SButtonsInit chek_init;
    chek_init.direction = CChecks::SButtonsInit::edHorizontal;
    chek_init.font = this->font();
    chek_init.font.setPixelSize(25);
    chek_init.color_backgraund = QColor(25, 80, 100, 255);//0, 30, 185, 255);
    chek_init.color_backgraund_checked = QColor(100, 100, 255, 255);
    chek_init.color_text = Qt::white;
    chek_init.sglaz_const = 20;
    button_run.SetInitStruct(chek_init);
    button_run.AddButton(CChecks::SButton(QString::fromLocal8Bit("<< отмена")));
//    button_run.AddButton(CChecks::SButton(QString::fromLocal8Bit("РЎРѕС…СЂР°РЅРёС‚СЊ")));
    button_run.SetFocusAll(true);
    QObject::connect(&button_run, SIGNAL(PressButton(unsigned,bool)), this, SLOT(OnPressButton(unsigned,bool)));
   // Run(Cwheel());

}
void CBlockScan::Run(const CWheel &w)
{
    label_block_data1.setText(QString::fromLocal8Bit(""));
    label_block_data2.setText(QString::fromLocal8Bit(""));
    wheel = w;
    map_of_datchik[0] = CMapOfDatchik();
    map_of_datchik[1] = CMapOfDatchik();
    button_run.SubButton(1);
    SetTypeVisiable(true);
}
void CBlockScan::SetTypeVisiable(const bool n)
{
    if(!n)
    {
        image_my = image_back;
        image_defect.SetMapOfDatchik(map_of_datchik[0], map_of_datchik[1]);
        repaint();
    }
    if(n)
        edit_ps.Clear();
    edit_ps.setVisible(!n);    
    image_defect.setVisible(!n);
    label_block.setVisible(n);
    label_block_data1.setVisible(n);
    label_block_data2.setVisible(n);
}
void CBlockScan::OnPressButton(unsigned n, bool v)
{
    if(n)
    {
        wheel.SetMapOfDatchik(map_of_datchik[0], map_of_datchik[1]);
        wheel.SetDefect(edit_ps.GetCheck());
        wheel.SetPS(edit_ps.GetStr());
        emit NewWheel(wheel);
    }
    emit PressButton(0);
}
void CBlockScan::OnBlockState(unsigned type, unsigned w, unsigned l)
{
    if(type == 0)
    {
        button_run.AddButton(QString::fromLocal8Bit("занести в базу"));
        button_run.SetFocusAll(true);
        button_run.Paint();
        SetTypeVisiable(false);
        return;
    }
    if(button_run.GetSize() > 1)
        return;

    unsigned side = (w & 0x00ff0000)? 1 : 0;
    int datchik = ((w & 0x0000ff00) >> 8);
    int round =   (w & 0x0000000f);
    bool state = ((l & 0xff000000) == 0x55000000)? true : false;
    int pix = l & 0x0000ffff;
    if(l & 0x00008000)
        pix = 0x0000ffff - pix + 1;
    int coordinate = (pix * 359) / param.GetRast(0);
    if(side > 1 || datchik > 8 || round > 1)
        return;

    if(type & 0x08)
    {
        if(state)
           map_of_datchik[side].SetPixels(datchik, round, pix, true);
        return;
    }
    if(type & 0x01)
    {
        QString str1 = QString::number(round+1) + "\n";
        str1 = str1 + ((side)? QString::fromLocal8Bit("правая\n") : QString::fromLocal8Bit("левая\n"));
        str1 = str1 + QString::number(datchik+1);
        label_block_data1.setText(str1);
    }
    if(type & 0x02)
    {
        label_block_data2.setText(QString::number(-pix));
        const unsigned image_height = 400;
        QRect rect_image_map(600, 50, image_height, image_height);
        map_of_datchik[side].PaintOnScreen(image_my, rect_image_map, datchik, coordinate, true);
        repaint(rect_image_map);
    }
}
void CBlockScan::paintEvent(QPaintEvent *p)
{
    if(!QWidget::isVisible())
        return;
    QPainter painter;
    painter.begin(this);
//    painter.drawImage(rect(), image_back, rect());
    painter.drawImage(p->rect(), image_my, p->rect());
    painter.end();
}
void CBlockScan::SetImageBack(const QImage &ib, const QRect &r)
{
    image_back = QImage(width(), height(), QImage::Format_RGB32);
    QPainter painter(&image_back);
    painter.drawImage(rect(), ib, r);
    painter.end();
    image_my = image_back;
    button_run.setGeometry(QRect(50, height() - 120, width() - 100, 70));
    button_run.SetImageBack(image_back, button_run.geometry());
    image_defect.setGeometry(QRect(50, button_run.y() - 315, width() - 100, 265));
    image_defect.SetImageBack(image_back, image_defect.geometry());
    edit_ps.setGeometry(QRect(50, 25, width() - 100, image_defect.y() - 50));
    edit_ps.SetImageBack(image_back, edit_ps.geometry());
}
void CBlockScan::resizeEvent(QResizeEvent *r)
{
    emit IAmResize();
}
