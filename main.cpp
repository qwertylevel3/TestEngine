#include"T3Engine/t3engine.h"
#include"T3Engine/gameconfigurator.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameConfigurator::instance()->init();

    T3Engine::instance()->show();

    return a.exec();
}
