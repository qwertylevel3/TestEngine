#include "spritegeneraldialog.h"
#include "ui_spritegeneraldialog.h"
#include"stable.h"

SpriteGeneralDialog::SpriteGeneralDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpriteGeneralDialog)
{
    ui->setupUi(this);
    ui->hShardNumberSpinBox->setValue(1);
    ui->vShardNumberSpinBox->setValue(1);

    connect(ui->vShardNumberSpinBox,SIGNAL(valueChanged(int)),this,SLOT(cutV()));
    connect(ui->hShardNumberSpinBox,SIGNAL(valueChanged(int)),this,SLOT(cutH()));

}

SpriteGeneralDialog::~SpriteGeneralDialog()
{
    delete ui;
}

void SpriteGeneralDialog::setPicturePath(const QString &p)
{
    picturePath=p;
    pixmap=new QPixmap(picturePath);
    ui->pictureLabel->setScaledContents(true);

    ui->pictureLabel->setPixmap(*pixmap);
    ui->pictureWidthTextEdit->setText(QString::number(pixmap->width()));
    ui->pictureHeightTextEdit->setText(QString::number(pixmap->height()));
}

void SpriteGeneralDialog::paintEvent(QPaintEvent *event)
{
    QDialog::paintEvent(event);
}

QString SpriteGeneralDialog::getSpriteName()
{
    return ui->spriteNameTextEdit->toPlainText();
}

int SpriteGeneralDialog::getSpriteTotalActionNumber()
{
    return ui->totalActionNumberSpinBox->value();
}

int SpriteGeneralDialog::getSpriteWidth()
{
    return ui->spriteWidthSpinBox->value();
}

int SpriteGeneralDialog::getSpriteHeight()
{
    return ui->spriteHeightSpinBox->value();
}

void SpriteGeneralDialog::cutV()
{
    QPainter painter;
    int vNumber=ui->vShardNumberSpinBox->value();
    if(vNumber==0)
        return;

    QPixmap * p=new QPixmap(*pixmap);

    painter.begin(p);
    int offset=p->height()/vNumber;
    for(int i=0;i<vNumber;i++)
    {
        painter.drawLine(0,i*offset,p->width(),i*offset);
    }
    painter.end();

    ui->afterShardHeightTextEdit->setText(QString::number(p->height()/vNumber));
    ui->pictureLabel->setPixmap(*p);
}

void SpriteGeneralDialog::cutH()
{
    QPainter painter;
    int hNumber=ui->hShardNumberSpinBox->value();
    if(hNumber==0)
        return;

    QPixmap * p=new QPixmap(*pixmap);

    painter.begin(p);

    int offset=p->width()/hNumber;
    for(int i=0;i<hNumber;i++)
    {
        painter.drawLine(i*offset,0,i*offset,p->height());
    }
    painter.end();

    ui->afterShardWidthTextEdit->setText(QString::number(p->width()/hNumber));
    ui->pictureLabel->setPixmap(*p);
}
QString SpriteGeneralDialog::getPicturePath() const
{
    return picturePath;
}

QString SpriteGeneralDialog::getPictureName() const
{

    int len=picturePath.length()-QDir::currentPath().length();
    QString pictureName=picturePath.right(len);

    return pictureName;


}

