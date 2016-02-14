#include "gameconfigurator.h"

GameConfigurator::GameConfigurator()
{

}

void GameConfigurator::init()
{
    scale=200;
    drawRect=false;
    paintNear=3;
    paintFar=20;
    windowWidth=800;
    windowHeight=600;
    spriteConfigFileName="test.xml";
    characterConfigFileName="character.xml";
    terrainConfigFileName="terrain.xml";
    decorationConfigFileName="decoration.xml";
    bulletConfigFileName="bullet.xml";

    format.setSamples(16);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
}








