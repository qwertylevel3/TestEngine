#include "t3engine.h"

T3Engine::T3Engine()
{

}

T3Engine::~T3Engine()
{
}

void T3Engine::init()
{
    format.setSamples(16);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);


    renderModule=new RenderModule();
    renderModule->setFormat(format);
    renderModule->resize(640, 480);
}

void T3Engine::run()
{
    renderModule->show();
}

