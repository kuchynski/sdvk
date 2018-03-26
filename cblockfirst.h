#ifndef CBLOCKFIRST_H
#define CBLOCKFIRST_H

#include <QWidget>
#include <QPainter>
#include "cbuttonscheck.h"
#include "cspinbox.h"
#include "ctable.h"
#include "cbuttons.h"
#include "ccomport.h"
#include "cparam.h"
#include "CWheel.h"

class CBlockFirst : public QWidget
{
    Q_OBJECT
    CButtonsCheck check_port;
    CButtons button_run;
 //   CButtons button_set_motor_end;
    CComPort com_port;
    QLabel label_com_state;
    QProcess *process_reload;
    CSpinBox spin_box_diametr;
    CTable table_defectoskopist;
    QLineEdit line_edit_number;

    bool now_exit;
    QString dir_path;
    int timer_new_second;
    void timerEvent(QTimerEvent *event) {com_port.SetNewSecond();}

    QImage image_back;

    void setVisibleStart(const bool s);
public:
    explicit CBlockFirst(QWidget *parent = 0);
    ~CBlockFirst();

    void Run();
    void Begin(unsigned h) {com_port.Begin(1, h);}
    void Stop(const bool only_stoped = false) {com_port.Stop(only_stoped);}
    void paintEvent(QPaintEvent *p);
    void resizeEvent(QResizeEvent *r);
    void SetImageBack(const QImage &ib, const QRect &r);
signals:
    void PressButtonStart(CWheel &);
    void IAmResize();

public slots:
    void OnNewComPortState(unsigned);
    void OnEndReload(int res);
    void on_checked_portChanged(unsigned n, bool tmp);
    void OnPressButtonStart(unsigned n, bool v);
  //  void OnPressButtonSetMotor(unsigned n, bool v);
    void OnClickLineTablet(unsigned n);
};

#endif // CBLOCKFIRST_H
