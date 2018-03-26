#ifndef CIMAGEDEFECT_H
#define CIMAGEDEFECT_H

#include <QWidget>
#include <QPainter>
#include <QtGui>
#include "cparam.h"
#include "cbuttonscheck.h"
#include "CMapOfDatchik.h"

class CImageDefect : public QWidget
{
    Q_OBJECT
private:
    CMapOfDatchik left, right;
    QImage image, image_back;
    CButtonsCheck *buttons;

    void Paint();
public:
    explicit CImageDefect(QWidget *parent = 0);

    void SetMapOfDatchik(CMapOfDatchik l, CMapOfDatchik r);
    explicit CImageDefect(CMapOfDatchik l, CMapOfDatchik r, QWidget *parent = 0);
    void SetImageBack(const QImage &ib, const QRect &r);

    void resizeEvent(QResizeEvent *r);
    void paintEvent(QPaintEvent *p);
protected:
signals:
    void IAmReSize();

public slots:
    void OnButtonsClick(unsigned n, bool b);
};

#endif
