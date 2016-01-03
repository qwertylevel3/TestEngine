#include"t3engine.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    T3Engine engine;
    engine.init();
    engine.run();

    return a.exec();
}
