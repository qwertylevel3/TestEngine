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

