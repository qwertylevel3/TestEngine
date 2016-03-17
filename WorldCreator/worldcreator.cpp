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


void WorldCreator::closeEvent(QCloseEvent *event)
{
    if (okToContinue()) {
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

void WorldCreator::openWorld()
{
    if (okToContinue()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open World"), ".",
                                                        tr("World files (*.xml)"));
        if (!fileName.isEmpty())
        {
            openFile(fileName);
            curFile=World::instance()->getName();
        }
    }
}

void WorldCreator::closeWorld()
{
    if(okToContinue())
    {
        World::instance()->clear();
    }
    setCurrentFile("");
}

bool WorldCreator::saveWorld()
{
    if(curFile=="")
    {
        bool ok=false;
        curFile = QInputDialog::getText(this, tr("save"),
                                        tr("world name:"), QLineEdit::Normal,
                                        QDir::home().dirName(), &ok);

        if(!ok)
        {
            return false;
        }
    }
    return saveFile(curFile);
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


void WorldCreator::addDecoration(QString decorationName)
{
    openglWidget->addDecoration(decorationName);
    worldModified();
}

void WorldCreator::addCharacter(QString characterName)
{
    openglWidget->addCharacter(characterName);
    worldModified();
}

void WorldCreator::setBackground(QString backgroundName)
{
    openglWidget->setBackground(backgroundName);
    worldModified();
}

void WorldCreator::worldModified()
{
    setWindowModified(true);
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
    connect(openAction, SIGNAL(triggered()), this, SLOT(openWorld()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save the world to disk"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveWorld()));

    closeAction=new QAction(tr("Close"),this);
    closeAction->setStatusTip(tr("close the world"));
    connect(closeAction,SIGNAL(triggered()),this,SLOT(closeWorld()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));


    showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setCheckable(true);
    //showGridAction->setChecked(world->showGrid());
    showGridAction->setStatusTip(tr("Show or hide the world's "
                                    "grid"));
    //connect(showGridAction, SIGNAL(toggled(bool)),
    //        world, SLOT(setShowGrid(bool)));

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
    fileMenu->addSeparator();
    fileMenu->addAction(closeAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    propertyMenu = menuBar()->addMenu(tr("Property(&P)"));
    propertyMenu->addAction(worldDescriptionAction);
//    toolsMenu->addAction(recalculateAction);
//    toolsMenu->addAction(sortAction);
    moduleMenu = menuBar()->addMenu(tr("Module(&M)"));

    optionsMenu = menuBar()->addMenu(tr("Options(&O)"));
    optionsMenu->addAction(showRect);



    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

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

}

void WorldCreator::createStatusBar()
{
    statusLabel = new QLabel;
    statusLabel->setIndent(3);

    //statusBar()->addWidget(statusLabel);

//    connect(spreadsheet, SIGNAL(modified()),
//            this, SLOT(spreadsheetModified()));

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

bool WorldCreator::okToContinue()
{
    if (isWindowModified()) {
        int r = QMessageBox::warning(this, tr("World"),
                        tr("The document has been modified.\n"
                           "Do you want to save your changes?"),
                        QMessageBox::Yes | QMessageBox::No
                        | QMessageBox::Cancel);
        if (r == QMessageBox::Yes) {
            return saveWorld();
        } else if (r == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}

bool WorldCreator::openFile(const QString &path)
{
    if (!openglWidget->open(path)) {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }

    setCurrentFile(World::instance()->getName());
    statusBar()->showMessage(tr("File loaded"), 2000);

    return true;
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
