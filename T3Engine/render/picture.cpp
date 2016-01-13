#include "picture.h"

#include <QVector2D>
#include <QVector3D>
#include<QMatrix2x2>
#include<math.h>
#include"T3Engine/manager/shadermanager.h"
#include<QDir>

Picture::Picture(const QString &imagePath)
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initFaceGeometry();

    setTextures(imagePath);

    setName(imagePath);

    zoom=1;
    x=y=z=0;
    tx=ty=0;
    tw=th=1;
    mir=false;

    angle=0;
    ax=0;
    ay=0;
    az=0;

    matrix.setToIdentity();

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
    matrix.rotate(angle,x,y,z);
    matrix.scale(zoom,zoom,1);
    if(!mir)
    {
        vertices[0]=VertexData({(QVector4D(-1.0f+x, -1.0f+y,  0.0f+z,1)*matrix).toVector3D(),
                                QVector2D(0.0f+tx, 0.0f+ty)});
        vertices[1]=VertexData({(QVector4D( 1.0f+x, -1.0f+y,  0.0f+z,1)*matrix).toVector3D(),
                                QVector2D(1.0f*tw+tx, 0.0f+ty)});
        vertices[2]=VertexData({(QVector4D(-1.0f+x,  1.0f+y,  0.0f+z,1)*matrix).toVector3D(),
                                QVector2D(0.0f+tx, 1.0f*th+ty)});
        vertices[3]=VertexData({(QVector4D( 1.0f+x,  1.0f+y,  0.0f+z,1)*matrix).toVector3D(),
                                QVector2D(1.0f*tw+tx, 1.0f*th+ty)});


    }
    else
    {
        vertices[0]=VertexData({(QVector4D(-1.0f+x, -1.0f+y,  0.0f+z,1)*matrix).toVector3D(),
                                QVector2D(1.0f*tw+tx, 0.0f+ty)});
        vertices[1]=VertexData({(QVector4D( 1.0f+x, -1.0f+y,  0.0f+z,1)*matrix).toVector3D(),
                                QVector2D(0.0f+tx, 0.0f+ty)});
        vertices[2]=VertexData({(QVector4D(-1.0f+x,  1.0f+y,  0.0f+z,1)*matrix).toVector3D(),
                                QVector2D(1.0f*tw+tx, 1.0f*th+ty)});
        vertices[3]=VertexData({(QVector4D( 1.0f+x,  1.0f+y,  0.0f+z,1)*matrix).toVector3D(),
                                QVector2D(0.0f+tx, 1.0f*th+ty)});
    }
    arrayBuf.bind();
    arrayBuf.write(0,vertices,4*sizeof(VertexData));
}

void Picture::setName(const QString &imagePath)
{
    int len=imagePath.length()-QDir::currentPath().length();
    name=imagePath.right(len);
}


void Picture::draw()
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    texture->bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = ShaderManager::instance()->getProgram()->attributeLocation("a_position");
    ShaderManager::instance()->getProgram()->enableAttributeArray(vertexLocation);
    ShaderManager::instance()->getProgram()->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation =
            ShaderManager::instance()->getProgram()->attributeLocation("a_texcoord");
    ShaderManager::instance()->getProgram()->enableAttributeArray(texcoordLocation);
    ShaderManager::instance()->getProgram()->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);

    //arrayBuf.release();
    //indexBuf.release();
}

void Picture::setCoordinate(float x, float y, float z)
{
    this->x=x;
    this->y=y;
    this->z=z;

    updateArrayBuffer();
}

void Picture::setTexturePosition(float t_x, float t_y, float t_w, float t_h)
{
    this->tx=t_x;
    this->ty=t_y;
    this->tw=t_w;
    this->th=t_h;

    updateArrayBuffer();
}

void Picture::setZoom(float z)
{
    zoom=z;

    updateArrayBuffer();
}

void Picture::setMatrix(const QMatrix4x4 &m)
{
    matrix=m;
    updateArrayBuffer();
}

void Picture::mirror(bool m)
{
    mir=m;
    updateArrayBuffer();
}

void Picture::rotate(float angle, float a_x, float a_y, float a_z)
{
    this->angle=angle;
    ax=a_x;
    ay=a_y;
    az=a_z;

    updateArrayBuffer();
}


void Picture::setTextures(const QString &imagePath)
{

    if(!image.load(imagePath))
    {
        qDebug()<<"can not load "<<imagePath<<endl;
        return ;
    }
    setName(imagePath);
    imageWidth=image.size().width();
    imageHeight=image.size().height();


    texture = new QOpenGLTexture(QOpenGLTexture::Target2D);
    texture->setFormat(QOpenGLTexture::RGBA8U);
    texture->setData(image.mirrored());
    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
}
