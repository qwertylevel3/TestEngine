#ifndef ACTIONPAGE_H
#define ACTIONPAGE_H

#include <QWidget>

namespace Ui {
class ActionPage;
}

class ActionPage : public QWidget
{
    Q_OBJECT

public:
    explicit ActionPage(QWidget *parent = 0);
    ~ActionPage();
    QString getActionName();
    int getFrameDelay();
    int getFrameTotal();
    bool getIsRepeat();
    int getRepeatStart();
    int getRepeatOver();

    int getFrameX(int index);
    int getFrameY(int index);
    int getFrameDX(int index);
    int getFrameDY(int index);
    int getFrameTotal(int index);
    QList<QRect> getFrameRect(int index);
private slots:
    void setFramePage(int n);
private:
    Ui::ActionPage *ui;
};

#endif // ACTIONPAGE_H
