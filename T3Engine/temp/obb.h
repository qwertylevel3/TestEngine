#ifndef OBB_H
#define OBB_H

#include<QPointF>
#include<QVector2D>

struct Axes
{
    QVector2D horAxis;
    QVector2D verAxis;
};

class OBB
{
public:
    OBB();
    OBB(QPointF centerP,float wid,float hei,float rot);

    QPointF getCenterPoint() const;
    void setCenterPoint(const QPointF &value);

    float getWidth() const;
    void setWidth(float value);

    float getHeight() const;
    void setHeight(float value);

    float getRotation() const;
    void setRotation(float value);

    float getProjectionRadius(QVector2D axis);
    Axes getAxes() const;
    void setAxes(const Axes &value);

protected:
    float angle2radian(float angle);
    QPointF centerPoint;
    float width;
    float height;
    float rotation;
    float extents[2];
    Axes axes;
};

#endif // OBB_H
