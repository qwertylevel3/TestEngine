#include "decorationwidget.h"
#include"decorationmanager.h"


DecorationWidget::DecorationWidget(QWidget *parent) : QScrollArea(parent)
{
    //QScrollArea* listArea=new QScrollArea();

    QVBoxLayout* layout=new QVBoxLayout();
    QWidget* widget=new QWidget();

    QMap<QString,Decoration* > decorationBox=DecorationManager::instance()->getDecorationBox();
    QMap<QString,Decoration*>::const_iterator i = decorationBox.constBegin();
    while (i != decorationBox.constEnd()) {
        QCommandLinkButton* button=new QCommandLinkButton();
        button->setText(i.key());
        layout->addWidget(button);

        ++i;
    }
    //this->setLayout(layout);
    widget->setLayout(layout);
    this->setWidget(widget);
    //this->setGeometry(0,0,200,200);//要显示的区域大小
    //widget->setGeometry(0,0,300,300);
}

