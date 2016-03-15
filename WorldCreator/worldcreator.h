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
    void contextMenuEvent(QContextMenuEvent *event);
    void closeEvent(QCloseEvent *event);


    QString strippedName(const QString &fullFileName);

    void updateDockWindow();
    void clearDockWindow();
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void createDockWindow();
    void readSettings();
    void writeSettings();
    bool okToContinue();
    bool loadFile(const QString& fileName);
    bool saveFile(const QString& fileName);
    void setCurrentFile(const QString& fileName);
    void updateRecentFileActions();
    QStringList recentFiles;
    QString curFile;
    enum {MaxRecentFiles=5};
    QAction* recentFileActions[MaxRecentFiles];
    QAction* separatorAction;

    QLabel* statusLabel;

    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* selectSubMenu;
    QMenu* propertyMenu;
    QMenu* moduleMenu;
    QMenu* windowMenu;
    QMenu *optionsMenu;
    QMenu *helpMenu;
    QMenu* contextMenu;

    QToolBar* fileToolBar;
    QToolBar* editToolBar;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;
    QAction* cutAction;
    QAction* pasteAction;
    QAction* deleteAction;
    QAction* copyAction;
    QAction* closeAction;
    QAction* spriteSettingAction;
    QAction* worldDescriptionAction;

    QAction* showRect;
    QAction* characterSelectable;
    QAction* terrainSelectable;
    QAction* decorationSelectable;
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
    void open();
    void closeWorld();
    bool save();
    void about();
    void openRecentFile();
    void updateStatusBar();

    void addDecoration(QString decorationName);
    void addCharacter(QString characterName);
    void setBackground(QString backgroundName);
};

#endif // WORLDCREATOR_H
