#include "worldcreator.h"

WorldCreator::WorldCreator(QWidget* parent)
    :QMainWindow(parent)
{
    openglWidget=new WorldOpenglWidget(this);

    this->setCentralWidget(openglWidget);
    setWindowState(Qt::WindowMaximized);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();
    createDockWindow();

    readSettings();

    //bug，鼠标右键被占用，导致dockwidget关闭后无法显示
    //暂时解决方案：强行显示
    backgroundDockWidget->setVisible(true);
    characterDockWidget->setVisible(true);
    decorationDockWidget->setVisible(true);

    setWindowIcon(QIcon(":/images/icon.png"));
    //setCurrentFile("");

    connect(decorationWidget,SIGNAL(addDecoration(QString)),this,SLOT(addDecoration(QString)));
    connect(characterWidget,SIGNAL(addCharacter(QString)),this,SLOT(addCharacter(QString)));
    connect(backgroundWidget,SIGNAL(setBackground(QString)),this,SLOT(setBackground(QString)));
}


void WorldCreator::contextMenuEvent(QContextMenuEvent *event)
{
     contextMenu->exec(QCursor::pos());
}


void WorldCreator::closeEvent(QCloseEvent *event)
{
    if (okToContinue()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void WorldCreator::newWorld()
{
    if (okToContinue()) {
        bool ok;
        QString fileName = QInputDialog::getText(this, tr("create new world"),
                                             tr("world name:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
        if (ok && !fileName.isEmpty())
        {
            openglWidget->newWorld(fileName);
            setCurrentFile(fileName);
        }
    }
}

void WorldCreator::open()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open World"), ".",
                                                        tr("World files (*.xml)"));
        if (!fileName.isEmpty())
        {
            loadFile(fileName);
            //curFile=world->getWorldName();
            updateDockWindow();
        }
    }
}

void WorldCreator::closeWorld()
{
    if(okToContinue())
    {
        //world->close();
        clearDockWindow();
    }
    setCurrentFile("");
}

bool WorldCreator::save()
{
    if(curFile!="")
    {
        return saveFile(curFile);
    }
    return false;
}


void WorldCreator::about()
{
    QMessageBox::about(this, tr("About WorldCreator"),
            tr("<h2>WorldCreator 0.1</h2>"
               "<p>Copyright &copy; 2015 qwertylevel3"
               "<p>WorldCreator is a small application that "
               "you can create a small 2d game "
               "<p>If any question : qwertylevel3@126.com"));

}

void WorldCreator::openRecentFile()
{
    if (okToContinue()) {
        QAction *action = qobject_cast<QAction *>(sender());
        if (action)
        {
            loadFile(action->data().toString());
            //curFile=world->getWorldName();
            updateDockWindow();
        }

    }
}

void WorldCreator::updateStatusBar()
{
    statusLabel->setText("world update...");
}

void WorldCreator::addDecoration(QString decorationName)
{
    openglWidget->addDecoration(decorationName);
}

void WorldCreator::addCharacter(QString characterName)
{
    openglWidget->addCharacter(characterName);
}

void WorldCreator::setBackground(QString backgroundName)
{
    openglWidget->setBackground(backgroundName);
}

void WorldCreator::worldModified()
{
    setWindowModified(true);
    updateStatusBar();
}

void WorldCreator::createActions()
{
    newAction = new QAction(tr("&New"), this);
    newAction->setIcon(QIcon(":/images/new.png"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("Create a new world"));
    connect(newAction, SIGNAL(triggered()), this, SLOT(newWorld()));

    openAction = new QAction(tr("&Open..."), this);
    openAction->setIcon(QIcon(":/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the world to disk"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    closeAction=new QAction(tr("Close"),this);
    closeAction->setStatusTip(tr("close the world"));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(closeWorld()));


    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    cutAction = new QAction(tr("Cu&t"), this);
    cutAction->setIcon(QIcon(":/images/cut.png"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("Cut the current sprite "
                               "to the clipboard"));
    //connect(cutAction, SIGNAL(triggered()), world, SLOT(cut()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/images/copy.png"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("Copy the current sprite "
                                "to the clipboard"));
    //connect(copyAction, SIGNAL(triggered()), world, SLOT(copy()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/images/paste.png"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("Paste the sprite into "
                                 "the current world"));
//    connect(pasteAction, SIGNAL(triggered()),
//            world, SLOT(paste()));

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("Delete the current selection's sprite"));

//    connect(deleteAction, SIGNAL(triggered()),
//            world, SLOT(del()));

    showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setCheckable(true);
    //showGridAction->setChecked(world->showGrid());
    showGridAction->setStatusTip(tr("Show or hide the world's "
                                    "grid"));
    //connect(showGridAction, SIGNAL(toggled(bool)),
    //        world, SLOT(setShowGrid(bool)));


    characterSelectable=new QAction(tr("set character selectable"),this);
    characterSelectable->setCheckable(true);
    //characterSelectable->setChecked(world->getCharacterSelectable());
    characterSelectable->setStatusTip(tr("Switch character selectable on or off"));
    //connect(characterSelectable,SIGNAL(toggled(bool)),world,SLOT(setCharacterDragable(bool)));

    terrainSelectable=new QAction(tr("set terrain selectable"),this);
    terrainSelectable->setCheckable(true);
   // terrainSelectable->setChecked(world->getTerrainSelectable());
    terrainSelectable->setStatusTip(tr("Switch terrain selectable on or off"));
    //connect(terrainSelectable,SIGNAL(toggled(bool)),world,SLOT(setTerrainDragable(bool)));

    decorationSelectable=new QAction(tr("set decoration selectable"),this);
    decorationSelectable->setCheckable(true);
    //decorationSelectable->setChecked(world->getDecorationSelectable());
    decorationSelectable->setStatusTip(tr("Switch decoration selectable on or off"));
    //connect(decorationSelectable,SIGNAL(toggled(bool)),world,SLOT(setDecorationDragable(bool)));

    showRect=new QAction(tr("show collision rect"),this);
    showRect->setCheckable(true);
    //showRect->setChecked(world->getShowRect());
    showRect->setStatusTip(tr("Switch show collision rect"));
    //connect(showRect,SIGNAL(toggled(bool)),world,SLOT(setShowRect(bool)));

    spriteSettingAction=new QAction(tr("setting"),this);
    spriteSettingAction->setStatusTip(tr("open sprite setting panel"));
    //connect(spriteSettingAction,SIGNAL(triggered()),world,SLOT(spriteSetting()));

    worldDescriptionAction=new QAction(tr("world description"),this);
    worldDescriptionAction->setStatusTip(tr("set the world description"));
