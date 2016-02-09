#include"scene.h"
#include"T3Engine/gameconfigurator.h"
#include"T3Engine/manager/terrainmanager.h"
#include"T3Engine/manager/charactermanager.h"
#include"T3Engine/manager/decorationmanager.h"
Scene::Scene()
{

}

Scene::~Scene()
{

}

void Scene::init()
{
    for(int i=0;
        i<=GameConfigurator::instance()->getPaintFar();i++)
    {

        QList<Entity*>* box =new QList<Entity*>;
        layerBox.append(*box);
    }

    for(int i=0;i<15;i++)
    {
        for(int j=0;j<15;j++)
        {
            Terrain* grass=TerrainManager::instance()->getTerrain("grass");
            grass->setX(-3.2+i*0.48);
            grass->setY(-3.2+j*0.48);
            grass->setZ(-10);

            addTerrainToBox(grass);
        }
    }

    Decoration* tree=DecorationManager::instance()->getDecoration("tree1");
    tree->setZ(-4);
    addDecorationToBox(tree);



    Character* testCharacter_0=CharacterManager::instance()->getCharacter("test");
    testCharacter_0->setZ(-5);
    testCharacter_0->setX(1);
    addCharacterToBox(testCharacter_0);


//    Decoration* shadow=DecorationManager::instance()->getDecoration("shadow");
//    shadow->setZ(-6);
//    shadow->setX(1);
//    shadow->setY(-0.18);
//    decorationBox.append(shadow);
//
//
//    Decoration* shadow_0=DecorationManager::instance()->getDecoration("shadow");
//    testCharacter_0->addChild(shadow_0);
//    shadow_0->setY(-0.18);
//    shadow_0->setLocalZ(-1);

    Character* testCharacter_1=CharacterManager::instance()->getCharacter("test");
    testCharacter_1->setZ(-5);
    testCharacter_1->setX(2);
    addCharacterToBox(testCharacter_1);


//    Decoration* shadow_1=DecorationManager::instance()->getDecoration("shadow");
//    testCharacter_1->addChild(shadow_1);
//    shadow_1->setLocalY(-0.18);
//    shadow_1->setLocalZ(-1);
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
    if(GameConfigurator::instance()->getDrawRect())
    {
        drawRect();
    }
}

void Scene::drawRect()
{
    //TODO
}

void Scene::update()
{
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
    characterBox[1]->setX(characterBox[1]->getX()-0.01);
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

void Scene::addEntityToLayerBox(Entity *entity)
{
    layerBox[-(entity->getZ())].append(entity);
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
