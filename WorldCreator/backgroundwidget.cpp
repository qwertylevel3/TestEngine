#include "backgroundwidget.h"
#include"backgroundmanager.h"

BackgroundWidget::BackgroundWidget(QWidget *parent) : QListWidget(parent)
{
    QMap<QString,Background* > backgroundBox=BackgroundManager::instance()->getBackgroundBox();
    QMap<QString,Background*>::const_iterator i = backgroundBox.constBegin();
    while (i != backgroundBox.constEnd()) {
        new QListWidgetItem(i.key(),this);

        ++i;
    }
}

