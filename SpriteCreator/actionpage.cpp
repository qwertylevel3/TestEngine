#include "actionpage.h"
#include "ui_actionpage.h"
#include"framepage.h"

ActionPage::ActionPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ActionPage)
{
    ui->setupUi(this);
    connect(ui->totalFrameNumberSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setFramePage(int)));
}

ActionPage::~ActionPage()
{
    delete ui;
}

int ActionPage::getFrameX(int index)
{
    return static_cast<FramePage*>(ui->tabWidget->widget(index))->getFrameX();
}

int ActionPage::getFrameY(int index)
{
     return static_cast<FramePage*>(ui->tabWidget->widget(index))->getFrameY();
}

int ActionPage::getFrameDX(int index)
{
     return static_cast<FramePage*>(ui->tabWidget->widget(index))->getFrameDx();
}

int ActionPage::getFrameDY(int index)
{
    return static_cast<FramePage*>(ui->tabWidget->widget(index))->getFrameDy();
}

QList<QRect> ActionPage::getFrameRect(int index)
{
    return static_cast<FramePage*>(ui->tabWidget->widget(index))->getAllRect();
}


void ActionPage::setFramePage(int n)
{
    for(int i=0;i<ui->tabWidget->count();i++)
    {
        delete ui->tabWidget->widget(i);
    }
    ui->tabWidget->clear();
    for(int i=0;i<n;i++)
    {
        FramePage* framePage=new FramePage();
        ui->tabWidget->addTab(framePage,"frame"+i);
    }
}
