#ifndef CHARACTERWIDGET_H
#define CHARACTERWIDGET_H

#include <QWidget>
#include"stable.h"

class CharacterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CharacterWidget(QWidget *parent = 0);

signals:
    void addCharacter(QString characterName);

public slots:
    void sendAddCharacter();
protected:
    QListWidget* listWidget;
    QPushButton* addButton;
};

#endif // CHARACTERWIDGET_H
