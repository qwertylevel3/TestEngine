#include "backgroundwidget.h"
#include"backgroundmanager.h"

BackgroundWidget::BackgroundWidget(QWidget *parent) : QWidget(parent)
{
    listWidget=new QListWidget();
    setButton=new QPushButton();
    setButton->setText("set");
    QVBoxLayout* layout=new QVBoxLayout();

    QMap<QString,Background* > backgroundBox=BackgroundManager::instance()->getBackgroundBox();
    QMap<QString,Background*>::const_iterator i = backgroundBox.constBegin();
    while (i != backgroundBox.constEnd()) {
        new QListWidgetItem(i.key(),listWidget);
        ++i;
    }

    layout->addWidget(listWidget);
    layout->addWidget(setButton);

    this->setLayout(layout);

    connect(setButton,SIGNAL(clicked(bool)),this,SLOT(sendSetBackground()));
}

void BackgroundWidget::sendSetBackground()
{
    QListWidgetItem* item=listWidget->currentItem();
    if(item)
    {
        emit setBackground(item->text());
    }
}

