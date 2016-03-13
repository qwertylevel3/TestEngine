#include "worldcreator.h"

WorldCreator::WorldCreator(QWidget* parent)
    :QMainWindow(parent)
{
    openglWidget=new WorldOpenglWidget(this);

    this->setCentralWidget(openglWidget);
    setWindowState(Qt::WindowMaximized);

}

