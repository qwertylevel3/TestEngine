#include "spritedetaildialog.h"
#include "ui_spritedetaildialog.h"

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
