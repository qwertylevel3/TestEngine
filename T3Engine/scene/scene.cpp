#include"scene.h"
#include"T3Engine/gameconfigurator.h"

Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::init()
{
    Character* testCharacter_0=new Character("test");
    characterBox.append(testCharacter_0);

    testCharacter_0->setZ(-5);
    testCharacter_0->setX(1);
    testCharacter_0->setZoomX(0.7);

    Character* testCharacter_1=new Character("test");
    characterBox.append(testCharacter_1);

    testCharacter_1->setZ(-5);
    testCharacter_1->setX(2);
    testCharacter_1->setZoomX(0.7);
}

void Scene::draw()
{
    for(int i=0;i<characterBox.size();i++)
    {
        characterBox[i]->draw();
    }
}

void Scene::drawRect()
{
    for(int i=0;i<characterBox.size();i++)
    {
        characterBox[i]->drawRect();
    }
}

void Scene::update()
{
    for(int i=0;i<characterBox.size();i++)
    {
        characterBox[i]->update();
    }
    characterBox[1]->setX(characterBox[1]->getX()-0.001);
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
        for(int j=0;j<characterBox.size();j++)
        {
            if(i!=j)
            {
                if(isCollision(characterBox[i],characterBox[j]))
                {
                    qDebug()<<"collision!"<<endl;
                }
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

            float aRectx=aRect.x()+a->getX();
            aRectx*=GameConfigurator::instance()->getScale();
            float aRecty=aRect.y()+a->getY();
            aRecty*=GameConfigurator::instance()->getScale();
            float aRectwidth=aRect.width();
            float aRectheight=aRect.height();

            aRect.setX(aRectx-aRectwidth);
            aRect.setY(aRecty-aRectheight);
            aRect.setWidth(aRectwidth*2);
            aRect.setHeight(aRectheight*2);

            QRectF bRect=b->getCurrentRects()[j];

            float bRectx=bRect.x()+b->getX();
            bRectx*=GameConfigurator::instance()->getScale();
            float bRecty=bRect.y()+b->getY();
            bRecty*=GameConfigurator::instance()->getScale();
            float bRectwidth=bRect.width();
            float bRectheight=bRect.height();

            bRect.setX(bRectx-bRectwidth);
            bRect.setY(bRecty-bRectheight);
            bRect.setWidth(bRectwidth*2);
            bRect.setHeight(bRectheight*2);


            //发现接触
            if(isCollision(aRect,bRect))
            {
                return true;
            }
        }
    }
    return false;
}

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
