#ifndef CBLOCKSCAN_H
#define CBLOCKSCAN_H

#include <QWidget>
#include <QPainter>
#include "cbuttons.h"
#include "CWheel.h"
#include "cparam.h"
#include "ceditps.h"
#include "cimagedefect.h"

class CBlockScan : public QWidget
{
    Q_OBJECT

    CButtons button_run;

    QLabel label_block, label_block_data1, label_block_data2;
    CEditPs edit_ps;
    CImageDefect image_defect;
  //  QLabel label_ps;
 //   QLineEdit edit_ps;
 //   CTable table_ps;

    CWheel wheel;
    CMapOfDatchik map_of_datchik[2];
    QImage image_back, image_my;

    void SetTypeVisiable(const bool n);
public:
    explicit CBlockScan(QWidget *parent = 0);

    void Run(const CWheel &w);
    void OnBlockState(unsigned type, unsigned w, unsigned l);
    void paintEvent(QPaintEvent *p);
    void resizeEvent(QResizeEvent *r);
    void SetImageBack(const QImage &ib, const QRect &r);
signals:
    void NewWheel(const CWheel &w);
    void PressButton(unsigned n);
    void IAmResize();

public slots:

    void OnPressButton(unsigned n, bool v);
};

#endif // CBLOCKSCAN_H
