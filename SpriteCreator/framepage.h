#ifndef FRAMEPAGE_H
#define FRAMEPAGE_H

#include <QWidget>

namespace Ui {
class FramePage;
}

class FramePage : public QWidget
{
    Q_OBJECT
public:
    explicit FramePage(QWidget *parent = 0);
    ~FramePage();
    int getFrameX();
    int getFrameY();
    int getFrameDx();
    int getFrameDy();
    int getTotalRectNumber();
    QList<QRect> getAllRect();

private slots:
    void setRectPage(int n);
private:
    Ui::FramePage *ui;
};

#endif // FRAMEPAGE_H
