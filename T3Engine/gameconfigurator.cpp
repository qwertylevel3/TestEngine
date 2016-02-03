#include "gameconfigurator.h"

GameConfigurator::GameConfigurator()
{

}

void GameConfigurator::init()
{
    scale=100;
    windowWidth=640;
    windowHeight=480;

    format.setSamples(16);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
}

