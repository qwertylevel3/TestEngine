#ifndef RECTPAGE_H
#define RECTPAGE_H

#include <QWidget>

namespace Ui {
class RectPage;
}

class RectPage : public QWidget
{
    Q_OBJECT

public:
    explicit RectPage(QWidget *parent = 0);
    ~RectPage();

    int getRectX();
    int getRectY();
    int getRectWidth();
    int getRectHeight();
private:
    Ui::RectPage *ui;
};

#endif // RECTPAGE_H
