#include "spritecreator.h"
#include"stable.h"

SpriteCreator::SpriteCreator(QWidget *parent) : QMainWindow(parent)
{

    createActions();
    createMenus();

    tabWidget=new QTabWidget(this);

    this->setCentralWidget(tabWidget);

    setWindowState(Qt::WindowMaximized);
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
    openAction=new QAction(tr("&Open"),this);
    openAction->setIcon(QIcon(":/resource/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("打开xml文件"));
    connect(openAction,SIGNAL(triggered(bool)),this,SLOT(open()));

    exitAction=new QAction(tr("&Exit"),this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("退出"));
    connect(exitAction,SIGNAL(triggered(bool)),this,SLOT(close()));

}

void SpriteCreator::createMenus()
{
    fileMenu=menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

}
