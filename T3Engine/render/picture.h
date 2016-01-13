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
    void setTexturePosition(float t_x,float t_y,float t_w,float t_h);
    void setZoom(float z);
    void setMatrix(const QMatrix4x4& m);
    void setTextures(const QString &imagePath);
    void mirror(bool m);
    void rotate(float angle,float a_x,float a_y,float a_z=0);

    float getX(){return x;}
    float getY(){return y;}
    float getZ(){return z;}
    float getZoom(){return zoom;}
    float getImageHeight(){return imageHeight;}
    float getImageWidth(){return imageWidth;}
    bool isMirror(){return mir;}
    QString getName(){return name;}
    QMatrix4x4& getMatrix(){return matrix;}

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
    float zoom;//放缩
    float x,y,z;//位置坐标
    float tx,ty;//纹理坐标
    float tw,th;//纹理宽高
    bool mir;//镜像
    float angle;//旋转角度
    float ax,ay,az;//旋转轴
    QMatrix4x4 matrix;
    QString name;
};

#endif // PICTURE_H
