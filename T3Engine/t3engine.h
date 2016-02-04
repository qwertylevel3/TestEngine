#ifndef T3ENGINE_H
#define T3ENGINE_H

#include<QtGui/QWindow>
#include<QtGui/QOpenGLFunctions>
#include<QOpenGLBuffer>
#include<QOpenGLWidget>
#include<QTimer>
#include"T3Engine/singleton.h"
#include"T3Engine/scene/scene.h"
#include<QOpenGLContext>

class T3Engine:public QOpenGLWidget,public QOpenGLFunctions,public Singleton<T3Engine>
{
public:
    T3Engine(QWidget* parent = 0);
    ~T3Engine();

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

    Scene* scene;

    //Frame* frame;
};

#endif // T3ENGINE_H