//    connect(worldDescriptionAction,SIGNAL(triggered()),world,SLOT(worldDescription()));

    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("Show the application's About box"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void WorldCreator::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File(&F)"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    separatorAction = fileMenu->addSeparator();
    fileMenu->addSeparator();
    fileMenu->addAction(closeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    editMenu = menuBar()->addMenu(tr("Edit(&E)"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    editMenu->addSeparator();
//    editMenu->addAction(findAction);
//    editMenu->addAction(goToCellAction);

    propertyMenu = menuBar()->addMenu(tr("Property(&P)"));
    propertyMenu->addAction(worldDescriptionAction);
//    toolsMenu->addAction(recalculateAction);
//    toolsMenu->addAction(sortAction);
    moduleMenu = menuBar()->addMenu(tr("Module(&M)"));

    optionsMenu = menuBar()->addMenu(tr("Options(&O)"));
    optionsMenu->addAction(characterSelectable);
    optionsMenu->addAction(decorationSelectable);
    optionsMenu->addAction(terrainSelectable);
    optionsMenu->addAction(showRect);



    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    contextMenu=new QMenu(this);
    contextMenu->addAction(cutAction);
    contextMenu->addAction(copyAction);
    contextMenu->addAction(pasteAction);
    contextMenu->addSeparator();
    contextMenu->addAction(spriteSettingAction);
}

void WorldCreator::createContextMenu()
{
//    world->addAction(cutAction);
//    world->addAction(copyAction);
//    world->addAction(pasteAction);
    //spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void WorldCreator::createToolBars()
{
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->setObjectName("fileToolBar");

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->setObjectName("editToolBar");

}

void WorldCreator::createStatusBar()
{
    statusLabel = new QLabel;
    statusLabel->setIndent(3);

    //statusBar()->addWidget(statusLabel);

//    connect(spreadsheet, SIGNAL(modified()),
//            this, SLOT(spreadsheetModified()));

    updateStatusBar();
}

void WorldCreator::createDockWindow()
{
    backgroundWidget=new BackgroundWidget(this);
    characterWidget=new CharacterWidget(this);
    decorationWidget=new DecorationWidget(this);


    backgroundDockWidget=new QDockWidget(tr("background"));
    backgroundDockWidget->setObjectName("background");
    backgroundDockWidget->setWidget(backgroundWidget);
    addDockWidget(Qt::RightDockWidgetArea,backgroundDockWidget);

    characterDockWidget=new QDockWidget(tr("character"));
    characterDockWidget->setObjectName("character");
    characterDockWidget->setWidget(characterWidget);
    addDockWidget(Qt::RightDockWidgetArea,characterDockWidget);

    decorationDockWidget=new QDockWidget(tr("decoration"));
    decorationDockWidget->setObjectName("decoration");
    decorationDockWidget->setWidget(decorationWidget);
    addDockWidget(Qt::RightDockWidgetArea,decorationDockWidget);
}

void WorldCreator::readSettings()
{
 //   QSettings settings("qwertylevel3", "world");

 //   settings.beginGroup("mainwindow");
 //   restoreGeometry(settings.value("geometry").toByteArray());
 //   restoreState(settings.value("state").toByteArray());
 //   recentFiles = settings.value("recentFiles").toStringList();
 //   settings.endGroup();
 //   updateRecentFileActions();
}

void WorldCreator::writeSettings()
{
 //   QSettings settings("qwertylevel3", "world");

 //   settings.beginGroup("mainwindow");
 //   settings.setValue("geometry", saveGeometry());
 //   settings.setValue("state",saveState());
 //   settings.setValue("recentFiles", recentFiles);
 //   settings.endGroup();
}

bool WorldCreator::okToContinue()
{
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("World"),
                        tr("The document has been modified.\n"
                           "Do you want to save your changes?"),
                        QMessageBox::Yes | QMessageBox::No
                        | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return save();
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool WorldCreator::loadFile(const QString &fileName)
{
//    if (!world->loadFile(fileName)) {
//        statusBar()->showMessage(tr("Loading canceled"), 2000);
//        return false;
//    }
//
//    setCurrentFile(fileName);
//    statusBar()->showMessage(tr("File loaded"), 2000);
//
//    this->setCentralWidget(world->getView());
//    return true;
}

bool WorldCreator::saveFile(const QString &fileName)
{
    if (!openglWidget->save(fileName)) {
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void WorldCreator::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    setWindowTitle(tr("%1[*] - %2").arg(curFile)
                                   .arg(tr("World")));
}

QString WorldCreator::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void WorldCreator::updateDockWindow()
{
    characterWidget->update();
    backgroundWidget->update();
    decorationWidget->update();
}

void WorldCreator::clearDockWindow()
{
//    characterWidget->clear();
//    backgroundWidget->clear();
//    decorationWidget->clear();
}
