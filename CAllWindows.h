#ifndef CAllWindows_H
#define CAllWindows_H

#include <QWidget>
#include <QtGui>
#include "cbuttonscheck.h"

class CAllWindows : public QWidget
{
    Q_OBJECT
public:
    struct SAllWindowsInit
    {
        enum eDirection {edVertical, edHorizontal, edNone};

        eDirection direction_frame;
        eDirection direction_widget;
        unsigned rewindow_time_all;
        unsigned rewindow_kol_step;
        unsigned frame_height;
        unsigned frame_width;
        SAllWindowsInit(): rewindow_time_all(700), rewindow_kol_step(10), frame_height(30), frame_width(150),
                           direction_frame(edHorizontal), direction_widget(edHorizontal) {}
    };

    explicit CAllWindows(QWidget *parent = 0);

    void SetEnabledMouse(const bool e) {enabled_mouse = e;}
    void SetInitStruct(const SAllWindowsInit &set_struct);
    void AddWidget(QWidget *w, QString name);
    void AddWidget(QWidget *w, QString name, QPixmap &pix);
    void SetVisibleWidget(const unsigned n);
    unsigned GetVisibleWidget() const;
    void RePlaceWidget(unsigned n, QWidget *w, QString name, QPixmap &pix);
    void paintEvent(QPaintEvent *p);
    void resizeEvent(QResizeEvent *r);
private:

    QBoxLayout *box_layout;
    QList<QWidget*> list_windows;
    QWidget *main_widget;
    SAllWindowsInit init_struct;
    unsigned tek, new_tek;
    bool enabled_mouse;
    int mouse_press_x, mouse_press_y;
    bool mouse_press;
    CButtonsCheck buttons;

    int timer_id, timer_st;

    void SetWidget(const unsigned &n);
    void timerEvent(QTimerEvent *event);

protected:
    virtual void mousePressEvent(QMouseEvent *pe);
    virtual void mouseMoveEvent(QMouseEvent *pe);
    virtual void mouseReleaseEvent(QMouseEvent *pe);

signals:
    void NewWindow(unsigned n);

private slots:
    void OnButtonsClick(unsigned n, bool s = true);

public slots:
    virtual void OnPressButton(unsigned n){}
   // virtual void OnPressButtonStart1(){}
   // virtual void OnPressButtonStart2(){}
   // virtual void OnPressButtonCancel2(){}
   // virtual void OnPressButtonCancel3(){}
   // virtual void OnNewWheel(CWheel &w){}
};

#endif // CAllWindows_H
