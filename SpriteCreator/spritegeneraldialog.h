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
    void setPictureName(const QString& pictureName);
    void paintEvent(QPaintEvent* event);

private slots:
    void cutV();
    void cutH();
private:
    Ui::SpriteGeneralDialog *ui;
    QPixmap* pixmap;
};

#endif // SPRITEGENERALDIALOG_H
