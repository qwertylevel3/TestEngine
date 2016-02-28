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

QString ActionPage::getActionName()
{
    return ui->nameTextEdit->toPlainText();
}

int ActionPage::getFrameDelay()
{
    return ui->frameDelaySpinBox->value();
}

int ActionPage::getFrameTotal()
{
    return ui->frameDelaySpinBox->value();
}

bool ActionPage::getIsRepeat()
{
    return ui->isRepeatCheckBox->isChecked();
}

int ActionPage::getRepeatStart()
{
    return ui->repeatStartSpinBox->value();
}

int ActionPage::getRepeatOver()
{
    return ui->repeatOverSpinBox->value();
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

int ActionPage::getFrameTotal(int index)
{
    return static_cast<FramePage*>(ui->tabWidget->widget(index))->getTotalRectNumber();
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
