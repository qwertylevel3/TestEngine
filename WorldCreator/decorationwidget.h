#ifndef DECORATIONWIDGET_H
#define DECORATIONWIDGET_H

#include"stable.h"
#include <QWidget>

class DecorationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DecorationWidget(QWidget *parent = 0);

signals:
    void addDecoration(QString decorationName);
public slots:
    void sendAddDecoration();
protected:
    QListWidget* listWidget;
    QPushButton* addButton;
};

#endif // DECORATIONWIDGET_H
