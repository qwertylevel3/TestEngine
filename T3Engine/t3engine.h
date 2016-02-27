#ifndef T3ENGINE_H
#define T3ENGINE_H

#include"singleton.h"
#include"scene.h"
#include"inputmodule.h"

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
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
private:
    QBasicTimer timer;

    QMatrix4x4 projection;


    int m_frame;

    Scene* scene;

    //Frame* frame;

};

#endif // T3ENGINE_H
