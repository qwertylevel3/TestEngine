#include "characterwidget.h"
#include"charactermanager.h"

CharacterWidget::CharacterWidget(QWidget *parent) : QWidget(parent)
{
    listWidget=new QListWidget();
    addButton=new QPushButton();
    addButton->setText("add");
    QVBoxLayout* layout=new QVBoxLayout();


    QMap<QString,Character* > characterBox=CharacterManager::instance()->getCharacterBox();
    QMap<QString,Character*>::const_iterator i = characterBox.constBegin();
    while (i != characterBox.constEnd()) {

        new QListWidgetItem(i.key(),listWidget);
        ++i;
    }

    layout->addWidget(listWidget);
    layout->addWidget(addButton);

    this->setLayout(layout);

    connect(addButton,SIGNAL(clicked(bool)),this,SLOT(sendAddCharacter()));
}

void CharacterWidget::sendAddCharacter()
{
    QListWidgetItem* item=listWidget->currentItem();
    if(item)
    {
        emit addCharacter(item->text());
    }
}

