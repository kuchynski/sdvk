#ifndef CWHEEL_H
#define CWHEEL_H

#include <vector>
#include "CDateTime.h"
#include "CMapOfDatchik.h"

using namespace std;

class CWheel {
private:
    QString file_name;
    CString number;
    CString operating;
    CString ps;
    CDateTime date_time;
    unsigned defect;
    int th_of_rim_left, th_of_rim_right;
    int diameter_left, diameter_right;
    CMapOfDatchik map_of_datchik_left;
    CMapOfDatchik map_of_datchik_right;
public:
    CWheel();
    CWheel(const QString &num, const int t, const int d, const QString &op);
    CWheel(const QString &fn);
    CWheel(const CWheel& copy_wheel);
    CWheel& operator=(const CWheel &copy_wheel);
    ~CWheel() {}


    bool SaveToFile();
    bool SaveToFile(const QString &fn);

    //    void PaintMapOfDatchik(TImage *pic_map_l, TImage *pic_map_r, int new_datchik);
    void SetMapOfDatchik(CMapOfDatchik &new_map_l, CMapOfDatchik &new_map_r);

    void SetNumber(const QString new_number) { number = CString(new_number);}
    QString GetNumber(){ return number.GetQString(); }
    CDateTime GetDateTime() const {return date_time;}
    QDate GetQDate()const {return date_time.GetQDate();}
    QString GetTime(){return date_time.GetTime();}

    QString GetFileName() const {return file_name;}
    unsigned GetDefect() const {return defect;}
    void SetDefect(const unsigned d) {defect = d;}
    QString GetDate() {return date_time.GetDate();}
    QString GetNumberKP() {return number.GetQString();}
    int GetThicknessOfRimLeft() {return th_of_rim_left;}
    int GetThicknessOfRimRight() {return th_of_rim_right;}
    int GetDiameterLeft() {return diameter_left;}
    int GetDiameterRight() {return diameter_right;}
    QString GetOperating() {return operating.GetQString();}
    bool IsDefect(const unsigned side, const unsigned dat, const int oborot = -1);
    bool IsDefecAll();
    void ClearFirstD();
    QString GetPS() const {return ps.GetQString();}
    void SetPS(const QString &str) {ps = CString(str);}
    CMapOfDatchik GetMapLeft() const {return map_of_datchik_left;}
    CMapOfDatchik GetMapRight() const {return map_of_datchik_right;}

    void PaintOnGrid(QList<QString> &list);
};
//----------------------------------------------------------------------------
#endif //CWHEEL_H
