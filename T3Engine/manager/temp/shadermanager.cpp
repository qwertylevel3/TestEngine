#include "shadermanager.h"

ShaderManager::ShaderManager()
{
    vShader=":/vshader.glsl";
    fShader=":/fshader.glsl";
}

bool ShaderManager::loadVertexShader(const QString &vShader)
{
    if(!program->addShaderFromSourceFile(QOpenGLShader::Vertex,vShader))
    {
        qDebug()<<"can not load "<<vShader<<endl;
        return false;
    }
    return true;
}

bool ShaderManager::loadFragmentShader(const QString &fShader)
{
    if(!program->addShaderFromSourceFile(QOpenGLShader::Fragment,fShader))
    {
        qDebug()<<"can not load "<<fShader<<endl;
        return false;
    }
    return true;
}

bool ShaderManager::init()
{
    QOpenGLFunctions::initializeOpenGLFunctions();

    program=new QOpenGLShaderProgram;

    if(!loadVertexShader(vShader))
        return false;
    if(!loadFragmentShader(fShader))
        return false;
    if (!program->link())
    {
        qDebug()<<"shader can not link"<<endl;
        return false;
    }
    if (!program->bind())
    {
        qDebug()<<"shader can not bind"<<endl;
        return false;
    }
    return true;
}


