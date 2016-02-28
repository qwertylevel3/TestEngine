#include "framepage.h"
#include "ui_framepage.h"
#include"rectpage.h"

FramePage::FramePage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FramePage)
{
    ui->setupUi(this);

    connect(ui->totalRectNumberSpinBox,SIGNAL(valueChanged(int)),this,SLOT(setRectPage(int)));
}

FramePage::~FramePage()
{
    delete ui;
}

int FramePage::getFrameX()
{
    return ui->xSpinBox->value();
}

int FramePage::getFrameY()
{
    return ui->ySpinBox->value();
}

int FramePage::getFrameDx()
{
    return ui->dxSpinBox->value();
}

int FramePage::getFrameDy()
{
    return ui->dySpinBox->value();
}

int FramePage::getTotalRectNumber()
{
    return ui->totalRectNumberSpinBox->value();
}

QList<QRect> FramePage::getAllRect()
{
    QList<QRect> list;
    for(int i=0;i<ui->tabWidget->count();i++)
    {
        RectPage* r=static_cast<RectPage*>(ui->tabWidget->widget(i));
        list.push_back(QRect(r->getRectX()
                             ,r->getRectY()
                             ,r->getRectWidth()
                             ,r->getRectHeight()));
    }
    return list;
}

void FramePage::setRectPage(int n)
{
    for(int i=0;i<ui->tabWidget->count();i++)
    {
        delete ui->tabWidget->widget(i);
    }
    ui->tabWidget->clear();
    for(int i=0;i<n;i++)
    {
        RectPage* rectPage=new RectPage();
        ui->tabWidget->addTab(rectPage,"rect"+i);
    }
}
