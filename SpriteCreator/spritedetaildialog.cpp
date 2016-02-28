#include "spritedetaildialog.h"
#include "ui_spritedetaildialog.h"
#include"actionpage.h"

SpriteDetailDialog::SpriteDetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpriteDetailDialog)
{
    ui->setupUi(this);


}

SpriteDetailDialog::~SpriteDetailDialog()
{
    delete ui;
}

void SpriteDetailDialog::setTotalActionNumber(int value)
{
    for(int i=0;i<ui->tabWidget->count();i++)
    {
        delete ui->tabWidget->widget(i);
    }
    ui->tabWidget->clear();
    totalActionNumber = value;
    for(int i=0;i<value;i++)
    {
        ActionPage* actionPage=new ActionPage();
        ui->tabWidget->addTab(actionPage,"action"+QString::number(i));
    }
}

QString SpriteDetailDialog::getActionName(int index)
{
    return static_cast<ActionPage*>(ui->tabWidget->widget(index))->getActionName();
}

int SpriteDetailDialog::getFrameDelay(int index)
{
     return static_cast<ActionPage*>(ui->tabWidget->widget(index))->getFrameDelay();
}

int SpriteDetailDialog::getFrameTotal(int index)
{
      return static_cast<ActionPage*>(ui->tabWidget->widget(index))->getFrameTotal();
}

bool SpriteDetailDialog::getIsRepeat(int index)
{
    return static_cast<ActionPage*>(ui->tabWidget->widget(index))->getIsRepeat();
}

int SpriteDetailDialog::getRepeatStart(int index)
{
    return static_cast<ActionPage*>(ui->tabWidget->widget(index))->getRepeatStart();
}

int SpriteDetailDialog::getRepeatOver(int index)
{
    return static_cast<ActionPage*>(ui->tabWidget->widget(index))->getRepeatOver();
}

int SpriteDetailDialog::getFrameX(int actionIndex, int frameIndex)
{
    return static_cast<ActionPage*>(ui->tabWidget->widget(actionIndex))->getFrameX(frameIndex);
}

int SpriteDetailDialog::getFrameY(int actionIndex, int frameIndex)
{
    return static_cast<ActionPage*>(ui->tabWidget->widget(actionIndex))->getFrameY(frameIndex);
}

int SpriteDetailDialog::getFrameDX(int actionIndex, int frameIndex)
{
    return static_cast<ActionPage*>(ui->tabWidget->widget(actionIndex))->getFrameDX(frameIndex);
}

int SpriteDetailDialog::getFrameDY(int actionIndex, int frameIndex)
{
    return static_cast<ActionPage*>(ui->tabWidget->widget(actionIndex))->getFrameDY(frameIndex);
}

int SpriteDetailDialog::getFrameTotal(int actionIndex, int frameIndex)
{
    return static_cast<ActionPage*>(ui->tabWidget->widget(actionIndex))->getFrameTotal(frameIndex);
}

QList<QRect> SpriteDetailDialog::getFrameRect(int actionIndex, int frameIndex)
{
    return static_cast<ActionPage*>(ui->tabWidget->widget(actionIndex))->getFrameRect(frameIndex);
}
