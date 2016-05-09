#include "collisiondetector.h"
#include<math.h>

CollisionDetector::CollisionDetector()
{

}

float CollisionDetector::Pi=3.1415926;

float CollisionDetector::radian2angle(float radian)
{
    return radian*180/Pi;
}

float CollisionDetector::angle2radian(float angle)
{
    return Pi*angle/180;
}

QVector2D CollisionDetector::rotate(QVector2D p, float angle)
{
    QMatrix4x4 matrix;
    matrix.setToIdentity();
    matrix.rotate(angle,0,0,1);

    return (QVector4D(p,0,1)*matrix).toVector2D();
}


bool CollisionDetector::isCollision(OBB obb1, OBB obb2)
{
    QVector2D nv;
    nv.setX(obb1.getCenterPoint().x()-obb2.getCenterPoint().x());
    nv.setY(obb1.getCenterPoint().y()-obb2.getCenterPoint().y());

    QVector2D axisA1=obb1.getAxes().horAxis;
    if(obb1.getProjectionRadius(axisA1)+obb2.getProjectionRadius(axisA1)
            <= fabs(QVector2D::dotProduct(nv,axisA1)))
    {
        return false;
    }

    QVector2D axisA2=obb1.getAxes().verAxis;
    if(obb1.getProjectionRadius(axisA2)+obb2.getProjectionRadius(axisA2)
            <= fabs(QVector2D::dotProduct(nv,axisA2)))
    {
        return false;
    }
    QVector2D axisB1=obb2.getAxes().horAxis;
    if(obb1.getProjectionRadius(axisB1)+obb2.getProjectionRadius(axisB1)
            <=fabs(QVector2D::dotProduct(nv,axisB1)))
    {
        return false;
    }
    QVector2D axisB2=obb2.getAxes().verAxis;
    if(obb1.getProjectionRadius(axisB2)+obb2.getProjectionRadius(axisB2)
            <= fabs(QVector2D::dotProduct(nv,axisB2)))
    {
        return false;
    }
    return true;
}

bool CollisionDetector::isCollision(Entity *a, Entity *b)
{
    if(!a->isCollisionAble() || !b->isCollisionAble())
    {
        return false;
    }

    float scale=GameConfigurator::instance()->getScale();

    QList<QRectF> aRectList=a->getCurrentRects();
    QList<QRectF> bRectList=b->getCurrentRects();

    for(int i=0;i<aRectList.size();i++)
    {
        for(int j=0;j<bRectList.size();j++)
        {
            QRectF aRect=a->getCurrentRects()[i];

            float aRectx=aRect.x()+(a->getX()+a->getDx())*scale;
            float aRecty=aRect.y()+(a->getY()+a->getDy())*scale;
            float aRectwidth=aRect.width()*a->getZoomX();
            float aRectheight=aRect.height()*a->getZoomY();

            aRect.setX(aRectx);
            aRect.setY(aRecty);
            aRect.setWidth(aRectwidth);
            aRect.setHeight(aRectheight);


            QRectF bRect=b->getCurrentRects()[j];

            float bRectx=bRect.x()+(b->getX()+b->getDx())*scale;
            float bRecty=bRect.y()+(b->getY()+b->getDy())*scale;
            float bRectwidth=bRect.width()*b->getZoomX();
            float bRectheight=bRect.height()*b->getZoomY();


            bRect.setX(bRectx);
            bRect.setY(bRecty);
            bRect.setWidth(bRectwidth);
            bRect.setHeight(bRectheight);


            OBB obb1(QPointF(aRect.x(),aRect.y()),aRect.width(),aRect.height(),-a->getRotateAngle());
            OBB obb2(QPointF(bRect.x(),bRect.y()),bRect.width(),bRect.height(),-b->getRotateAngle());

            //发现接触
            if(isCollision(obb1,obb2))
            {
                return true;
            }
        }
    }
    return false;
}

bool CollisionDetector::isCollision(QRectF a, QRectF b)
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

bool CollisionDetector::inField(QVector2D field, float fx, float fy, float x, float y)
{
    float dx=fx-x;
    dx=dx<0?-dx:dx;

    float dy=fy-y;
    dy=dy<0?-dy:dy;

    if(dx<=field.x()/2 &&
            dy<=field.y()/2)
    {
        return true;
    }

    return false;
}

