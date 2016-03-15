#include "worldopenglwidget.h"

WorldOpenglWidget::WorldOpenglWidget(QWidget* parent)
    :T3Engine(parent)
{
    this->setDebug(true);
    this->setFixedSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
    chooseEntity=0;
    //setAcceptDrops(true);
}

void WorldOpenglWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::LeftButton)
    {
        if(chooseEntity)
        {
            //displayMousePos(e);
            //displayChooseEntityPos();

            int distance=(winCoodtoOpenglCood(e->pos())-dragStartPos).manhattanLength();
            if(distance >= QApplication::startDragDistance())
            {
                chooseEntity->setX(winCoodtoOpenglCood(e->pos()).x());
                chooseEntity->setY(winCoodtoOpenglCood(e->pos()).y());
            }
        }
    }
    T3Engine::mouseMoveEvent(e);
}

void WorldOpenglWidget::mousePressEvent(QMouseEvent *e)
{
    chooseEntity=selectEntity(e->pos());
    if(chooseEntity)
    {
        dragStartPos.setX(chooseEntity->getX());
        dragStartPos.setY(chooseEntity->getY());
    }
    T3Engine::mousePressEvent(e);
}

void WorldOpenglWidget::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)
    chooseEntity=0;
    T3Engine::mouseReleaseEvent(e);
}

void WorldOpenglWidget::addDecoration(const QString &decorationName)
{
    world->addDecoration(decorationName);
}

void WorldOpenglWidget::addCharacter(const QString &characterName)
{
    world->addCharacter(characterName);
}

QPoint WorldOpenglWidget::winCoodtoOpenglCood(const QPoint &winP)
{
    QPoint p;
    p.setX(winP.x()-this->width()/2);
    p.setY(-winP.y()+this->height()/2);
    return p;
}

QPoint WorldOpenglWidget::openglCoodtoWinCood(const QPoint &openglP)
{
    QPoint p;
    p.setX(openglP.x()+this->width()/2);
    p.setY(-openglP.y()+this->height()/2);
    return p;
}

void WorldOpenglWidget::displayMousePos(QMouseEvent *e)
{
    qDebug()<<"mousePos"<<endl;
    qDebug()<<e->pos().x()<<endl;
    qDebug()<<e->pos().y()<<endl;


}

void WorldOpenglWidget::displayChooseEntityPos()
{
    qDebug()<<"chooseEntity"<<endl;
    qDebug()<<chooseEntity->getX()<<endl;
    qDebug()<<chooseEntity->getY()<<endl;

}

Entity *WorldOpenglWidget::selectEntity(const QPoint &p)
{
    //qDebug()<<winCoodtoOpenglCood(p)<<endl;
    return world->selectEntity(winCoodtoOpenglCood(p));
}
