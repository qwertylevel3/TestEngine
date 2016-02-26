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
    void initManager();
    void createActions();
    void createMenus();
    void makeUI();

    void makeSpriteList();
    void makeTotalSpriteLabel();
    void makeButton();
    
    QMenu* fileMenu;

    QAction* openAction;
    QAction* exitAction;


    QScrollArea* listArea;
    QVBoxLayout* totalNumberLayout;
    QVBoxLayout* buttonLayout;
};

#endif // SPRITECREATOR_H
