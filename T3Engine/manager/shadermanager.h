#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include<QOpenGLShaderProgram>
#include"T3Engine/singleton.h"
#include<QOpenGLFunctions>

class ShaderManager:public Singleton<ShaderManager>,public QOpenGLFunctions
{
public:
    ShaderManager();
    bool init();
    bool loadVertexShader(const QString& vShader);
    bool loadFragmentShader(const QString& fShader);
    QOpenGLShaderProgram* getProgram(){return program;}
private:
    QOpenGLShaderProgram* program;
    QString vShader;
    QString fShader;
};

#endif // SHADERMANAGER_H
