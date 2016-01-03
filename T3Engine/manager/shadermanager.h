#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include<QOpenGLShaderProgram>

class ShaderManager
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
