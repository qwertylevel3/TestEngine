#ifndef PICTURETEXT_H
#define PICTURETEXT_H

#include"stable.h"

class PictureText
{
public:
    PictureText();
    void writeToImage(QImage& image);

    QColor getTextColor() const;
    void setTextColor(const QColor &value);

    QFont getTextFont() const;
    void setTextFont(const QFont &value);

    QRect getTextRect() const;
    void setTextRect(const QRect &value);

    Qt::Alignment getTextAlignment() const;
    void setTextAlignment(const Qt::Alignment &value);


    QString getContent() const;
    void setContent(const QString &value);

protected:
    QColor textColor;
    QFont textFont;
    QRect textRect;
    Qt::Alignment textAlignment;

    QString content;

};

#endif // PICTURETEXT_H
