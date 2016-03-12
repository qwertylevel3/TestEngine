#include "obb.h"
#include<math.h>
#include<QDebug>

OBB::OBB()
{

}

OBB::OBB(QPointF centerP, float wid, float hei, float rot)
    :centerPoint(centerP),
      width(wid),
      height(hei)
{
    rotation=angle2radian(rot);
    extents[0]=width/2;
    extents[1]=height/2;
    axes.horAxis=QVector2D(cos(rotation),sin(rotation));
    axes.verAxis=QVector2D(-sin(rotation),cos(rotation));

}

QPointF OBB::getCenterPoint() const
{
    return centerPoint;
}

void OBB::setCenterPoint(const QPointF &value)
{
    centerPoint = value;
}
float OBB::getWidth() const
{
    return width;
}

void OBB::setWidth(float value)
{
    width = value;
}
float OBB::getHeight() const
{
    return height;
}

void OBB::setHeight(float value)
{
    height = value;
}
float OBB::getRotation() const
{
    return rotation;
}

void OBB::setRotation(float value)
{
    rotation = value;
}

float OBB::getProjectionRadius(QVector2D axis)
{
    return this->extents[0]*fabs(QVector2D::dotProduct(axis,axes.horAxis))
            +this->extents[1]*fabs(QVector2D::dotProduct(axis,axes.verAxis));
}
Axes OBB::getAxes() const
{
    return axes;
}

void OBB::setAxes(const Axes &value)
{
    axes = value;
}

float OBB::angle2radian(float angle)
{
    return 3.1415926*angle/180;
}






