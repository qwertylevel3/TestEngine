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

private:
    Ui::SpriteDetailDialog *ui;
};

#endif // SPRITEDETAILDIALOG_H
