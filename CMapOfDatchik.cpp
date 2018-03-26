//---------------------------------------------------------------------------
#include "CMapOfDatchik.h"

//---------------------------------------------------------------------------
CMapOfDatchik::CMapOfDatchik(int md): pm(0)
{
  number_datchik = (md > max_datchik)? max_datchik : md;
  for(int dat = 0; dat < max_datchik; dat ++)
  {
    map[dat] = new SPixels;
    map[dat]->number_oborot = 2;
    map[dat]->number_pixels = param.GetRast(0);
    for(int k = 0; k < max_oborot; k ++)
    {
      for(int pix = 0; pix < max_pixels; pix ++)
        map[dat]->oborot[k][pix] = 0;//(pix % 10)? 0 : 1;
    }
  }
}
//---------------------------------------------------------------------------
CMapOfDatchik::CMapOfDatchik(CFileBin &f): pm(0)
{
    if(!f.Read(&number_datchik, sizeof(number_datchik), 1)) throw this;
    for(int dat = 0; dat < max_datchik; dat ++)
    {
        map[dat] = new SPixels;
        if(!f.Read(map[dat], sizeof(SPixels), 1)) throw this;
    }
}
//---------------------------------------------------------------------------
CMapOfDatchik::CMapOfDatchik(const CMapOfDatchik& copy_map_of_datchik)
{
    number_datchik = copy_map_of_datchik.number_datchik;
    pm = copy_map_of_datchik.pm;
    for(int dat = 0; dat < max_datchik; dat ++)
    {
        map[dat] = new SPixels;
        *map[dat] = *copy_map_of_datchik.map[dat];
    }
}
//---------------------------------------------------------------------------
CMapOfDatchik::~CMapOfDatchik()
{
  for(int dat = 0; dat < max_datchik; dat ++)
    if(map[dat])
      delete map[dat];
}
//---------------------------------------------------------------------------
CMapOfDatchik& CMapOfDatchik::operator=(const CMapOfDatchik &copy_map_of_datchik)
{
    if(this != &copy_map_of_datchik)
    {
        number_datchik = copy_map_of_datchik.number_datchik;
        pm = copy_map_of_datchik.pm;
        for(int dat = 0; dat < max_datchik; dat ++)
           // for(int k = 0; k < max_oborot; k ++)
           // {
                *map[dat] = *copy_map_of_datchik.map[dat];
//                for(int pix = 0; pix < max_pixels; pix ++)
  //                  map[dat]->oborot[k][pix] = copy_map_of_datchik.map[dat]->oborot[k][pix];
    //            map[dat]->number_pixels = copy_map_of_datchik.map[dat]->number_pixels;
      //          map[dat]->number_pixels = copy_map_of_datchik.map[dat]->number_pixels;
           // }
  }
  return *this;
}
//---------------------------------------------------------------------------
void CMapOfDatchik::ClearFirstD()
{
  if(map[0])
    for(int k = 0; k < max_oborot; k ++)
      for(int pix = 0; pix < max_pixels; pix ++)
        map[0]->oborot[k][pix] = 0;
}
//---------------------------------------------------------------------------
bool CMapOfDatchik::SetPixels(int dat, int ob, int pix, bool state)
{
  if((dat >= number_datchik))// || (ob >= map[dat]->number_oborot))
    return false;
  if(pix >= map[dat]->number_pixels)
    pix = map[dat]->number_pixels - 1;
  if(-pix >= map[dat]->number_pixels)
    pix = -map[dat]->number_pixels + 1;
  if(pix < 0)
    pix = map[dat]->number_pixels + pix;
  if(state)
    map[dat]->oborot[ob][pix] = 1;
  return true;
}
void CMapOfDatchik::SaveToFile(CFileBin &f)
{
    if(!f.Write(&number_datchik, sizeof(number_datchik), 1)) throw 0;
    for(int i = 0; i < max_datchik; i ++)
        if(!f.Write(map[i], sizeof(SPixels), 1)) throw 0;
}
//---------------------------------------------------------------------------
void CMapOfDatchik::PaintOnScreen(QImage &image, QRect rect, const unsigned datchik, const int coordinate, const bool simple) const
{//datchik = max_datchik => all datchik
    if(datchik > max_datchik)
        return;
    const int width = rect.width();
    const int height = rect.height();
    const int center_x = rect.x() + width / 2;
    const int center_y = rect.y() + height / 2;
    const int radius = height / 2 - 5;
    const int radius2 = radius / 4;//height / 2 - 80;
    const int radius3 = radius / 6; // 2 - 95;
    const int h_pis = radius / 40;

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(170, 170, 170, 255));
    painter.setPen(QColor(0, 0, 0, 255));
    painter.setBrush(QColor(90, 90, 90, 255));
    painter.drawEllipse(QRect(center_x-radius, center_y-radius, radius*2, radius*2));
    painter.setBrush(QColor(70, 70, 70, 255));
    painter.drawEllipse(QRect(center_x-radius2, center_y-radius2, radius2*2, radius2*2));
    painter.setBrush(QColor(170, 170, 170, 255));
    painter.drawEllipse(QRect(center_x-radius3, center_y-radius3, radius3*2, radius3*2));

    const double grad_to_rad = M_PI / 180.0;
    const int coord_grad_m = coordinate;
    const double coord_rad_m = static_cast<double>(coord_grad_m) * grad_to_rad;
    const int x_m1 = center_x + (radius2+h_pis) * cos(-coord_rad_m);
    const int y_m1 = center_y + (radius2+h_pis) * sin(-coord_rad_m);
    const int x_m2 = center_x + (radius-h_pis) * cos(-coord_rad_m);
    const int y_m2 = center_y + (radius-h_pis) * sin(-coord_rad_m);
    const int size_ellipse = (datchik == max_datchik)? radius / 50 : radius / 25;
    painter.setPen(QPen(Qt::red, h_pis));
    painter.drawLine(x_m1, y_m1, x_m2, y_m2);
    QColor color_dat[9] = {QColor(255, 0, 0, 255), QColor(200, 150, 0, 255), QColor(0, 255, 0, 255),
                           QColor(0, 150, 200, 255), QColor(0, 0, 255, 255), QColor(255, 0, 0, 255),
                           QColor(0, 255, 0, 255), QColor(0, 0, 255, 255), QColor(255, 255, 0, 255)};
    for(int dat = 0; dat < max_datchik; dat ++)
    {
        if((datchik < max_datchik) && (datchik != dat))
            continue;
     //   if(simple)
       //     painter.setPen(QPen(color_dat[dat], size_ellipse/2));
       // else
            painter.setPen(QPen(color_dat[dat], size_ellipse));
//            painter.setPen(color_dat[dat]);
        painter.setBrush(color_dat[dat]);
        int radius_datchik = (datchik == max_datchik)? radius - 4 * (dat + 1) : radius - 4;
        for(int pix = 0; pix < map[dat]->number_pixels; pix ++)
        {
            unsigned int def = 0;
            for(int k = 0; k < map[dat]->number_oborot; k ++)
                if(map[dat]->oborot[k][pix])
                   def = 1;
            if(def)
            {
                const int coord_grad = coordinate - (pix * 359) / map[dat]->number_pixels - 90;
                const double coord_rad = static_cast<double>(coord_grad) * grad_to_rad;
                const int x = center_x + radius_datchik * cos(-coord_rad);
                const int y = center_y + radius_datchik * sin(-coord_rad);
               // if(simple)
                    painter.drawPoint(QPointF(x, y));
//                painter.drawRect(QRect(x-size_rect/2, y-size_rect/2, size_rect, size_rect));
               // else
                 //   painter.drawEllipse(QRect(x-size_ellipse/2, y-size_ellipse/2, size_ellipse, size_ellipse));
            }
        }

    }

    painter.end();
}
/*bool CMapOfDatchik::SetNumberPixels(int d, int o, int n)
{
  if(d >= max_datchik)
    return false;
  if(o >= max_oborot)
    return false;
  if(n >= max_pixels)
    return false;
  map[d]->number_pixels = n;
  int sm = max_pixels - n;
  if(pm < 0)
    for(int i = 0; i < n; i ++)
      map[d]->oborot[o][i] = map[d]->oborot[o][i+sm];
}
//---------------------------------------------------------------------------
void CMapOfDatchik::SetNumberPixelsAll(int n)
{
  for(int dat = 0; dat < number_datchik; dat ++)
    map[dat]->number_pixels = n;
}*/
//---------------------------------------------------------------------------
bool CMapOfDatchik::IsDefect(const unsigned dat, const int oborot)
{
    for(int pix = 0; pix < map[dat]->number_pixels; pix ++)
    {
        const unsigned beg = (oborot < 0)? 0 : oborot;
        const unsigned end = (oborot < 0)? map[dat]->number_oborot-1 : oborot;
        for(unsigned k = beg; k <= end; k ++)
            if(map[dat]->oborot[k][pix])
                return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool CMapOfDatchik::IsDefectAll()
{
    for(unsigned dat = 0; dat < max_datchik - 1; dat ++)
        for(unsigned pix = 0; pix < map[dat]->number_pixels; pix ++)
        {
            const unsigned end = map[dat]->number_oborot-1;
            for(unsigned k = 0; k <= end; k ++)
                if(map[dat]->oborot[k][pix])
                    return true;
        }
    return false;
}
//---------------------------------------------------------------------------
