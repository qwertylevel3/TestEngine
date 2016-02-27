#include "spritegeneraldialog.h"
#include "ui_spritegeneraldialog.h"

SpriteGeneralDialog::SpriteGeneralDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpriteGeneralDialog)
{
    ui->setupUi(this);
}

SpriteGeneralDialog::~SpriteGeneralDialog()
{
    delete ui;
}
