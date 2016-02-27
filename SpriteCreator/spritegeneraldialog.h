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

private:
    Ui::SpriteGeneralDialog *ui;
};

#endif // SPRITEGENERALDIALOG_H
