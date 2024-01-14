#include "Serial.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Serial w;
    w.show();
    return a.exec();
}
