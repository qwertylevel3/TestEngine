#include "picture.h"

#include"stable.h"
#include<math.h>
#include"shadermanager.h"
#include"gameconfigurator.h"

Picture::Picture(const QString &imagePath)
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();
    initParameter();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initFaceGeometry();

    //initTexture
    loadImage(imagePath);
    setTextures(image);

}

Picture::~Picture()
{
    arrayBuf.destroy();
    indexBuf.destroy();
    delete texture;
}


void Picture::initFaceGeometry()
{
    vertices[0]=VertexData({QVector3D(-1.0f, -1.0f,  0.0f), QVector2D(0.0f, 0.0f)});
    vertices[1]=VertexData({QVector3D( 1.0f, -1.0f,  0.0f), QVector2D(1.0f, 0.0f)});
    vertices[2]=VertexData({QVector3D(-1.0f,  1.0f,  0.0f), QVector2D(0.0f, 1.0f)});
    vertices[3]=VertexData({QVector3D( 1.0f,  1.0f,  0.0f), QVector2D(1.0f, 1.0f)});

    indices[0]=0;
    indices[1]=1;
    indices[2]=2;
    indices[3]=3;
    indices[4]=3;

    allocateBuffer();
}

void Picture::allocateBuffer()
{
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 4 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 5 * sizeof(GLushort));

}

void Picture::updateArrayBuffer()
{
    matrix.setToIdentity();
    matrix.rotate(angle,ax,ay,az);
    //matrix.scale(zoomX,zoomY,1);

   // width=width*zoomX;
    //height=height*zoomY;

    if(!mir)
    {
        updateVertexData();
    }
    else
    {
        updateVertexDataMir();
    }
    arrayBuf.bind();
    arrayBuf.write(0,vertices,4*sizeof(VertexData));
}

void Picture::initParameter()
{
    texture=0;
    zoomX=1;
    zoomY=1;
    x=y=z=0;
    width=1;
    height=1;
    tx=ty=0;
    tw=th=1;
    mir=false;
    repeatX=0;
    repeatY=0;

    angle=0;
    ax=0;
    ay=0;
    az=0;

    alpha=1.0;

    matrix.setToIdentity();


    tempImage=0;
}

void Picture::updateVertexData()
{
    float tempWidth=width*zoomX/GameConfigurator::instance()->getScale();
    float tempHeight=height*zoomY/GameConfigurator::instance()->getScale();
    tempWidth/=2;
    tempHeight/=2;

    QVector4D tempPosition[4];
    tempPosition[0]=QVector4D(-1.0f*tempWidth,-1.0f*tempHeight,0.0f,1);
    tempPosition[1]=QVector4D(1.0f*tempWidth,-1.0f*tempHeight,0.0f,1);
    tempPosition[2]=QVector4D(-1.0f*tempWidth,1.0f*tempHeight,0.0f,1);
    tempPosition[3]=QVector4D(1.0f*tempWidth,1.0f*tempHeight,0.0f,1);

    //rotate
    for(int i=0;i<4;i++)
    {
        tempPosition[i]=tempPosition[i]*matrix;
    }

    //move
    for(int i=0;i<4;i++)
    {
        tempPosition[i].setX(tempPosition[i].x()+x);
        tempPosition[i].setY(tempPosition[i].y()+y);
        tempPosition[i].setZ(tempPosition[i].z()+z);
    }


    vertices[0]=VertexData({tempPosition[0].toVector3D(),
                            QVector2D(0.0f+tx, 0.0f+ty)});
    vertices[1]=VertexData({tempPosition[1].toVector3D(),
                            QVector2D(1.0f*tw+tx+repeatX, 0.0f+ty)});
    vertices[2]=VertexData({tempPosition[2].toVector3D(),
                            QVector2D(0.0f+tx, 1.0f*th+ty+repeatY)});
    vertices[3]=VertexData({tempPosition[3].toVector3D(),
                            QVector2D(1.0f*tw+tx+repeatX, 1.0f*th+ty+repeatY)});
}

