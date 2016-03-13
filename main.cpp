#include"t3engine.h"
#include"gameconfigurator.h"
#include"spritecreator.h"
#include"worldcreator.h"
#include"stable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //GameConfigurator::instance()->init("conf/spriteCreator.xml");
    GameConfigurator::instance()->init("conf/config.xml");

    //T3Engine engine;
    //engine.show();

    WorldCreator worldCreator;
    worldCreator.show();

    return a.exec();
}
