#ifndef COPTIONSWINDOW_H
#define COPTIONSWINDOW_H

#include "cbasewindow.h"
#include "clabelchange.h"
#include "cparam.h"
#include "cspinbox.h"
#include "cspisok.h"
#include "cenableddatchik.h"

class COptionsWindow : public CBaseWindow
{
private:
    Q_OBJECT

    CLabelChange label_change;
    CSpinBox spinbox_rast0;
    CSpinBox spinbox_rast1;
    CSpinBox spinbox_rast2;
    CSpisok spisok_defectoskopist, spisok_ps;
    CEnabledDatchik enabled_datchik;
    CChecks check_mouse;

    QImage image_my;

public:
    explicit COptionsWindow(QWidget *parent = 0);

    void ReadDataFromParam();
    void SetMouseEnabled(const bool s);
    void resizeEvent(QResizeEvent *r);
    void paintEvent(QPaintEvent *p);
signals:

public slots:
    void OnButtonsBaseClick(unsigned n, bool s);
    void OnCheckMouseClick(unsigned, bool);
    void OnReSizeSpisokD();
    void OnReSizeSpisokPs();
    void OnReSizeEnabledD();
};

#endif // COPTIONSWINDOW_H
