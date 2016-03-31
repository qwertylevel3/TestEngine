#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include<QVector2D>
#include<QMatrix4x4>
#include"obb.h"
#include"entity.h"
#include"character.h"
#include"bullet.h"
#include"decoration.h"


class CollisionDetector
{
public:
    static float Pi;
    CollisionDetector();
    static float radian2angle(float radian);
    static float angle2radian(float angle);
    static QVector2D rotate(QVector2D p,float angle);

    static bool isCollision(OBB obb1,OBB obb2);

    static void collision();
    static bool isCollision(Entity *a, Entity *b);
    static bool isCollision(QRectF a,QRectF b);
    static bool inField(QVector2D field,float fx,float fy,float x,float y);

};


#endif // COLLISIONDETECTOR_H
