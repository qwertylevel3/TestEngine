#include "openglwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    //format.setSamples(16);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    OpenGLWindow window;
    window.setFormat(format);
    window.resize(640, 480);
    window.show();

    return a.exec();
}
