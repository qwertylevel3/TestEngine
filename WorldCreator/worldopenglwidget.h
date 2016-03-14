#ifndef WORLDOPENGLWIDGET_H
#define WORLDOPENGLWIDGET_H

#include"t3engine.h"

class WorldOpenglWidget:public T3Engine
{
public:
    WorldOpenglWidget(QWidget* parent=0);
protected:
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    QPoint winCoodtoOpenglCood(const QPoint& winP);
    QPoint openglCoodtoWinCood(const QPoint& openglP);

    //debug
    void displayMousePos(QMouseEvent* e);
    void displayChooseEntityPos();

    Entity* selectEntity(const QPoint& p);

    Entity* chooseEntity;
    QPoint dragStartPos;
};

#endif // WORLDOPENGLWIDGET_H
