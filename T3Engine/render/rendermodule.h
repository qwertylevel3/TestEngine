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


QT_BEGIN_NAMESPACE
class QPainter;
class QOpenGLContext;
class QOpenGLPaintDevice;
QT_END_NAMESPACE

class RenderModule:public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit RenderModule(QWidget *parent = 0);
    ~RenderModule();
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

    QVector<Picture*> pictureBox;

    int m_frame;
};

#endif // RENDERMODULE_H


