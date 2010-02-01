#include <QtGui/QApplication>
#include "composerdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ComposerDialog w;
    w.show();
    return a.exec();
}
