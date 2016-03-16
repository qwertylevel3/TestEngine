#include "spritecreator.h"
#include"stable.h"
#include"spritemanager.h"
#include"picturemanager.h"
#include"spritegeneraldialog.h"
#include"spritedetaildialog.h"

SpriteButton::SpriteButton(QWidget *parent) : QCommandLinkButton(parent)
{

    connect(this,SIGNAL(clicked(bool)),this,SLOT(sendSpriteName()));
}

void SpriteButton::sendSpriteName()
{
    emit spriteName(this->text());
}


SpriteCreator::SpriteCreator(QWidget *parent) : QMainWindow(parent)
{
    generalDialog=0;
    detailDialog=0;
    makeUI();
}

void SpriteCreator::save()
{

}

void SpriteCreator::setSprite(const QString &spriteName)
{
//    currentSpriteName=spriteName;
//    Sprite* sprite=SpriteManager::instance()->getSprite(spriteName);
//    openglWidget->setSprite(sprite);
}

void SpriteCreator::editSprite()
{

}

void SpriteCreator::newSprite()
{
    QString fileName=QFileDialog::getOpenFileName(this,
                                                  tr("打开png图片"),".",
                                                  tr("png files(*.png)"));
    if(!fileName.isEmpty())
    {
        if(generalDialog!=0)
        {
            delete generalDialog;
        }
        generalDialog = new SpriteGeneralDialog(this);

        //TODO....pictureName
       // int len=fileName.length()-QDir::currentPath().length();
       // QString pictureName=pictureName=fileName.right(len);



        generalDialog->setPicturePath(fileName);
        if(generalDialog->exec())
        {
            detailDialog = new SpriteDetailDialog(this);
            detailDialog->setTotalActionNumber(generalDialog->getSpriteTotalActionNumber());

            if(detailDialog->exec())
            {
                Sprite* sprite=makeNewSpriteInstance();
                SpriteManager::instance()->addSprite(sprite);

                updateSpriteList();

                qDebug()<<SpriteManager::instance()->getTotalSpriteNumber()<<endl;
            }

        }
    }
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

void SpriteCreator::createActions()
{
//    openAction=new QAction(tr("&Open"),this);
//    openAction->setIcon(QIcon(":/resource/open.png"));
//    openAction->setShortcut(QKeySequence::Open);
//    openAction->setStatusTip(tr("打开图片"));
//    connect(openAction,SIGNAL(triggered(bool)),this,SLOT(open()));

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
//    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
}

void SpriteCreator::makeUI()
{
    createActions();
    createMenus();


    QWidget* mainWidget=new QWidget();

    hLayout=new QHBoxLayout();
    vLayout=new QVBoxLayout();


    makeTotalSpriteLabel();
    makeButton();

    vLayout->addLayout(totalNumberLayout);
    openglWidget=new OpenglWidget(this);
    vLayout->addWidget(openglWidget);
    //vLayout->addStretch();
    vLayout->addLayout(buttonLayout);

    makeSpriteList();
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
        SpriteButton* button=new SpriteButton();
        button->setText(i.key());
        layout->addWidget(button);

        connect(button,SIGNAL(spriteName(QString)),this,SLOT(setSprite(QString)));

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

    connect(chooseButton,SIGNAL(clicked(bool)),this,SLOT(editSprite()));

    QPushButton* newSpriteButton=new QPushButton();
    newSpriteButton->setText("新建Sprite");

    connect(newSpriteButton,SIGNAL(clicked(bool)),this,SLOT(newSprite()));

    QPushButton* quitButton=new QPushButton();
    quitButton->setText("退出");

    buttonLayout->addWidget(chooseButton);
    buttonLayout->addWidget(newSpriteButton);
    buttonLayout->addWidget(quitButton);

    connect(quitButton,SIGNAL(clicked(bool)),this,SLOT(close()));
}

void SpriteCreator::updateSpriteList()
{
    hLayout->removeWidget(listArea);
    hLayout->removeItem(vLayout);
    delete listArea;
    makeSpriteList();
    hLayout->addWidget(listArea);
    hLayout->addLayout(vLayout);

}

Sprite *SpriteCreator::makeNewSpriteInstance()
{
    Sprite* sprite=new Sprite();
    sprite->setName(generalDialog->getSpriteName());
    sprite->setTotalActionNumber(generalDialog->getSpriteTotalActionNumber());
    sprite->setWidth(generalDialog->getSpriteWidth());
    sprite->setHeight(generalDialog->getSpriteHeight());

    for(int i=0;i<sprite->getTotalActionNumber();i++)
    {
        Action* action=makeNewSpriteActionInstance(i);
        sprite->addAction(action);
    }
    return sprite;
}

Action* SpriteCreator::makeNewSpriteActionInstance(int index)
{
    Action* action=new Action();

    action->setName(detailDialog->getActionName(index));
    action->setFrameDelay(detailDialog->getFrameDelay(index));
    action->setFrameTotal(detailDialog->getFrameTotal(index));
    action->setRepeat(detailDialog->getIsRepeat(index));
    action->setRepeatStart(detailDialog->getRepeatStart(index));
    action->setRepeatOver(detailDialog->getRepeatOver(index));

    for(int i=0;i<action->getFrameTotal();i++)
    {
        Frame* frame=makeNewSpriteFrameInstance(index,i);
        action->addFrame(frame);
    }
    return action;

}

Frame *SpriteCreator::makeNewSpriteFrameInstance(int actionIndex, int frameIndex)
{
    int x=detailDialog->getFrameX(actionIndex,frameIndex);
    int y=detailDialog->getFrameY(actionIndex,frameIndex);
    int dx=detailDialog->getFrameDX(actionIndex,frameIndex);
    int dy=detailDialog->getFrameDY(actionIndex,frameIndex);
    QRect rect(x,y,dx,dy);

    Frame* frame=new Frame(generalDialog->getPictureName(),rect);

    QList<QRect> list=detailDialog->getFrameRect(actionIndex,frameIndex);
    for(int i=0;i<list.size();i++)
    {
        frame->addRect(list[i]);
    }

    return frame;
}
