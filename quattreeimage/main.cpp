#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    long int _curColorIndex = 0;
//    while(1)
    {
        int l = _curColorIndex<<1;
        int red = _curColorIndex & 0xff;
        int green = (_curColorIndex >> 8) & 0xff;
        int blue = (_curColorIndex >> 16) & 0xff;
        int alpha = (_curColorIndex >> 24) & 0xff;

        ++_curColorIndex;
    }







    Widget w;
    w.show();

    return a.exec();
}
