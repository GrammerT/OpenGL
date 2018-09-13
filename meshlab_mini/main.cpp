#include "mainwindow.h"
#include <QApplication>
#include <clocale>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::setlocale(LC_ALL,"C");
    QLocale::setDefault(QLocale::C);
#if QT_VERSION >= 0x050100
    // Enable support for highres images (added in Qt 5.1, but off by default)
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
    MainWindow w;
    w.showMaximized();

    FileOpenEater *filterObj=new FileOpenEater(&w);
    a.installEventFilter(filterObj);
    a.processEvents();

    return a.exec();
}


