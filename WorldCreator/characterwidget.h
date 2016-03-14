#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QWidget>
#include"stable.h"

class CharacterWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit CharacterWidget(QWidget *parent = 0);

signals:

public slots:
};

#endif // CHARACTERWIDGET_H
