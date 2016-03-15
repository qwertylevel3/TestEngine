#include "decorationwidget.h"
#include"decorationmanager.h"


DecorationWidget::DecorationWidget(QWidget *parent) : QWidget(parent)
{
    listWidget=new QListWidget();
    addButton=new QPushButton();
    addButton->setText("add");
    QVBoxLayout* layout=new QVBoxLayout();


    QMap<QString,Decoration* > decorationBox=DecorationManager::instance()->getDecorationBox();
    QMap<QString,Decoration*>::const_iterator i = decorationBox.constBegin();
    while (i != decorationBox.constEnd()) {
        new QListWidgetItem(i.key(),listWidget);

        ++i;
    }

    layout->addWidget(listWidget);
    layout->addWidget(addButton);

    this->setLayout(layout);

    connect(addButton,SIGNAL(clicked(bool)),this,SLOT(sendAddDecoration()));

}

void DecorationWidget::sendAddDecoration()
{
    QListWidgetItem* item=listWidget->currentItem();
    if(item)
    {
        emit addDecoration(item->text());
    }
}

