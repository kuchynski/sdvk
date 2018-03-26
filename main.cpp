#include <QtGui>
#include <iostream>
#include "cmainwindow.h"

using namespace std;

int main(int argc, char **argv)
{
    cout << "from andrei kuchynski" << endl;
    cout << "kuchynski@tut.by" << endl;
    cout << "+375 447302607" << endl;
    cout << "minsk 2013" << endl;
    QApplication app(argc, argv);
   // QSplashScreen splash(QPixmap("first.jpg"));

    //splash.show();

    QWidget widget_main;
    widget_main.setAttribute(Qt::WA_PaintOnScreen);
    QBoxLayout *layout_main = new QBoxLayout(QBoxLayout::LeftToRight);
    layout_main->setMargin(0);
    layout_main->setSpacing(0);
    widget_main.setLayout(layout_main);
    widget_main.resize(1000, 700);
    CMainWindow main_window;
    layout_main->addWidget(&main_window);

 //   QTime time;
  //  time.start();
   // while(time.elapsed() < 1000){}

  //  QApplication::setOverrideCursor(Qt::BlankCursor);
    widget_main.showFullScreen();
    param.SetMouseEnabled(param.GetMouseEnabled());
//    widget_main.show();
    //splash.finish(&widget_main);

    return app.exec();
}
