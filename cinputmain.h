#ifndef CINPUTMAIN_H
#define CINPUTMAIN_H

#include <QWidget>
#include "cbasewindow.h"
#include "CWheel.h"
#include "cinput.h"

class CInputMain : public CBaseWindow
{
    Q_OBJECT

    CInput input;
    QImage image_my;
public:
    explicit CInputMain(QWidget *parent = 0);

    void Run();
    void resizeEvent(QResizeEvent *r);
    void paintEvent(QPaintEvent *p);
signals:
    void NewWheel(const CWheel &w);

public slots:
    void OnButtonsBaseClick(unsigned n, bool s);
    void OnNewWheel(const CWheel &w);

};

#endif // CINPUTMAIN_H
