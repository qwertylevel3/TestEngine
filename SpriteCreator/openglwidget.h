#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include"stable.h"
#include"sprite.h"

class OpenglWidget:public QOpenGLWidget,public QOpenGLFunctions
{
public:
    OpenglWidget(QWidget* parent=0);
    ~OpenglWidget();
protected:
    void timerEvent(QTimerEvent* e)Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void initializeGL() Q_DECL_OVERRIDE;


    QMatrix4x4 projection;


    Sprite* sprite;
    QBasicTimer timer;
};

#endif // OPENGLWIDGET_H
