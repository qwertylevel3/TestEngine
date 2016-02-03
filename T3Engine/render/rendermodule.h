#ifndef RENDERMODULE_H
#define RENDERMODULE_H


#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>
#include<QOpenGLBuffer>
#include<QOpenGLWidget>
#include<QTimer>
#include<QMatrix4x4>
#include<QOpenGLTexture>
#include"T3Engine/render/picture.h"
#include"T3Engine/manager/shadermanager.h"
#include"T3Engine/singleton.h"
#include"T3Engine/sprite/frame.h"
#include"T3Engine/sprite/action.h"
#include"T3Engine/sprite/sprite.h"
#include"T3Engine/manager/spritemanager.h"
#include"T3Engine/scene/scene.h"

QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

class RenderModule:public QOpenGLWidget, protected QOpenGLFunctions,public Singleton<RenderModule>
{
    Q_OBJECT
public:
    explicit RenderModule(QWidget *parent = 0);
    ~RenderModule();

    void init();
protected:
    void timerEvent(QTimerEvent *e) Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void initializeGL() Q_DECL_OVERRIDE;
    void gameLoop();
private:
    QBasicTimer timer;
    bool m_update_pending;
    bool m_animating;

    QMatrix4x4 projection;

    QOpenGLContext *m_context;

    GLuint m_posAttr;
    GLuint m_colAttr;
    GLuint m_matrixUniform;
    int xRot;
    int yRot;
    int zRot;

    int m_frame;


    //temp...
    Action* action2;
    Action* action3;

    Sprite* testSprite;


    Scene* scene;
    //Frame* frame;
};

#endif // RENDERMODULE_H


