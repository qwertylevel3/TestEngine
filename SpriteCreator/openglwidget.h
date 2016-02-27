#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include"stable.h"
#include"sprite.h"

class OpenglWidget:public QOpenGLWidget,public QOpenGLFunctions
{
public:
    OpenglWidget(QWidget* parent=0);
    ~OpenglWidget();
public slots:
    void setSprite(Sprite* sp);
protected:
    void timerEvent(QTimerEvent* e)Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int w, int h) Q_DECL_OVERRIDE;
    void initializeGL() Q_DECL_OVERRIDE;

    void initManager();

    QMatrix4x4 projection;

    Sprite* sprite;
    QBasicTimer timer;
};

#endif // OPENGLWIDGET_H
