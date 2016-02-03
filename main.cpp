#include"T3Engine/t3engine.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    T3Engine::instance()->show();

    return a.exec();
}
