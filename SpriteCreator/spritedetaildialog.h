#ifndef SPRITEDETAILDIALOG_H
#define SPRITEDETAILDIALOG_H

#include <QDialog>

namespace Ui {
class SpriteDetailDialog;
}

class SpriteDetailDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SpriteDetailDialog(QWidget *parent = 0);
    ~SpriteDetailDialog();

    void setTotalActionNumber(int value);

    QString getActionName(int index);
    int getFrameDelay(int index);
    int getFrameTotal(int index);
    bool getIsRepeat(int index);
    int getRepeatStart(int index);
    int getRepeatOver(int index);

    int getFrameX(int actionIndex,int frameIndex);
    int getFrameY(int actionIndex,int frameIndex);
    int getFrameDX(int actionIndex,int frameIndex);
    int getFrameDY(int actionIndex,int frameIndex);
    int getFrameTotal(int actionIndex,int frameIndex);
    QList<QRect> getFrameRect(int actionIndex,int frameIndex);
private:
    Ui::SpriteDetailDialog *ui;
    int totalActionNumber;
};

#endif // SPRITEDETAILDIALOG_H
