#ifndef CMAPOFDATCHIK_H
#define CMAPOFDATCHIK_H

#include <stdio.h>
#include <math.h>
#include <vector>
#include "cfilebin.h"
#include "cparam.h"

const int max_datchik = 9;
const int max_oborot = 5;
const int max_pixels = 520;
//----------------------------------------------------------------------------
class CMapOfDatchik {
public:
    CMapOfDatchik(int md = max_datchik);//, int mo = max_oborot, int mp = max_pixels);
    CMapOfDatchik(CFileBin &f);
    CMapOfDatchik(const CMapOfDatchik& copy_map_of_datchik);
    virtual ~CMapOfDatchik();
    CMapOfDatchik& operator=(const CMapOfDatchik &copy_map_of_datchik);

    //bool SetNumberPixels(int d, int o, int n);
   // void SetNumberPixelsAll(int n);
    bool SetPixels(int dat, int ob, int pixel, bool state);
    void SaveToFile(CFileBin &f);
   // void PaintOnScreen(TImage * pic, int coordinate, int new_datchik) const;
    void PaintOnScreen(QImage &image, QRect rect, const unsigned datchik, const int coordinate, const bool simple = false) const;
    bool IsDefect(const unsigned dat, const int oborot = -1);
    bool IsDefectAll();
    void ClearFirstD();
protected:
    struct SPixels
    {
      unsigned char oborot[max_oborot][max_pixels];
      int number_oborot;
      int number_pixels;
    };
    int number_datchik;
    int pm;
    SPixels *map[max_datchik];
};
//----------------------------------------------------------------------------
#endif //CMAPOFDATCHIK_H
