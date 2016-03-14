#include "characterwidget.h"
#include"charactermanager.h"

CharacterWidget::CharacterWidget(QWidget *parent) : QScrollArea(parent)
{
    //QScrollArea* listArea=new QScrollArea();

    QVBoxLayout* layout=new QVBoxLayout();
    QWidget* widget=new QWidget();

    QMap<QString,Character* > characterBox=CharacterManager::instance()->getCharacterBox();
    QMap<QString,Character*>::const_iterator i = characterBox.constBegin();
    while (i != characterBox.constEnd()) {
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

