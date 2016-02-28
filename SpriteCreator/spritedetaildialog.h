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
    void setSpriteWidth(int value);
    void setSpriteHeight(int value);
    void setSpriteName(const QString &value);

private:
    Ui::SpriteDetailDialog *ui;
    QString spriteName;
    int totalActionNumber;
    int spriteWidth;
    int spriteHeight;
};

#endif // SPRITEDETAILDIALOG_H
