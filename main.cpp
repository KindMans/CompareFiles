#include "comparefile.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CompareFile w;
    w.show();
    return a.exec();
}
