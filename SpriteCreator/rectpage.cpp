#include "rectpage.h"
#include "ui_rectpage.h"

RectPage::RectPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RectPage)
{
    ui->setupUi(this);
}

RectPage::~RectPage()
{
    delete ui;
}

int RectPage::getRectX()
{
    return ui->xSpinBox->value();
}

int RectPage::getRectY()
{
    return ui->ySpinBox->value();
}

int RectPage::getRectWidth()
{
    return ui->widthSpinBox->value();
}

int RectPage::getRectHeight()
{
    return ui->heightSpinBox->value();
}
