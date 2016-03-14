#include "decorationwidget.h"
#include"decorationmanager.h"


DecorationWidget::DecorationWidget(QWidget *parent) : QListWidget(parent)
{
    QMap<QString,Decoration* > decorationBox=DecorationManager::instance()->getDecorationBox();
    QMap<QString,Decoration*>::const_iterator i = decorationBox.constBegin();
    while (i != decorationBox.constEnd()) {
        new QListWidgetItem(i.key(),this);

        ++i;
    }
}

