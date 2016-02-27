#include"t3engine.h"
#include"gameconfigurator.h"
#include"spritecreator.h"
#include"stable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GameConfigurator::instance()->init("conf/spriteCreator.xml");

    T3Engine::instance()->show();
    T3Engine::instance()->hide();

    SpriteCreator spriteCreator;
    spriteCreator.show();

    return a.exec();
}
