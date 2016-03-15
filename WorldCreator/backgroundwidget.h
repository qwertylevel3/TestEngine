#ifndef BACKGROUNDWIDGET_H
#define BACKGROUNDWIDGET_H

#include"stable.h"

class BackgroundWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BackgroundWidget(QWidget *parent = 0);

signals:
    void setBackground(QString backgroundName);
public slots:
    void sendSetBackground();
protected:
    QListWidget* listWidget;
    QPushButton* setButton;
};

#endif // BACKGROUNDWIDGET_H
