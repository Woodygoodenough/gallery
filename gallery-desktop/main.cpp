#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //As the base class for all widget objects in Qt, QWidget provides the show() method to make the widget visible.
    //If the widget is a top-level window, this will create a new window on the screen; if it's a child widget, it will be displayed within its parent widget.
    return a.exec();
}
