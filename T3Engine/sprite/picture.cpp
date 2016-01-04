/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "picture.h"

#include <QVector2D>
#include <QVector3D>
#include<QMatrix2x2>
#include<math.h>
#include"T3Engine/manager/shadermanager.h"

Picture::Picture(const QString &imageName)
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    initFaceGeometry();
    initTextures(imageName);

    zoom=1;
    x=y=z=0;
    cx=cy=0;
    dx=dy=1;
    mir=false;

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
    vertices[0]=VertexData({QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)});
    vertices[1]=VertexData({QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)});
    vertices[2]=VertexData({QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)});
    vertices[3]=VertexData({QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(1.0f, 1.0f)});

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
    if(!mir)
    {
        vertices[0]=VertexData({QVector3D(-1.0f+x, -1.0f+y,  1.0f+z)*zoom, QVector2D(0.0f+cx, 0.0f+cy)*zoom});
        vertices[1]=VertexData({QVector3D( 1.0f+x, -1.0f+y,  1.0f+z)*zoom, QVector2D(1.0f*dx+cx, 0.0f+cy)*zoom});
        vertices[2]=VertexData({QVector3D(-1.0f+x,  1.0f+y,  1.0f+z)*zoom, QVector2D(0.0f+cx, 1.0f*dy+cy)*zoom});
        vertices[3]=VertexData({QVector3D( 1.0f+x,  1.0f+y,  1.0f+z)*zoom, QVector2D(1.0f*dx+cx, 1.0f*dy+cy)*zoom});
    }
    else
    {
        vertices[0]=VertexData({QVector3D(-1.0f+x, -1.0f+y,  1.0f+z)*zoom, QVector2D(1.0f*dx+cx, 0.0f+cy)*zoom});
        vertices[1]=VertexData({QVector3D( 1.0f+x, -1.0f+y,  1.0f+z)*zoom, QVector2D(0.0f+cx, 0.0f+cy)*zoom});
        vertices[2]=VertexData({QVector3D(-1.0f+x,  1.0f+y,  1.0f+z)*zoom, QVector2D(1.0f*dx+cx, 1.0f*dy+cy)*zoom});
        vertices[3]=VertexData({QVector3D( 1.0f+x,  1.0f+y,  1.0f+z)*zoom, QVector2D(0.0f+cx, 1.0f*dy+cy)*zoom});
    }
    arrayBuf.write(0,vertices,4*sizeof(VertexData));
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
}

void Picture::setCoordinate(float x, float y, float z)
{
    this->x=x;
    this->y=y;
    this->z=z;

    updateArrayBuffer();
}

void Picture::setTexturePosition(float x, float y, float dx, float dy)
{
    this->cx=x;
    this->cy=y;
    this->dx=dx;
    this->dy=dy;

    updateArrayBuffer();
}

void Picture::setZoom(float z)
{
    zoom=z;

    updateArrayBuffer();
}

void Picture::setTexture(const QString &name)
{
    image.load(name);
}

void Picture::mirror(bool m)
{
    mir=m;
    updateArrayBuffer();
}


void Picture::initTextures(const QString &imageName)
{
    setTexture(imageName);

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
