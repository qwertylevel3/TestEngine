#include"scene.h"
#include"T3Engine/gameconfigurator.h"
#include"T3Engine/manager/terrainmanager.h"
#include"T3Engine/manager/charactermanager.h"
#include"T3Engine/manager/decorationmanager.h"
#include"T3Engine/inputmodule.h"
#include"T3Engine/manager/bulletmanager.h"

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
            layerBox[i][j]->draw();
        }
    }
}

void Scene::drawBackground()
{
}

void Scene::update()
{
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
    //characterBox[1]->setX(characterBox[1]->getX()-0.01);
    //bulletBox[0]->setX(bulletBox[0]->getX()+0.001);
    collision();
}

void Scene::load(const QString &filename)
{

}

void Scene::unload()
{

}

void Scene::collision()
{
    for(int i=0;i<characterBox.size();i++)
    {
        for(int j=0;j<bulletBox.size();j++)
        {
//            if(i!=j)
//            {
//                if(isCollision(characterBox[i],characterBox[j]))
//                {
//                    qDebug()<<"collision!"<<endl;
//
//                }
//                else
//                {
//                    qDebug()<<"....."<<endl;
//                }
//            }
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

void Scene::addEntityToLayerBox(Entity *entity)
{
    entity->setScene(this);
    layerBox[-(entity->getZ())].append(entity);
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
    characterBox.append(character);
    addEntityToLayerBox(character);
}

void Scene::addTerrainToBox(Terrain *terrain)
{
    terrainBox.append(terrain);
    addEntityToLayerBox(terrain);
}

void Scene::addDecorationToBox(Decoration *decoration)
{
    decorationBox.append(decoration);
    addEntityToLayerBox(decoration);
}

void Scene::addBulletToBox(Bullet *bullet)
{
    bulletBox.append(bullet);
    addEntityToLayerBox(bullet);
}
