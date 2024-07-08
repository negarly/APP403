#include "myserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myserver server;
    // w.show();
    return a.exec();
}
