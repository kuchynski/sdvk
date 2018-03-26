#ifndef CBASEWINDOW_H
#define CBASEWINDOW_H

#include <QWidget>
#include <QtGui>
#include "cbuttons.h"

class CBaseWindow : public QWidget
{
private:
    Q_OBJECT
    CButtons buttons;

    QWidget *child;
    int timer_up, timer_down;
    unsigned timer_step, timer_max_step;
    unsigned center_x, center_y;

    void timerEvent(QTimerEvent *event);
protected:
public:
    explicit CBaseWindow(const QString name_but_ok, const QString name_but_cancel, QWidget *parent = 0);

    void resizeEvent(QResizeEvent *r);
    void paintEvent(QPaintEvent *p);

    virtual void SetVisible(const bool vis);

    void SetChild(QWidget *ch, unsigned cx, unsigned cy, const unsigned tms = 10);
    void CloseChild();
signals:
    void BaseSignal(int signal);

public slots:
    virtual void OnButtonsBaseClick(unsigned n, bool s);

};

#endif // CBASEWINDOW_H
