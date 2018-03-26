#ifndef CINPUTTEXTDIALOG_H
#define CINPUTTEXTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include "cbuttons.h"


class CInputTextDialog : public QDialog
{
    Q_OBJECT

    QLineEdit line_edit;
    CButtons buttons;
    unsigned max_x, max_y;
    int timer_id, timer_st;
    QRect rect_my;
    QImage image_my;

    void timerEvent(QTimerEvent *event);
public:
    explicit CInputTextDialog(const QString str, const unsigned size_x, const unsigned size_y, QWidget *parent = 0);

    QString GetStr() const;
    void paintEvent(QPaintEvent *p);
signals:

public slots:
    void OnButtonsClick(unsigned n, bool b);
};

#endif // CINPUTTEXTDIALOG_H