void Picture::updateVertexDataMir()
{
//    float tempWidth=width*zoomX/GameConfigurator::instance()->getScale();
//    float tempHeight=height*zoomY/GameConfigurator::instance()->getScale();
//
//    vertices[0]=VertexData({(QVector4D(-1.0f*tempWidth+x, -1.0f*tempHeight+y,  0.0f+z,1)*matrix).toVector3D(),
//                            QVector2D(1.0f*tw+tx+repeatX, 0.0f+ty)});
//    vertices[1]=VertexData({(QVector4D( 1.0f*tempWidth+x, -1.0f*tempHeight+y,  0.0f+z,1)*matrix).toVector3D(),
//                            QVector2D(0.0f+tx, 0.0f+ty)});
//    vertices[2]=VertexData({(QVector4D(-1.0f*tempWidth+x, 1.0f*tempHeight+y,  0.0f+z,1)*matrix).toVector3D(),
//                            QVector2D(1.0f*tw+tx+repeatX, 1.0f*th+ty+repeatY)});
//    vertices[3]=VertexData({(QVector4D( 1.0f*tempWidth+x,  1.0f*tempHeight+y,  0.0f+z,1)*matrix).toVector3D(),
//                            QVector2D(0.0f+tx, 1.0f*th+ty+repeatY)});
}

void Picture::setName(const QString &imagePath)
{
    int len=imagePath.length()-QDir::currentPath().length();
    name=imagePath.right(len);
}

float Picture::getAz() const
{
    return az;
}

void Picture::setAz(float value)
{
    az = value;
}

float Picture::getAy() const
{
    return ay;
}

void Picture::setAy(float value)
{
    ay = value;
}

float Picture::getAx() const
{
    return ax;
}

void Picture::setAx(float value)
{
    ax = value;
}

float Picture::getAngle() const
{
    return angle;
}

void Picture::setAngle(float value)
{
    angle = value;
}

float Picture::getAlpha() const
{
    return alpha;
}

void Picture::setAlpha(float value)
{
    alpha = value;
}


void Picture::draw()
{
    updateArrayBuffer();

    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    texture->bind();

    quintptr offset = 0;

    int vertexLocation = ShaderManager::instance()->getProgram()->attributeLocation("a_position");
    ShaderManager::instance()->getProgram()->enableAttributeArray(vertexLocation);
    ShaderManager::instance()->getProgram()->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texcoordLocation =
            ShaderManager::instance()->getProgram()->attributeLocation("a_texcoord");
    ShaderManager::instance()->getProgram()->enableAttributeArray(texcoordLocation);
    ShaderManager::instance()->getProgram()->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    //set alpha
    ShaderManager::instance()->getProgram()->setUniformValue("alpha",alpha);


    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);

}

void Picture::loadImage(const QString &imagePath)
{
    if(!image.load(imagePath))
    {
        qDebug()<<"can not load "<<imagePath<<endl;
        return ;
    }
    setName(imagePath);
}

void Picture::rotate(float angle, float a_x, float a_y, float a_z)
{
    this->angle=angle;
    ax=a_x;
    ay=a_y;
    az=a_z;

}


void Picture::setTextures(QImage img)
{
    if(texture!=0)
    {
        delete texture;
    }
    texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture->setFormat(QOpenGLTexture::RGBA8U);
    texture->setData(img.mirrored());
    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}

void Picture::setText(const QString &content)
{
    if(tempImage!=0)
    {
        delete tempImage;
    }
    tempImage=new QImage;
    *tempImage=image;

    text.setContent(content);
    text.writeToImage(*tempImage);

    setTextures(*tempImage);
}


void Picture::setCoordinate(float x, float y, float z)
{
    this->x=x;
    this->y=y;
    this->z=z;
}


void Picture::setTexturePosition(float t_x, float t_y, float t_w, float t_h)
{
    this->tx=t_x;
    this->ty=t_y;
    this->tw=t_w;
    this->th=t_h;
}
