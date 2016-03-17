#ifndef WORLDCREATOR_H
#define WORLDCREATOR_H

#include<stable.h>
#include"worldopenglwidget.h"
#include"decorationwidget.h"
#include"characterwidget.h"
#include"backgroundwidget.h"

class WorldCreator:public QMainWindow
{
    Q_OBJECT
public:
    explicit WorldCreator(QWidget* parent=0);

private:
    void closeEvent(QCloseEvent *event);

    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void createDockWindow();

    bool okToContinue();
    bool openFile(const QString& path);
    bool saveFile(const QString& fileName);
    void setCurrentFile(const QString& fileName);
    QString curFile;

    QLabel* statusLabel;

    QMenu* fileMenu;
    QMenu* selectSubMenu;
    QMenu* propertyMenu;
    QMenu* moduleMenu;
    QMenu* windowMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;

    QToolBar* fileToolBar;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;

    QAction* closeAction;
    QAction* spriteSettingAction;
    QAction* worldDescriptionAction;

    QAction* showRect;
    QAction *showGridAction;
    QAction *aboutAction;
    QAction *aboutQtAction;

    WorldOpenglWidget* openglWidget;
    DecorationWidget* decorationWidget;
    CharacterWidget* characterWidget;
    BackgroundWidget* backgroundWidget;

    QDockWidget* backgroundDockWidget;
    QDockWidget* characterDockWidget;
    QDockWidget* decorationDockWidget;
private slots:
    void worldModified();

    void newWorld();
    void openWorld();
    void closeWorld();
    bool saveWorld();

    void about();

    void addDecoration(QString decorationName);
    void addCharacter(QString characterName);
    void setBackground(QString backgroundName);
};

#endif // WORLDCREATOR_H
