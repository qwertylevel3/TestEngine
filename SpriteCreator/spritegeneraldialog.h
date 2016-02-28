#ifndef SPRITEGENERALDIALOG_H
#define SPRITEGENERALDIALOG_H

#include <QDialog>

namespace Ui {
class SpriteGeneralDialog;
}

class SpriteGeneralDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SpriteGeneralDialog(QWidget *parent = 0);
    ~SpriteGeneralDialog();
    void setPictureName(const QString& p);
    void paintEvent(QPaintEvent* event);
    QString getSpriteName();
    int getSpriteTotalActionNumber();
    int getSpriteWidth();
    int getSpriteHeight();

    QString getPictureName() const;

private slots:
    void cutV();
    void cutH();
private:
    Ui::SpriteGeneralDialog *ui;
    QPixmap* pixmap;
    QString pictureName;
};

#endif // SPRITEGENERALDIALOG_H
