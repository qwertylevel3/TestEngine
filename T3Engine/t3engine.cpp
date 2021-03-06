#include "t3engine.h"

#include"stable.h"
#include"shadermanager.h"
#include"picturemanager.h"
#include"gameconfigurator.h"
#include"spritemanager.h"
#include"charactermanager.h"
#include"decorationmanager.h"
#include"bulletmanager.h"
#include"clockmanager.h"
#include"facemanager.h"
#include"dialogmanager.h"
#include"backgroundmanager.h"
#include"aimanager.h"


T3Engine::T3Engine(QWidget *parent)
    : QOpenGLWidget(parent)
{
    this->setFormat(GameConfigurator::instance()->getQSurfaceFormat());

    this->setFixedSize(GameConfigurator::instance()->getWindowWidth(),
                       GameConfigurator::instance()->getWindowHeight());
    debug=false;
}

T3Engine::~T3Engine()
{
    World::instance()->destory();

    DialogManager::instance()->destroy();
    BackgroundManager::instance()->destroy();
    FaceManager::instance()->destroy();
    BulletManager::instance()->destory();
    DecorationManager::instance()->destroy();
    CharacterManager::instance()->destroy();
    AIManager::instance()->destory();
    ClockManager::instance()->destroy();
    SpriteManager::instance()->destroy();
    PictureManager::instance()->destroy();
    ShaderManager::instance()->destory();
}

void T3Engine::init()
{
    ShaderManager::instance()->init();
    PictureManager::instance()->init();
    SpriteManager::instance()->init();
    ClockManager::instance()->init();
    AIManager::instance()->init();
    CharacterManager::instance()->init();
    DecorationManager::instance()->init();
    BulletManager::instance()->init();
    FaceManager::instance()->init();
    BackgroundManager::instance()->init();
    DialogManager::instance()->init();

    World::instance()->init();

    //随机数种子
    QTime time;
    time= QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
}


void T3Engine::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e)
    if(!debug)
    {
        gameLoop();
    }
    update();
}


void T3Engine::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(1,1,1,0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_POLYGON_OFFSET_LINE);
    glEnable(GL_POLYGON_OFFSET_POINT);
    glPolygonOffset(0.1,1);

    //initialize...
    //PictureManager::instance()->showPictureBoxMessage();

    init();

    timer.start(12,this);
    m_frame=0;

}

void T3Engine::gameLoop()
{
    m_frame++;

    World::instance()->update();

    ClockManager::instance()->update();
}

void T3Engine::keyPressEvent(QKeyEvent *e)
{
    QOpenGLWidget::keyPressEvent(e);
    InputModule::instance()->keyPressEvent(e);
}

void T3Engine::keyReleaseEvent(QKeyEvent *e)
{
    QOpenGLWidget::keyReleaseEvent(e);
    InputModule::instance()->keyReleaseEvent(e);
}
bool T3Engine::getDebug() const
{
    return debug;
}

void T3Engine::setDebug(bool value)
{
    debug = value;
}


void T3Engine::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ShaderManager::instance()->getProgram()
            ->setUniformValue("mvp_matrix",projection);

    ShaderManager::instance()->getProgram()->setUniformValue("texture", 0);
    World::instance()->draw();
}

void T3Engine::resizeGL(int w, int h)
{
    Q_UNUSED(w)
    Q_UNUSED(h)
    // Calculate aspect ratio
    //qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    //const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    //projection.perspective(fov, aspect, zNear, zFar);
   // projection.ortho(-2.5,2.5,-2,2,0,
   //                  GameConfigurator::instance()->getPaintFar());
   // projection.ortho(-GameConfigurator::instance()->getWindowWidth()/2,
   //                  GameConfigurator::instance()->getWindowWidth()/2,
   //                  -GameConfigurator::instance()->getWindowHeight()/2,
   //                  GameConfigurator::instance()->getWindowHeight()/2,
   //                  0,
   //                  GameConfigurator::instance()->getPaintFar());
    projection.ortho(-this->width()/2,
                     this->width()/2,
                     -this->height()/2,
                     this->height()/2,
                     0,GameConfigurator::instance()->getPaintFar());

}

