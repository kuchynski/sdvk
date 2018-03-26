#ifndef CQUESTIODIALOGDIALOG_H
#define CQUESTIODIALOGDIALOG_H

#include <QDialog>
#include "ceditps.h"


class CQuestionDialog : public QDialog
{
    Q_OBJECT

    QLabel label;
    CButtons buttons;
    unsigned ret;
    unsigned wid_my, height_label, max_x, max_y;
    int timer_id, timer_st;
    QRect rect_my;
    QImage image_my;

    void timerEvent(QTimerEvent *event);
public:
    explicit CQuestionDialog(const QList<QString> str, const QList<QString> but, const unsigned wid, const unsigned size_x, const unsigned size_y, QWidget *parent = 0);

    unsigned GetResult() const {return ret;}


    void paintEvent(QPaintEvent *p);
  //  void resizeEvent(QResizeEvent *r);
signals:

public slots:
    void OnButtonsClick(unsigned n, bool b);
};

#endif
