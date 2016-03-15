#include "backgroundwidget.h"
#include"backgroundmanager.h"

BackgroundWidget::BackgroundWidget(QWidget *parent) : QWidget(parent)
{
    listWidget=new QListWidget();
    addButton=new QPushButton();
    addButton->setText("add");
    QVBoxLayout* layout=new QVBoxLayout();

    QMap<QString,Background* > backgroundBox=BackgroundManager::instance()->getBackgroundBox();
    QMap<QString,Background*>::const_iterator i = backgroundBox.constBegin();
    while (i != backgroundBox.constEnd()) {
        new QListWidgetItem(i.key(),listWidget);
        ++i;
    }

    layout->addWidget(listWidget);
    layout->addWidget(addButton);

    this->setLayout(layout);

}

