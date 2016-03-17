#include "worldopenglwidget.h"
#include"world.h"

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
    World::instance()->addDecoration(decorationName);
}

void WorldOpenglWidget::addCharacter(const QString &characterName)
{
    World::instance()->addCharacter(characterName);
}

void WorldOpenglWidget::setBackground(const QString &backgroundName)
{
    World::instance()->setBackground(backgroundName);
}

bool WorldOpenglWidget::save(const QString &fileName)
{
    return World::instance()->save(fileName);
}

bool WorldOpenglWidget::open(const QString &path)
{
    return World::instance()->open(path);
}

void WorldOpenglWidget::newWorld(const QString &worldName)
{
    World::instance()->clear();
    World::instance()->init();
    World::instance()->setName(worldName);
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


Entity *WorldOpenglWidget::selectEntity(const QPoint &p)
{
    //qDebug()<<winCoodtoOpenglCood(p)<<endl;
    return World::instance()->selectEntity(winCoodtoOpenglCood(p));
}
