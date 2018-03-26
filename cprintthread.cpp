#include "cprintthread.h"

CPrintThread::CPrintThread(QPrinter *p, const bool pd, const QString n, const QDate d1, const QDate d2, QObject *parent):
    QThread(parent), printer(p), pdf(pd), date1(d1), date2(d2), name(n), file_path(QDir::current().absolutePath())
{
}
CPrintThread::~CPrintThread()
{
}
void CPrintThread::run()
{
    unsigned kol_whell[4] = {0, 0, 0, 0};

    for(QDate date = date1; date <= date2;)
    {
        if(SetDir(date))
        {
            QStringList list(QString("*.kp"));
            QStringList sr = dir.entryList(list, QDir::Files);
            for(int i = 0; i < sr.size(); i ++)
            {
                QString file_name = tek_file_path + "/" + sr[i];
                try
                {
                    CWheel wheel(file_name);
                    kol_whell[0] ++;
                    if(wheel.GetDefect())
                        kol_whell[1] ++;
                    else if(wheel.IsDefecAll())
                        kol_whell[2] ++;
                    else
                        kol_whell[3] ++;
                }
                catch(CWheel *cs){}
            }
        }
        date = date.addDays(1);
    }

    QPainter painter(printer);
    QRect rect(painter.viewport());

    const double bw = rect.width();// GetDeviceCaps(prn->Handle, HORZRES);
    const double bh = rect.height();// GetDeviceCaps(prn->Handle, VERTRES);
    const double width = 210;//GetDeviceCaps(prn->Handle, HORZSIZE);
    const double height = 290;//GetDeviceCaps(prn->Handle, VERTSIZE);
    const double mmw = bw / width;
    const double mmh = bh / height;
    const double mmpole = width / 210;
    QFont font(painter.font());

    painter.setBrush(Qt::white);
    QPen pen(Qt::black);
    if(pdf)
        pen.setWidth(1);
    painter.setPen(pen);

    font.setPointSize(14); painter.setFont(font);
    painter.drawText(mmpole*90*mmw, 7*mmh, QString::fromLocal8Bit("РЕЗУЛЬТАТ"));
    painter.drawText(mmpole*35*mmw, 15*mmh, QString::fromLocal8Bit("ультразвукового контроля колёсных пар на стенде СДВК"));
    QString str_data;
    if(date1 == date2)
        str_data = QString::fromLocal8Bit("за ") + date1.toString("dd.MM.yyyy") + QString::fromLocal8Bit(" г.");
    else
        str_data = QString::fromLocal8Bit("с ") + date1.toString("dd.MM.yyyy") +
                   QString::fromLocal8Bit(" г. по ") + date2.toString("dd.MM.yyyy") + QString::fromLocal8Bit(" г.");
    painter.drawText(mmpole*70*mmw, 23*mmh, str_data);

    painter.drawText(mmpole*12*mmw, 36*mmh, QString::fromLocal8Bit("Проконтролировано"));
    painter.drawText(mmpole*100*mmw, 36*mmh, QString::fromLocal8Bit("Признано годными"));
    painter.drawText(mmpole*189*mmw, 36*mmh, QString::fromLocal8Bit("Брак"));
    painter.drawText(mmpole*20*mmw, 42*mmh, QString::fromLocal8Bit("колёсных пар"));

    font.setPointSize(11); painter.setFont(font);
    painter.drawText(mmpole*67*mmw, 44*mmh, QString::fromLocal8Bit("присутствует превышение"));
    painter.drawText(mmpole*126*mmw, 44*mmh, QString::fromLocal8Bit("отсутствует превышение"));
    painter.drawText(mmpole*73*mmw, 50*mmh, QString::fromLocal8Bit("уровня браковочной"));
    painter.drawText(mmpole*132*mmw, 50*mmh, QString::fromLocal8Bit("уровня браковочной"));
    painter.drawText(mmpole*75*mmw, 56*mmh, QString::fromLocal8Bit("чувствительности"));
    painter.drawText(mmpole*134*mmw, 56*mmh, QString::fromLocal8Bit("чувствительности"));

    font.setPointSize(14); painter.setFont(font);
    painter.drawText(mmpole*35*mmw, 64*mmh, QString::number(kol_whell[0]));
    painter.drawText(mmpole*92*mmw, 64*mmh, QString::number(kol_whell[2]));
    painter.drawText(mmpole*149*mmw, 64*mmh, QString::number(kol_whell[3]));
    painter.drawText(mmpole*192*mmw, 64*mmh, QString::number(kol_whell[1]));


    painter.drawLine((mmpole*10)*mmw, 30*mmh, (mmpole*210)*mmw, 30*mmh);
    painter.drawLine((mmpole*65)*mmw, 38*mmh, (mmpole*180)*mmw, 38*mmh);
    painter.drawLine((mmpole*10)*mmw, 58*mmh, (mmpole*210)*mmw, 58*mmh);
    painter.drawLine((mmpole*10)*mmw, 66*mmh, (mmpole*210)*mmw, 66*mmh);

    painter.drawLine((mmpole*10)*mmw, 30*mmh, (mmpole*10)*mmw, 66*mmh);
    painter.drawLine((mmpole*65)*mmw, 30*mmh, (mmpole*65)*mmw, 66*mmh);
    painter.drawLine((mmpole*124)*mmw, 38*mmh, (mmpole*124)*mmw, 66*mmh);
    painter.drawLine((mmpole*180)*mmw, 30*mmh, (mmpole*180)*mmw, 66*mmh);
    painter.drawLine((mmpole*210)*mmw, 30*mmh, (mmpole*210)*mmw, 66*mmh);
    painter.end();
  //  msleep(500);
    emit NewState(0);
}
bool CPrintThread::SetDir(const QDate &_date)
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
