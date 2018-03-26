#ifndef CBDMAIN_H
#define CBDMAIN_H

#include <QWidget>
#include "cbasewindow.h"
#include "cbd.h"
#include <QObject>

class CBdMain : public CBaseWindow
{
    Q_OBJECT

    CBd bd;
    QImage image_my;
public:
    explicit CBdMain(QWidget *parent = 0);

    void Run();
    void resizeEvent(QResizeEvent *r);
    void paintEvent(QPaintEvent *p);
signals:

public slots:
    void OnButtonsBaseClick(unsigned n, bool s);
    void OnNewWheel(const CWheel &w);

};

#endif // CBDMAIN_H
