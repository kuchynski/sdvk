#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include "cbasewindow.h"
#include "coptionswindow.h"
#include "clabelchange.h"
#include "cbdmain.h"
#include "cinputmain.h"

class CMainWindow : public CBaseWindow
{
private:
    Q_OBJECT

    CButtons buttons;
    QImage image_my;

    COptionsWindow options_window;
    CBdMain bd_window;
    CInputMain input_window;
public:
    explicit CMainWindow(QWidget *parent = 0);

    void resizeEvent(QResizeEvent *r);
    void paintEvent(QPaintEvent *p);
    void SetVisible(const bool vis);
signals:
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *pe);

public slots:
    void OnButtonsBaseClick(unsigned n, bool s);
    void OnButtonsClick(unsigned n, bool s);
    void OnOkCancelOptionsWindow(int);
    void OnOkCancelBdWindow(int);
    void OnOkCancelInputWindow(int);
};

#endif // CMAINWINDOW_H
