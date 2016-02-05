#include "gameconfigurator.h"

GameConfigurator::GameConfigurator()
{

}

void GameConfigurator::init()
{
    scale=200;
    windowWidth=800;
    windowHeight=600;
    spriteConfiguratorName="test.xml";
    characterConfigFileName="character.xml";
    terrainConfigFileName="terrain.xml";
    decorationConfigFileName="decoration.xml";

    format.setSamples(16);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
}
