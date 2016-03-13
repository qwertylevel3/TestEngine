#include"scene.h"
#include"gameconfigurator.h"
#include"terrainmanager.h"
#include"charactermanager.h"
#include"decorationmanager.h"
#include"inputmodule.h"
#include"bulletmanager.h"
#include"obb.h"

Scene::Scene()
{
    pause=false;
    for(int i=0;
        i<=GameConfigurator::instance()->getPaintFar();i++)
    {

        QList<Entity*>* box =new QList<Entity*>;
        layerBox.append(*box);
    }

//    for(int i=0;i<1;i++)
//    {
//        for(int j=0;j<1;j++)
//        {
//            Character* tempC=CharacterManager::instance()->getCharacter("test");
//            tempC->setX(-250+i*30);
//            tempC->setY(-250+j*30);
//            tempC->setZ(-10);
//            this->addCharacterToBox(tempC);
//
//        }
//    }

}

Scene::~Scene()
{
    characterList.clear();
    terrainList.clear();
    decorationList.clear();
    bulletList.clear();
    dialogList.clear();

    for(int i=0;i<layerBox.size();i++)
    {
        for(int j=0;j<layerBox[i].size();j++)
        {
            delete layerBox[i][j];
        }
        layerBox[i].clear();
    }
}

void Scene::draw()
{
    for(int i=GameConfigurator::instance()->getPaintFar();
        i>=GameConfigurator::instance()->getPaintNear();i--)
    {
        if(i==10)
        {
            qSort(layerBox[i].begin(),layerBox[i].end(),Entity::compareY);
        }

        for(int j=0;j<layerBox[i].size();j++)
        {
            if(layerBox[i][j]->isAlive())
                layerBox[i][j]->draw();
        }
    }
}

void Scene::drawBackground()
{
}

void Scene::update()
{
    for(int i=0;i<triggerList.size();i++)
    {
        if(triggerList[i]->judge())
        {
            triggerList[i]->run();
            delete triggerList[i];
            triggerList.removeAt(i);
        }
    }
    collision();
    if(!pause)
    {
        if(player->isAlive())
        {
            player->update();
        }
        for(int i=0;i<bulletList.size();i++)
        {
            if(bulletList[i]->isAlive())
            {
                bulletList[i]->update();
            }
        }
        for(int i=0;i<characterList.size();i++)
        {
            if(characterList[i]->isAlive())
            {
                characterList[i]->update();
            }
        }
        for(int i=0;i<terrainList.size();i++)
        {
            if(terrainList[i]->isAlive())
            {
                terrainList[i]->update();
            }
        }
        for(int i=0;i<decorationList.size();i++)
        {
            if(decorationList[i]->isAlive())
            {
                decorationList[i]->update();
            }
        }
    }
    for(int i=0;i<dialogList.size();i++)
    {
        if(dialogList[i]->isAlive())
        {
            dialogList[i]->update();
        }
    }

//    qDebug()<<characterList.size()<<endl;
}

void Scene::collision()
{
    detectPlayerBulletCollision();
    detectCharacterBulletCollision();
    detectPlayerCharacterCollision();
    detectPlayerDecorationCollision();
}

void Scene::detectPlayerBulletCollision()
{
    for(int i=0;i<bulletList.size();i++)
    {
        if(player->isAlive() && bulletList[i]->isAlive())
        {
            if(isCollision(player,bulletList[i]))
            {
                //TODO
            }
        }

    }
}

void Scene::detectCharacterBulletCollision()
{
    for(int i=0;i<characterList.size();i++)
    {
        for(int j=0;j<bulletList.size();j++)
        {
            if(characterList[i]->isAlive() && bulletList[j]->isAlive())
            {
                if(isCollision(characterList[i],bulletList[j]))
                {
                    //qDebug()<<"collision"<<endl;
                    if(characterList[i]->getType()==Character::ENEMY
                            &&( bulletList[j]->getShooter()->getType()==Character::PLAYER
                            || bulletList[j]->getShooter()->getType()==Character::FRIEND))
                    {
                        characterList[i]->getDamage(bulletList[i]->getDamage());
                        bulletList[j]->boom();
                    }
                    else if((characterList[i]->getType()==Character::PLAYER
                            || characterList[i]->getType()==Character::FRIEND)
                            && bulletList[j]->getShooter()->getType()==Character::ENEMY)
                    {
                        characterList[i]->getDamage(bulletList[i]->getDamage());
                        bulletList[j]->boom();
                    }
                }
                else
                {
                    //qDebug()<<"...."<<endl;
                }
            }

        }
    }
}

