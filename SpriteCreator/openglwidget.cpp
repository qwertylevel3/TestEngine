#include "openglwidget.h"
#include"gameconfigurator.h"
#include"shadermanager.h"

OpenglWidget::OpenglWidget(QWidget *parent)
    :QOpenGLWidget(parent)
{
    this->setFormat(GameConfigurator::instance()->getQSurfaceFormat());
    sprite=0;
}

OpenglWidget::~OpenglWidget()
{

}

void OpenglWidget::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e)
    update();
}

void OpenglWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ShaderManager::instance()->getProgram()
            ->setUniformValue("mvp_matrix",projection);

    ShaderManager::instance()->getProgram()->setUniformValue("texture", 0);

    if(sprite)
    {
        sprite->draw();
    }

}

void OpenglWidget::resizeGL(int w, int h)
{
    Q_UNUSED(w)
    Q_UNUSED(h)

    projection.setToIdentity();

    projection.ortho(-2,2,-2,2,0,
                     GameConfigurator::instance()->getPaintFar());
}

void OpenglWidget::initializeGL()
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

    ShaderManager::instance()->init();

    timer.start(12,this);

}
