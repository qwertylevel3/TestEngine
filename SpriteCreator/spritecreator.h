#ifndef SPRITECREATOR_H
#define SPRITECREATOR_H

#include"stable.h"
#include"openglwidget.h"
#include"spritegeneraldialog.h"
#include"spritedetaildialog.h"

class SpriteButton: public QCommandLinkButton
{
    Q_OBJECT
public:
    SpriteButton(QWidget* parent=0);
signals:
    void spriteName(const QString& name);
public slots:
    void sendSpriteName();
};

class SpriteCreator : public QMainWindow
{
    Q_OBJECT
public:
    explicit SpriteCreator(QWidget *parent = 0);
public slots:
    void save();

    void setSprite(const QString& spriteName);
    void editSprite();
    void newSprite();
    void complete();
private:
    void createActions();
    void createMenus();
    void makeUI();

    void makeSpriteList();
    void makeTotalSpriteLabel();
    void makeButton();
    void updateSpriteList();


    Sprite* makeNewSpriteInstance();
    Animatioin* makeNewSpriteActionInstance(int index);
    Frame* makeNewSpriteFrameInstance(int actionIndex,int frameIndex);
    
    QMenu* fileMenu;

    QAction* openAction;
    QAction* exitAction;
    QAction* saveAction;

    OpenglWidget* openglWidget;

    QScrollArea* listArea;
    QHBoxLayout* totalNumberLayout;
    QVBoxLayout* buttonLayout;

    QString currentSpriteName;

    SpriteGeneralDialog *generalDialog;
    SpriteDetailDialog *detailDialog;
    QHBoxLayout* hLayout;
    QVBoxLayout* vLayout;
};

#endif // SPRITECREATOR_H
