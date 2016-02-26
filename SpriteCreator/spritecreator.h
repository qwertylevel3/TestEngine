#ifndef SPRITECREATOR_H
#define SPRITECREATOR_H

#include"stable.h"

class SpriteCreator : public QMainWindow
{
    Q_OBJECT
public:
    explicit SpriteCreator(QWidget *parent = 0);
public slots:
    void open();

    void complete();
private:
    void createActions();
    void createMenus();

    bool parseXsd(const QString& fileName);

    QMenu* fileMenu;

    QAction* openAction;
    QAction* exitAction;

    QTabWidget* tabWidget;

};

#endif // SPRITECREATOR_H
