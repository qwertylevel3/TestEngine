#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include<QOpenGLShaderProgram>
#include"singleton.h"
#include<QOpenGLFunctions>

class ShaderManager:public Singleton<ShaderManager>,public QOpenGLFunctions
{
public:
    ShaderManager();
    bool init(const QString& vShader,const QString& fShader);
    bool loadVertexShader(const QString& vShader);
    bool loadFragmentShader(const QString& fShader);
    QOpenGLShaderProgram* getProgram(){return program;}
private:
    QOpenGLShaderProgram* program;
};

#endif // SHADERMANAGER_H
