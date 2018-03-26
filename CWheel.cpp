//---------------------------------------------------------------------------
#include "CWheel.h"

//---------------------------------------------------------------------------
CWheel::CWheel()
{}
//---------------------------------------------------------------------------
CWheel::CWheel(const QString &num, const int t, const int d, const QString &op):
               number(num), operating(op),
               th_of_rim_left(t), th_of_rim_right(t),
               diameter_left(d), diameter_right(d), defect(0)
{}
//---------------------------------------------------------------------------
CWheel::CWheel(const QString &fn)
{
  int tmp;
  file_name = fn;
  CFileBin f(file_name, CFileBin::ETRead);
  if(!f.GetState())
      throw this;
  number = CString(f);
  operating = CString(f);
  ps = CString(f);

  if(!f.Read(&th_of_rim_left, sizeof(th_of_rim_left), 1)) throw this;
  if(!f.Read(&th_of_rim_right, sizeof(th_of_rim_right), 1)) throw this;
  if(!f.Read(&diameter_left, sizeof(diameter_left), 1)) throw this;
  if(!f.Read(&diameter_right, sizeof(diameter_right), 1)) throw this;
  if(!f.Read(&defect, sizeof(defect), 1)) throw this;
  if(defect != 1)
      defect = 0;
  date_time = CDateTime(f);
  if(!f.Read(&tmp, sizeof(tmp), 1)) throw this;
  try
  {
    map_of_datchik_left = CMapOfDatchik(f);
    map_of_datchik_right = CMapOfDatchik(f);
  }
  catch(CMapOfDatchik *mod)
  {
    delete mod;
    throw this;
  }
}
//---------------------------------------------------------------------------
CWheel::CWheel(const CWheel& copy_wheel)
{
    *this = copy_wheel;
}
//---------------------------------------------------------------------------
CWheel& CWheel::operator=(const CWheel &copy_wheel)
{
  if(this != &copy_wheel)
  {
    date_time = copy_wheel.date_time;
    number = copy_wheel.number;
    th_of_rim_left = copy_wheel.th_of_rim_left;
    th_of_rim_right = copy_wheel.th_of_rim_right;
    diameter_left = copy_wheel.diameter_left;
    diameter_right = copy_wheel.diameter_right;
    operating = copy_wheel.operating;
    ps = copy_wheel.ps;
    map_of_datchik_left = copy_wheel.map_of_datchik_left;
    map_of_datchik_right = copy_wheel.map_of_datchik_right;
    file_name = copy_wheel.file_name;
    defect = copy_wheel.defect;
  }
  return *this;
}
//---------------------------------------------------------------------------
void CWheel::ClearFirstD()
{
  map_of_datchik_left.ClearFirstD();
  map_of_datchik_right.ClearFirstD();
}
//---------------------------------------------------------------------------
bool CWheel::SaveToFile()
{
    if(file_name != "")
        return SaveToFile(file_name);
    return false;
}
bool CWheel::SaveToFile(const QString &fn)
{
    file_name = fn;
    CFileBin f(fn, CFileBin::ETWrite);
    if(!f.GetState())
        return false;
    try
    {
        number.SaveToFile(f);
        operating.SaveToFile(f);
        ps.SaveToFile(f);

        int tmp1 = 0;
        if(!f.Write(&th_of_rim_left, sizeof(th_of_rim_left), 1)) throw 0;
        if(!f.Write(&th_of_rim_right, sizeof(th_of_rim_right), 1)) throw 0;
        if(!f.Write(&diameter_left, sizeof(diameter_left), 1)) throw 0;
        if(!f.Write(&diameter_right, sizeof(diameter_right), 1)) throw 0;
        if(!f.Write(&defect, sizeof(defect), 1)) throw 0;
        date_time.SaveToFile(f);
        if(!f.Write(&tmp1, sizeof(tmp1), 1)) throw 0;
        map_of_datchik_left.SaveToFile(f);
        map_of_datchik_right.SaveToFile(f);
    }
    catch(int)
    {
        return false;
    }
    return true;
}
void CWheel::PaintOnGrid(QList<QString> &list)
{
    list.clear();
    list << date_time.GetTime();
    list << number.GetQString();
    list << ((defect)? QString::fromLocal8Bit("дефект") : "");
    list << QString::number(th_of_rim_left);// + " / " + QString::number(th_of_rim_right);
    list << QString::number(diameter_left);// + " / " + QString::number(diameter_right);
    list << operating.GetQString();
    list << ps.GetQString();
}
//---------------------------------------------------------------------------
/*void CWheel::PrintOnScreen(int row, bool activ) const
{
  AnsiString txt;
  grid_wheel->Cells[0][row] = " " + IntToStr(row);
  grid_wheel->Cells[1][row] = number.AnsiString();
  grid_wheel->Cells[2][row] = date_time.GetTime();
  grid_wheel->Cells[3][row] = IntToStr(th_of_rim_left) + "/" + IntToStr(th_of_rim_right);
  grid_wheel->Cells[4][row] = IntToStr(diameter_left)  + "/" + IntToStr(diameter_right);
  grid_wheel->Cells[5][row] = operating.AnsiString();
  grid_wheel->Cells[6][row] = ps.AnsiString();

  if(activ)
    PrintDefects();
}
//---------------------------------------------------------------------------
void CWheel::PaintMapOfDatchik(TImage *pic_map_l, TImage *pic_map_r, int new_datchik)
{
  if(pic_map_l)
    map_of_datchik_left.PaintOnScreen(pic_map_l, 0, new_datchik);
  if(pic_map_r)
    map_of_datchik_right.PaintOnScreen(pic_map_r, 0, new_datchik);
}*/
//---------------------------------------------------------------------------
void CWheel::SetMapOfDatchik(CMapOfDatchik &new_map_l, CMapOfDatchik &new_map_r)
{
  map_of_datchik_left = new_map_l;
  map_of_datchik_right = new_map_r;
}
//---------------------------------------------------------------------------
bool CWheel::IsDefect(const unsigned side, const unsigned dat, const int oborot)
{
    if(!side)
        return map_of_datchik_left.IsDefect(dat, oborot);
    else if(side == 1)
        return map_of_datchik_right.IsDefect(dat, oborot);
    return false;
}
bool CWheel::IsDefecAll()
{
    if(map_of_datchik_left.IsDefectAll())
        return true;
    return map_of_datchik_right.IsDefectAll();
}
//---------------------------------------------------------------------------

