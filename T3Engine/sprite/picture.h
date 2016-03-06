#ifndef PICTURE_H
#define PICTURE_H

#include<stable.h>
#include"picturetext.h"

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};


class Picture : protected QOpenGLFunctions
{
public:
    Picture(const QString& imagePath);
    virtual ~Picture();

    void draw();
    void loadImage(const QString& imagePath);

    QString getName(){return name;}
    QMatrix4x4& getMatrix(){return matrix;}


    void setCoordinate(float x,float y,float z=0);
    void setWidth(float w){width=w;}
    void setHeight(float h){height=h;}
    void setTexturePosition(float t_x,float t_y,float t_w,float t_h);
    void setZoomX(float z)
    {
        zoomX=z;
    }
    void setZoomY(float z)
    {
        zoomY=z;
    }
    void setMatrix(const QMatrix4x4& m)
    {
        matrix=m;
    }
    void setTextures(QImage img);
    void setText(const QString& content);
    void setMirror(bool m)
    {
        mir=m;
    }
    void rotate(float angle,float a_x,float a_y,float a_z=0);

    float getWidth(){return width;}
    float getHeight(){return height;}
    float getX(){return x;}
    float getY(){return y;}
    float getZ(){return z;}
    float getZoomX(){return zoomX;}
    float getZoomY(){return zoomY;}
    float getImageHeight(){return image.height();}
    float getImageWidth(){return image.width();}
    bool getMirror(){return mir;}
    int getRepeatX() const
    {
        return repeatX;
    }
    void setRepeatX(int value)
    {
        repeatX = value;
    }

    int getRepeatY() const
    {
        return repeatY;
    }
    void setRepeatY(int value)
    {
        repeatY = value;
    }

    float getAlpha() const;
    void setAlpha(float value);

    float getAngle() const;
    void setAngle(float value);

    float getAx() const;
    void setAx(float value);

    float getAy() const;
    void setAy(float value);

    float getAz() const;
    void setAz(float value);

private:
    void initFaceGeometry();
    void allocateBuffer();
    void updateArrayBuffer();
    void initParameter();
    void updateVertexData();
    void updateVertexDataMir();

    //名字由路径名自动分配
    void setName(const QString& imagePath);

    VertexData vertices[4];
    GLushort indices[5];

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QOpenGLTexture* texture;
    QImage image;
    QMatrix4x4 matrix;

    QString name;
    PictureText text;


    float zoomX;//放缩
    float zoomY;
    float x,y,z;//位置坐标
    float width;//宽高，单位为像素
    float height;
    float tx,ty;//纹理坐标
    float tw,th;//纹理宽高
    bool mir;//镜像
    float angle;//旋转角度
    float ax,ay,az;//旋转轴
    int repeatX;//重复次数(重复一次，绘制两次)
    int repeatY;
    float alpha;
};


#endif // PICTURE_H
