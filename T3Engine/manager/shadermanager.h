#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H


class ShaderManager:public Singleton<ShaderManager>,public QOpenGLFunctions
{
public:
    ShaderManager();
    bool init();
    void destory();
    bool loadVertexShader(const QString& vShader);
    bool loadFragmentShader(const QString& fShader);
    QOpenGLShaderProgram* getProgram(){return program;}
private:
    QOpenGLShaderProgram* program;
    QString vShader;
    QString fShader;
};

#endif // SHADERMANAGER_H
