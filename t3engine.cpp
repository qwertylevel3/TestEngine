#include "t3engine.h"
#include"T3Engine/manager/picturemanager.h"
#include"T3Engine/render/rendermodule.h"
#include"T3Engine/gameconfigurator.h"

T3Engine::T3Engine()
{

}

T3Engine::~T3Engine()
{
}

void T3Engine::init()
{
    GameConfigurator::instance()->init();
    RenderModule::instance()->init();
}

void T3Engine::run()
{
    RenderModule::instance()->show();
}

