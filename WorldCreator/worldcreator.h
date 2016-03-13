#ifndef WORLDCREATOR_H
#define WORLDCREATOR_H

#include <QMainWindow>
#include<stable.h>
#include"worldopenglwidget.h"

class WorldCreator:public QMainWindow
{
    Q_OBJECT
public:
    explicit WorldCreator(QWidget* parent=0);
private:
    WorldOpenglWidget* openglWidget;

};

#endif // WORLDCREATOR_H
