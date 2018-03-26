#include "cparam.h"

CParam param;

CParam::CParam(): settings("kuchynski", "sdvk")
{
    sizeXY[0] = 800;
    sizeXY[1] = 600;
    ReadSettings();
    count ++;
}
CParam::~CParam()
{
    SetSettings();
}
void CParam::SetSettings()
{
    for(unsigned i = 0; i < 10; i++)
        param_u[0+i] = rast[i];
    param_u[10] = enabled_dat[0];
    param_u[11] = enabled_dat[1];
    param_u[12] = com_number;
    param_u[13] = last_diametr[0];
    param_u[14] = last_diametr[1];
    param_u[15] = mouse_enabled;
    for(unsigned i = 0; i < 3; i++)
        param_u[16+i] = select_defectoskopist[i];

    settings.setValue("/count", count);
    for(unsigned i = 0; i < size_param; i ++)
    {
        settings.setValue("/uparam" + QString::number(i, 16), param_u[i]);
//        settings.setValue("/iparam" + QString::number(i, 16), param_i[i]);
    }


    QFile file(QDir::home().absolutePath() + "/sdvk_defectockopist.ini");
    if(file.open(QIODevice::Text | QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
       // list_defectoskopist << "qwe rt" << "123 45";
        for(unsigned i = 0; i < list_defectoskopist.size(); i ++)
            stream << list_defectoskopist[i] << endl;
    }
    file.close();
    QFile fileps(QDir::home().absolutePath() + "/sdvk_ps.ini");
    if(fileps.open(QIODevice::Text | QIODevice::WriteOnly))
    {
        QTextStream stream(&fileps);
//        list_ps << "qwe rt" << "123 45";
        for(unsigned i = 0; i < list_ps.size(); i ++)
            stream << list_ps[i] << endl;
    }
    fileps.close();
}
void CParam::ReadSettings()
{
    count = settings.value("/count", 0).toUInt();
    for(unsigned i = 0; i < size_param; i ++)
        param_u[i] = settings.value("/uparam" + QString::number(i, 16), 0).toUInt();
    for(unsigned i = 0; i < 10; i++)
        rast[i] = param_u[i];
    rast[3] = 40; //PosHorEnd
    enabled_dat[0] = param_u[10];
    enabled_dat[1] = param_u[11];
    com_number = param_u[12];
    last_diametr[0] = param_u[13];
    last_diametr[1] = param_u[14];
    mouse_enabled = param_u[15];
    for(unsigned i = 0; i < 3; i++)
        select_defectoskopist[i] = param_u[16+i];

    QFile file(QDir::home().absolutePath() + "/sdvk_defectockopist.ini");
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        while(!stream.atEnd())
        {
            QString str = stream.readLine();
            list_defectoskopist << str;
        }
    }
    else
        list_defectoskopist.clear();
    file.close();
    QFile fileps(QDir::home().absolutePath() + "/sdvk_ps.ini");
    if(fileps.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&fileps);
        while(!stream.atEnd())
        {
            QString str = stream.readLine();
            list_ps << str;
        }
    }
    else
        list_ps.clear();
    fileps.close();
 }
void CParam::SetEnabledDat(const unsigned n, const unsigned oborot, const unsigned state)
{
    if(n > 8)
        return;
    if(state)
        enabled_dat[oborot] |= (0x01 << (n-1));
    else
        enabled_dat[oborot] &= ~(0x01 << (n-1));
}
unsigned CParam::GetEnabledDat(const unsigned n, const unsigned oborot) const
{
    if(n > 8)
        return 0;
    return (enabled_dat[oborot] & (0x01 << (n-1)) )? 1 : 0;
}
void CParam::SetMouseEnabled(const bool state)
{
    mouse_enabled = (state)? 1 : 0;
    if(mouse_enabled)
        QApplication::setOverrideCursor(Qt::PointingHandCursor);
    else
    {
        QApplication::setOverrideCursor(Qt::BlankCursor);
      //  QApplication::changeOverrideCursor(Qt::BlankCursor);
    }
}


