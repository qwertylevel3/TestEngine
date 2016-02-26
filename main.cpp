#include"t3engine.h"
#include"gameconfigurator.h"
#include"spritecreator.h"
#include"stable.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //GameConfigurator::instance()->init();

    //T3Engine::instance()->show();
    SpriteCreator spriteCreator;
    spriteCreator.show();

    return a.exec();
}
