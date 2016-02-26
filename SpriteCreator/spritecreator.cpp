#include "spritecreator.h"
#include"stable.h"
#include"spritemanager.h"
#include"picturemanager.h"

SpriteCreator::SpriteCreator(QWidget *parent) : QMainWindow(parent)
{
    initManager();
    makeUI();
}


void SpriteCreator::open()
{
        QString fileName=QFileDialog::getOpenFileName(this,
                                                  tr("打开xsd文件"),".",
                                                  tr("xsd files(*.xsd)"));

//    if(!fileName.isEmpty())
//    {
//        if(!parseXsd(fileName))
//        {
//            QMessageBox::warning(this,tr("Error"),
//                                 tr("The file parse fail"),
//                                 QMessageBox::Ok);
//        }
//    }

}

void SpriteCreator::save()
{

}

void SpriteCreator::complete()
{
 //    InputIDDialog dialog(this);
//    if(dialog.exec())
//    {
//        QString fileName=dialog.getID();
//        if(fileName.isEmpty())
//        {
//            QMessageBox::warning(this,tr("error"),
//                                 tr("ID 不能为空"),
//                                 QMessageBox::Ok);
//            return;
//        }
//        QDir dir;
//        dir.mkdir(fileName);
//        dir.cd(fileName);
//        dir.mkdir("index");
//        dir.mkdir("result");
//        dir.mkdir("showDetail");
//
//        QString indexFileName=fileName+QDir::separator()
//                +QString("index")+QDir::separator()+fileName+QString(".xml");
//
//        QString resultFileName=fileName+QDir::separator()
//                +QString("result")+QDir::separator()+fileName+QString(".xml");
//        QString showDetailFileName=fileName+QDir::separator()
//                +QString("showDetail")+QDir::separator()+fileName+QString(".xml");
//
//        indexTab->writeFile(indexFileName);
//        resultTab->writeFile(resultFileName);
//        showDetailTab->writeFile(showDetailFileName);
//
//        QMessageBox::warning(this,tr("over"),
//                             tr("文件已写入当前文件夹下"),
//                             QMessageBox::Ok);
//    }

}

void SpriteCreator::initManager()
{
    PictureManager::instance()->init();
    SpriteManager::instance()->init();
}

void SpriteCreator::createActions()
{
    openAction=new QAction(tr("&Open"),this);
    openAction->setIcon(QIcon(":/resource/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("打开xml文件"));
    connect(openAction,SIGNAL(triggered(bool)),this,SLOT(open()));

    exitAction=new QAction(tr("&Exit"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("退出"));
    connect(exitAction,SIGNAL(triggered(bool)),this,SLOT(close()));

    saveAction=new QAction(tr("&Save"),this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("保存"));
    connect(saveAction,SIGNAL(triggered(bool)),this,SLOT(save()));

}

void SpriteCreator::createMenus()
{
    fileMenu=menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
}

void SpriteCreator::makeUI()
{
    createActions();
    createMenus();

    makeSpriteList();
    makeTotalSpriteLabel();
    makeButton();

    QWidget* mainWidget=new QWidget();

    QHBoxLayout* hLayout=new QHBoxLayout();
    QVBoxLayout* vLayout=new QVBoxLayout();

    vLayout->addLayout(totalNumberLayout);
    vLayout->addStretch();
    vLayout->addLayout(buttonLayout);

    hLayout->addWidget(listArea);
    hLayout->addLayout(vLayout);

    mainWidget->setLayout(hLayout);

    setCentralWidget(mainWidget);
    setWindowState(Qt::WindowMaximized);
}

void SpriteCreator::makeSpriteList()
{
    listArea=new QScrollArea();
    QWidget* listWidget=new QWidget();

    QVBoxLayout* layout=new QVBoxLayout();

    QMap<QString,Sprite* > spriteBox=SpriteManager::instance()->getSpriteBox();
    QMap<QString,Sprite*>::const_iterator i = spriteBox.constBegin();
    while (i != spriteBox.constEnd()) {
        QCommandLinkButton* button=new QCommandLinkButton();
        button->setText(i.key());
        layout->addWidget(button);

        ++i;
    }
    listWidget->setLayout(layout);
    listArea->setWidget(listWidget);

}

void SpriteCreator::makeTotalSpriteLabel()
{
    totalNumberLayout=new QHBoxLayout();
    QLabel* totalNumberLabel=new QLabel();
    totalNumberLabel->setText("sprite总数:");
    QTextEdit* totalNumberTextEdit=new QTextEdit();
    int totalNumber=SpriteManager::instance()->getTotalSpriteNumber();
    totalNumberTextEdit->setText(QString::number(totalNumber));
    totalNumberTextEdit->setMaximumHeight(25);
    totalNumberTextEdit->setEnabled(false);

    totalNumberLayout->addWidget(totalNumberLabel);
    totalNumberLayout->addWidget(totalNumberTextEdit);
}

void SpriteCreator::makeButton()
{
    buttonLayout=new QVBoxLayout();
    QPushButton* chooseButton=new QPushButton();
    chooseButton->setText("修改Sprite");
    QPushButton* newSpriteButton=new QPushButton();
    newSpriteButton->setText("新建Sprite");
    QPushButton* quitButton=new QPushButton();
    quitButton->setText("退出");

    buttonLayout->addWidget(chooseButton);
    buttonLayout->addWidget(newSpriteButton);
    buttonLayout->addWidget(quitButton);

    connect(quitButton,SIGNAL(clicked(bool)),this,SLOT(close()));
}







