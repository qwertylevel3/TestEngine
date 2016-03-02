#include"scene.h"
#include"gameconfigurator.h"
#include"terrainmanager.h"
#include"charactermanager.h"
#include"decorationmanager.h"
#include"inputmodule.h"
#include"bulletmanager.h"

Scene::Scene()
{
    width=GameConfigurator::instance()->getWindowWidth();
    height=GameConfigurator::instance()->getWindowHeight();
    for(int i=0;
        i<=GameConfigurator::instance()->getPaintFar();i++)
    {

        QList<Entity*>* box =new QList<Entity*>;
        layerBox.append(*box);
    }
}

Scene::~Scene()
{
}

void Scene::draw()
{
    for(int i=GameConfigurator::instance()->getPaintFar();
        i>=GameConfigurator::instance()->getPaintNear();i--)
    {
        for(int j=0;j<layerBox[i].size();j++)
        {
            if(layerBox[i][j]->getState()==Entity::ALIVE)
                layerBox[i][j]->draw();
        }
    }
}

void Scene::drawBackground()
{
}

void Scene::update()
{
    player->update();
    for(int i=0;i<bulletBox.size();i++)
    {
        bulletBox[i]->update();
    }
    for(int i=0;i<characterBox.size();i++)
    {
        characterBox[i]->update();
    }
    for(int i=0;i<terrainBox.size();i++)
    {
        terrainBox[i]->update();
    }
    for(int i=0;i<decorationBox.size();i++)
    {
        decorationBox[i]->update();
    }
    collision();
}

void Scene::collision()
{
    for(int i=0;i<bulletBox.size();i++)
    {
        if(isCollision(player,bulletBox[i]))
        {
            //TODO
        }
    }
    for(int i=0;i<characterBox.size();i++)
    {
        for(int j=0;j<bulletBox.size();j++)
        {
            if(isCollision(characterBox[i],bulletBox[j]))
            {
                //qDebug()<<"collision"<<endl;
            }
            else
            {
                //qDebug()<<"...."<<endl;
            }
        }
    }
}

bool Scene::isCollision(Entity* a,Entity* b)
{
    QList<QRectF> aRectList=a->getCurrentRects();
    QList<QRectF> bRectList=b->getCurrentRects();

    for(int i=0;i<aRectList.size();i++)
    {
        for(int j=0;j<bRectList.size();j++)
        {
            QRectF aRect=a->getCurrentRects()[i];

            float aRectx=aRect.x()+a->getX()*GameConfigurator::instance()->getScale();
            float aRecty=aRect.y()+a->getY()*GameConfigurator::instance()->getScale();
            float aRectwidth=aRect.width();
            float aRectheight=aRect.height();

            //aRect里保存的是矩形的中点和宽高，不是左上角点
            aRect.setX(aRectx);
            aRect.setY(aRecty);
            aRect.setWidth(aRectwidth*2*a->getZoomX());
            aRect.setHeight(aRectheight*2*a->getZoomY());

            QRectF bRect=b->getCurrentRects()[j];

            float bRectx=bRect.x()+b->getX()*GameConfigurator::instance()->getScale();
            //qDebug()<<bRectx<<endl;
            //qDebug()<<GameConfigurator::instance()->getScale()<<endl;
            //qDebug()<<bRectx<<endl;
            float bRecty=bRect.y()+b->getY()*GameConfigurator::instance()->getScale();
            float bRectwidth=bRect.width();
            float bRectheight=bRect.height();

            bRect.setX(bRectx);
            bRect.setY(bRecty);
            bRect.setWidth(bRectwidth*2*b->getZoomX());
            bRect.setHeight(bRectheight*2*b->getZoomY());
//            bRect.setX(bRectx);
//            bRect.setY(bRecty);
//            bRect.setWidth(bRectwidth);
//            bRect.setHeight(bRectheight);


            //发现接触
            if(isCollision(aRect,bRect))
            {
                return true;
            }
        }
    }
    return false;
}

//碰撞检测，a,b的xy坐标意义为中点
bool Scene::isCollision(QRectF a, QRectF b)
{
    float dx=a.x()-b.x();
    dx=dx<0?-dx:dx;

    float dy=a.y()-b.y();
    dy=dy<0?-dy:dy;


    if((dx<=a.width()/2+b.width()/2) &&
            (dy<=a.height()/2+b.height()/2))
    {
        return true;
    }

    return false;
}

bool Scene::addEntityToLayerBox(Entity *entity)
{
    entity->setScene(this);
    int z=-entity->getZ();
    if(z>GameConfigurator::instance()->getPaintFar() ||
            z<GameConfigurator::instance()->getPaintNear())
    {
        return false;
    }
    layerBox[-(entity->getZ())].append(entity);
    return true;
}
Character *Scene::getPlayer() const
{
    return player;
}

void Scene::setPlayer(Character *value)
{
    player = value;
    addEntityToLayerBox(player);
}

int Scene::getHeight() const
{
    return height;
}

void Scene::setHeight(int value)
{
    height = value;
}

int Scene::getWidth() const
{
    return width;
}

void Scene::setWidth(int value)
{
    width = value;
}


void Scene::addCharacterToBox(Character *character)
{
    if(addEntityToLayerBox(character))
    {
        characterBox.append(character);
    }
}

void Scene::addTerrainToBox(Terrain *terrain)
{
    if(addEntityToLayerBox(terrain))
    {
        terrainBox.append(terrain);
    }
}

void Scene::addDecorationToBox(Decoration *decoration)
{
    if(addEntityToLayerBox(decoration))
    {
        decorationBox.append(decoration);
    }
}

void Scene::addBulletToBox(Bullet *bullet)
{
    if(addEntityToLayerBox(bullet))
    {
        bulletBox.append(bullet);
    }
}