void Scene::detectPlayerCharacterCollision()
{
    for(int i=0;i<characterList.size();i++)
    {
        if(player->isAlive() && characterList[i]->isAlive())
        {
            if(isCollision(player,characterList[i]))
            {
                //qDebug()<<"collision"<<endl;
            }
            else
            {
                //qDebug()<<"....."<<endl;
            }
        }
    }
}

void Scene::detectCharacterDecorationCollision()
{

}

void Scene::detectPlayerDecorationCollision()
{
    for(int i=0;i<decorationList.size();i++)
    {
        if(player->isAlive() && decorationList[i]->isAlive())
        {
            if(isCollision(player,decorationList[i]))
            {
                //TODO
                //qDebug()<<"collision"<<endl;
                //player->setMoveAble(false);
                player->setDx(-player->getDx());
                if(isCollision(player,decorationList[i]))
                {
                    player->setDx(-player->getDx());
                    player->setDy(-player->getDy());
                    if(isCollision(player,decorationList[i]))
                    {
                        player->setDx(-player->getDx());
                    }
                }
            }
            else
            {
                //qDebug()<<"..."<<endl;
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

            float aRectx=aRect.x()+(a->getX()+a->getDx())*GameConfigurator::instance()->getScale();
            float aRecty=aRect.y()+(a->getY()+a->getDy())*GameConfigurator::instance()->getScale();
            float aRectwidth=aRect.width();
            float aRectheight=aRect.height();


            //aRect里保存的是矩形的中点和宽高，不是左上角点
            aRect.setX(aRectx);
            aRect.setY(aRecty);
            aRect.setWidth(aRectwidth*2*a->getZoomX());
            aRect.setHeight(aRectheight*2*a->getZoomY());

            QRectF bRect=b->getCurrentRects()[j];

            float bRectx=bRect.x()+b->getX()*GameConfigurator::instance()->getScale()+b->getDx();
            //qDebug()<<bRectx<<endl;
            //qDebug()<<GameConfigurator::instance()->getScale()<<endl;
            //qDebug()<<bRectx<<endl;
            float bRecty=bRect.y()+b->getY()*GameConfigurator::instance()->getScale()+b->getDy();
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

            OBB obb1(QPointF(aRect.x(),aRect.y()),aRect.width(),aRect.height(),a->getRotateAngle());
            OBB obb2(QPointF(bRect.x(),bRect.y()),bRect.width(),bRect.height(),b->getRotateAngle());

            //发现接触
            if(detector.isCollision(obb1,obb2))
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
bool Scene::getPause() const
{
    return pause;
}

void Scene::setPause(bool value)
{
    pause = value;
}
QString Scene::getName() const
{
    return name;
}

void Scene::setName(const QString &value)
{
    name = value;
}


QList<Character *> & Scene::getCharacterBox()
{
    return characterList;
}

void Scene::switchFocusToPlayer()
{
    InputModule::instance()->setEntity(player);
}

void Scene::switchFocusToDialog(Dialog *dialog)
{
    InputModule::instance()->setEntity(dialog);
}

void Scene::addDialogToScene(Dialog *dialog)
{
    if(addEntityToLayerBox(dialog))
    {
        dialogList.push_back(dialog);
    }
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
        characterList.append(character);
    }
}

void Scene::addTerrainToBox(Terrain *terrain)
{
    if(addEntityToLayerBox(terrain))
    {
        terrainList.append(terrain);
    }
}

void Scene::addDecorationToBox(Decoration *decoration)
{
    if(addEntityToLayerBox(decoration))
    {
        decorationList.append(decoration);
    }
}

void Scene::addBulletToBox(Bullet *bullet)
{
    if(addEntityToLayerBox(bullet))
    {
        bulletList.append(bullet);
    }
}

void Scene::addTrigger(Trigger *trigger)
{
    triggerList.append(trigger);
}
