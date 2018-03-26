#ifndef CINPUT_H
#define CINPUT_H

#include "CAllWindows.h"
#include "CWheel.h"
#include "cblockfirst.h"
#include "cblockscan.h"
#include "cquestiondialog.h"

class CInput : public CAllWindows
{
private:
    Q_OBJECT

    SAllWindowsInit init_struct;
    CBlockFirst block_first;
    CBlockScan block_scan;
    QImage image_back;
public:
    explicit CInput(QWidget *parent = 0);

    void Run();
    void Stop();
    void SetImageBack(const QImage &ib, const QRect &r);
signals:

public slots:
    void OnBlockState(unsigned type, unsigned w, unsigned l);
    void OnPressButton1(CWheel &w);
    void OnPressButton2(unsigned n);
    void OnReSizeBlockFirst();
    void OnReSizeBlockScan();
};

#endif // CINPUT_H
