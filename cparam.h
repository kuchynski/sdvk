#ifndef CPARAM_H
#define CPARAM_H

#include <QString>
#include <QSettings>
#include <QMutex>
#include <QDir>
#include <QTextStream>
#include <QtGui>

#define size_param 20
class CParam
{
public:
    CParam();
    ~CParam();

    void SetRast(const unsigned n, const unsigned &u) { if(n < 10) rast[n] = u;}
    void SetEnabledDat(const unsigned n, const unsigned oborot, const unsigned state);
    unsigned GetRast(const unsigned n)const { return (n < 10)? rast[n] : 0;}
    unsigned GetEnabledDat(const unsigned n, const unsigned oborot) const;
    QList<QString> GetListDefectoskopist() const {return list_defectoskopist;}
    QList<QString> GetListPs() const {return list_ps;}
    void SetListDefectoskopist(const QList<QString> &ld) {list_defectoskopist = ld;}
    void SetListPs(const QList<QString> &lp) {list_ps = lp;}
    unsigned GetComNumber()const  {return com_number;}
    void SetComNumber(const unsigned c) {com_number = c; SetSettings();}
    void SetLastDiametr(const unsigned n, const unsigned d){if(n < 2) last_diametr[n] = d;}
    unsigned GetLastDiametr(const unsigned n){return (n < 2)? last_diametr[n] : 845;}
    unsigned GetSelectDefectoskopist(const unsigned n) const {return (n < 3)? select_defectoskopist[n] : 0;}
    void SetSelectDefectoskopist(const unsigned n, const unsigned u) {if(n < 3) select_defectoskopist[n] = u;}
    bool GetMouseEnabled()const {return mouse_enabled != 0;}
    void SetMouseEnabled(const bool state = true);
    void SetSizeXY(const unsigned x, const unsigned y) {sizeXY[0] = x; sizeXY[1] = y;}
    unsigned GetSizeX()const {return sizeXY[0];}
    unsigned GetSizeY()const {return sizeXY[1];}
    void SetColor(const unsigned n, const QColor c) {if(n < 10) color[n] = c;}
    QColor GetColor(const unsigned n) const {return (n < 10)? color[n] : Qt::white;}

    void SetSettings();
private:

    QSettings settings;
    QMutex mutex;
    unsigned param_u[size_param];
    int param_i[size_param];

    unsigned rast[10];
    unsigned com_number;
    unsigned enabled_dat[2];
    unsigned count;
    unsigned last_diametr[2];
    unsigned select_defectoskopist[3];
    unsigned mouse_enabled;
    unsigned sizeXY[2];
    QColor color[10];
    QList<QString> list_defectoskopist;
    QList<QString> list_ps;

    void ReadSettings();
};
extern CParam param;

#endif // CPARAM_H
