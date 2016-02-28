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
void SpriteDetailDialog::setSpriteWidth(int value)
{
    spriteWidth = value;
}
void SpriteDetailDialog::setSpriteHeight(int value)
{
    spriteHeight = value;
}
void SpriteDetailDialog::setSpriteName(const QString &value)
{
    spriteName = value;
}




