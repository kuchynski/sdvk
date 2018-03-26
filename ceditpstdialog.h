#ifndef CINPUTTEXTDIALOG_H
#define CINPUTTEXTDIALOG_H

#include <QDialog>
#include "ceditps.h"


class CEditPsDialog : public QDialog
{
    Q_OBJECT

    CEditPs edit;
    CButtons buttons;
    unsigned max_x, max_y;
    int timer_id, timer_st;
    QRect rect_my;
    QImage image_my;

    void timerEvent(QTimerEvent *event);
public:
    explicit CEditPsDialog(const QString str, int spb, const unsigned size_x, const unsigned size_y, QWidget *parent = 0);

    QString GetStr() const {return edit.GetStr();}
    int GetCheck() const {return edit.GetCheck();}

    void paintEvent(QPaintEvent *p);
  //  void resizeEvent(QResizeEvent *r);
signals:

public slots:
    void OnButtonsClick(unsigned n, bool b);
};

#endif // CINPUTTEXTDIALOG_H
