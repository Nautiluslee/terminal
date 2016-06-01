#include "terminal.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    terminal w;
    w.show();

    return a.exec();
}
