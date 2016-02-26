#include "gameconfigurator.h"

GameConfigurator::GameConfigurator()
{

}

void GameConfigurator::init(const QString& fileName)
{
    parseXml(fileName);

    //format.setSamples(16);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);



}
QString GameConfigurator::getSceneConfigFileName() const
{
    return SceneConfigFileName;
}

void GameConfigurator::setSceneConfigFileName(const QString &value)
{
    SceneConfigFileName = value;
}

void GameConfigurator::makeParameter()
{
    reader.readNextStartElement();//<Scale>
    scale=reader.readElementText().toInt();

    reader.readNextStartElement();//<DrawRect>
    drawRect=reader.readElementText().toInt()==1?true:false;

    reader.readNextStartElement();//<paintNear>
    paintNear=reader.readElementText().toInt();

    reader.readNextStartElement();//<paintFar>
    paintFar=reader.readElementText().toInt();

    reader.readNextStartElement();//<windowWidth>
    windowWidth=reader.readElementText().toInt();

    reader.readNextStartElement();//<windowHeight>
    windowHeight=reader.readElementText().toInt();

    reader.readNextStartElement();//<spriteConfigFileName>
    spriteConfigFileName=reader.readElementText();

    reader.readNextStartElement();//<characterConfigFileName>
    characterConfigFileName=reader.readElementText();

    reader.readNextStartElement();//<terrainConfigFileName>
    terrainConfigFileName=reader.readElementText();

    reader.readNextStartElement();//<decorationConfigFilaName>
    decorationConfigFileName=reader.readElementText();

    reader.readNextStartElement();//<bulletConfigFileName>
    bulletConfigFileName=reader.readElementText();

    reader.readNextStartElement();//<sceneConfigFileName>
    SceneConfigFileName=reader.readElementText();
}

void GameConfigurator::parseXml(const QString &fileName)
{
    QString path=QDir::currentPath()+QDir::separator()+fileName;

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"can not open "<<fileName<<endl;
        return ;
    }
    reader.setDevice(&file);

    reader.readNextStartElement();//<Config>;

    makeParameter();

    file.close();
}









