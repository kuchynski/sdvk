#ifndef CBDTABLE_H
#define CBDTABLE_H

#include "cbasewindow.h"
#include "cparam.h"
#include "ctable.h"
#include "cbuttons.h"
#include "cinputdatadialog.h"
#include "CWheel.h"
#include "CStack.h"
#include "cimagedefect.h"
#include "ceditpstdialog.h"


class CBdTable : public QWidget
{
private:
    Q_OBJECT

    QWidget *wid1;
    QLabel label_date;
    CTable table;
    QImage image_back;//, image_my;
    CButtons buttons_main, buttons;
    QDate date;
    QDir dir;
    QString file_path, tek_file_path;
    CStack <CWheel> wheels;
    CImageDefect image_defect;

    bool SetDir(const QDate &_date);
    void SetDate();
    void PaintTable();
    void CloseSostav(const bool del = false);
    void ShowEditPS();
//    void PaintImageBack(const bool is_modal_diallog = false);
    void SetButtons();
public:
    explicit CBdTable(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *r);
    void paintEvent(QPaintEvent *p);

    void SetImageBack(const QImage &ib, const QRect &r);
signals:
    void OnPressButton(QDate d, CStack <CWheel> &w);
    void IAmReSize();
public slots:
    void OnButtonsMainClick(unsigned, bool);
    void OnButtonsClick(unsigned, bool);
    void OnTableClick(unsigned line);
    void OnTableClickDouble(unsigned line);
    void OnReSizeTable();
    void OnReSizeImageDefect();
    void OnNewWheel(const CWheel &w);
};

#endif
