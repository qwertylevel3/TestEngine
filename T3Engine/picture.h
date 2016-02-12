#ifndef PICTURE_H
#define PICTURE_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
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
    void setTextures(const QString &imagePath);
    void mirror(bool m)
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
    float getImageHeight(){return imageHeight;}
    float getImageWidth(){return imageWidth;}
    bool isMirror(){return mir;}
    QString getName(){return name;}
    QMatrix4x4& getMatrix(){return matrix;}

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

private:
    void initFaceGeometry();
    void allocateBuffer();
    void updateArrayBuffer();

    //名字由路径名自动分配
    void setName(const QString& imagePath);

    VertexData vertices[4];
    GLushort indices[5];

    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    QOpenGLTexture* texture;
    QImage image;
    float imageHeight;
    float imageWidth;
    float zoomX;//放缩
    float zoomY;
    float x,y,z;//位置坐标
    float width;
    float height;
    float tx,ty;//纹理坐标
    float tw,th;//纹理宽高
    bool mir;//镜像
    float angle;//旋转角度
    float ax,ay,az;//旋转轴
    int repeatX;//重复次数(重复一次，绘制两次)
    int repeatY;
    QMatrix4x4 matrix;
    QString name;
};

inline
void Picture::setCoordinate(float x, float y, float z)
{
    this->x=x;
    this->y=y;
    this->z=z;
}
inline
void Picture::setTexturePosition(float t_x, float t_y, float t_w, float t_h)
{
    this->tx=t_x;
    this->ty=t_y;
    this->tw=t_w;
    this->th=t_h;
}

#endif // PICTURE_H
