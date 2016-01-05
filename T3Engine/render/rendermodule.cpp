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

    glClearColor(0,1,1,1);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //initialize...

    ShaderManager::instance()->init(":/vshader.glsl",":/fshader.glsl");
    PictureManager::instance()->init();

    PictureManager::instance()->showPictureBoxMessage();

    timer.start(12,this);
    m_frame=0;

    QRectF r(0,0,128,128);
    f=new Frame(QString("\\resource\\character\\test.png"),r);
}

void RenderModule::gameLoop()
{
    m_frame++;

    PictureManager::instance()->getPicture("\\resource\\character\\test.png")
            ->getMatrix().setToIdentity();

     PictureManager::instance()->getPicture("\\resource\\character\\test.png")
             ->getMatrix().translate(0.0, 0.0, -5.0);
     PictureManager::instance()->getPicture("\\resource\\character\\test.png")
             ->getMatrix().rotate(0.1*m_frame,1,1,1);
}

void RenderModule::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    ShaderManager::instance()->getProgram()
            ->setUniformValue("mvp_matrix"
            ,projection*(PictureManager::instance()->getPicture("\\resource\\character\\test.png")->getMatrix()));

    ShaderManager::instance()->getProgram()->setUniformValue("texture", 0);

    f->draw(0,0,1,false);
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

