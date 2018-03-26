#ifndef CINPUTDATADIALOG_H
#define CINPUTDATADIALOG_H

#include <QDialog>
#include <QGridLayout>
#include "cbuttons.h"
#include "cinputdatadialog.h"

class CInputDataDialog : public QDialog
{
    Q_OBJECT

    CButtons buttons;
    QCalendarWidget calendar;
    unsigned max_x, max_y;
    int timer_id, timer_st;
    QRect rect_my;
    QImage image_my;

    void timerEvent(QTimerEvent *event);
public:
    explicit CInputDataDialog(const QDate date, const unsigned size_x, const unsigned size_y, QWidget *parent = 0);

    QDate GetDate() const;
    void paintEvent(QPaintEvent *p);
signals:

public slots:
    void OnButtonsClick(unsigned n, bool b);
};

#endif // CINPUTDATADIALOG_H
