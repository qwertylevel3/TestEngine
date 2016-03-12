#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include<QVector2D>
#include<QMatrix4x4>
#include"obb.h"


class CollisionDetector
{
public:
    static float Pi;
    CollisionDetector();
    float radian2angle(float radian);
    float angle2radian(float angle);
    QVector2D rotate(QVector2D p,float angle);

    bool isCollision(OBB obb1,OBB obb2);
};


#endif // COLLISIONDETECTOR_H
