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
    void setTexturePosition(float x,float y,float dx,float dy);
    void setZoom(float z);
    void setTextures(const QString &imagePath);
    void mirror(bool m);

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
    float zoom;
    float x,y,z;
    float cx,cy;
    float dx,dy;
    bool mir;
    QMatrix4x4 matrix;
    QString name;
};

#endif // PICTURE_H
