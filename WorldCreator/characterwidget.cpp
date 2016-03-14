#include "characterwidget.h"
#include"charactermanager.h"

CharacterWidget::CharacterWidget(QWidget *parent) : QListWidget(parent)
{
    QMap<QString,Character* > characterBox=CharacterManager::instance()->getCharacterBox();
    QMap<QString,Character*>::const_iterator i = characterBox.constBegin();
    while (i != characterBox.constEnd()) {

        new QListWidgetItem(i.key(),this);
        ++i;
    }
}

