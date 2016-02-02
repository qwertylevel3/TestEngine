#include"rendermodule.h"
#include <QtCore/QCoreApplication>

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include"T3Engine/manager/shadermanager.h"
#include"T3Engine/manager/picturemanager.h"

RenderModule::RenderModule(QWidget *parent)
    : QOpenGLWidget(parent)
    , m_update_pending(false)
    , m_animating(false)
    , m_context(0)
{
    testSprite=NULL;
}

RenderModule::~RenderModule()
{
}

void RenderModule::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e)
    gameLoop();
    update();
}


void RenderModule::initializeGL()
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

    //读取shader
    ShaderManager::instance()->init(":/vshader.glsl",":/fshader.glsl");
    //读取图片资源
    PictureManager::instance()->init();
    SpriteManager::instance()->init();

    //PictureManager::instance()->showPictureBoxMessage();

    timer.start(12,this);
    m_frame=0;

    testSprite=SpriteManager::instance()->getSprite("test");


}

void RenderModule::gameLoop()
{
    m_frame++;

    if(testSprite)
    {
        testSprite->update();
    }

}

void RenderModule::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ShaderManager::instance()->getProgram()
            ->setUniformValue("mvp_matrix",projection);

    ShaderManager::instance()->getProgram()->setUniformValue("texture", 0);

    //actionList.at(0)->draw(0.7,0,-5,1,false);
    //actionList.at(1)->draw(1*0.5,0,-6,1.5,false);

    testSprite->setZ(-5);
    testSprite->setX(1);
    testSprite->setZoomX(0.7);
    testSprite->draw();

    testSprite->drawRect();
}

void RenderModule::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

