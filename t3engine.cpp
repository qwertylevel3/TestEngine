#include "t3engine.h"
#include"T3Engine/manager/picturemanager.h"
#include"T3Engine/render/rendermodule.h"

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

    RenderModule::instance()->setFormat(format);
    RenderModule::instance()->resize(640, 480);
}

void T3Engine::run()
{
    RenderModule::instance()->show();
}

