#ifndef BACKGROUNDWIDGET_H
#define BACKGROUNDWIDGET_H

#include"stable.h"

class BackgroundWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BackgroundWidget(QWidget *parent = 0);

signals:

public slots:
protected:
    QListWidget* listWidget;
    QPushButton* addButton;
};

#endif // BACKGROUNDWIDGET_H
