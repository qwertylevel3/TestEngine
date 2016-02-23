#include "picturetext.h"

PictureText::PictureText()
{
    textColor=Qt::white;
    textAlignment=Qt::AlignCenter;
    textFont=QFont("Arial", 30);
}

void PictureText::writeToImage(QImage &image)
{
    textRect=QRect(0,0,image.width(),image.height());

    QPainter p;

    p.begin(&image);
    p.setPen(textColor);
    p.setFont(textFont);
    p.drawText(textRect,textAlignment,content);
    p.end();
}
QColor PictureText::getTextColor() const
{
    return textColor;
}

void PictureText::setTextColor(const QColor &value)
{
    textColor = value;
}
QFont PictureText::getTextFont() const
{
    return textFont;
}

void PictureText::setTextFont(const QFont &value)
{
    textFont = value;
}
QRect PictureText::getTextRect() const
{
    return textRect;
}

void PictureText::setTextRect(const QRect &value)
{
    textRect = value;
}
Qt::Alignment PictureText::getTextAlignment() const
{
    return textAlignment;
}

void PictureText::setTextAlignment(const Qt::Alignment &value)
{
    textAlignment = value;
}
QString PictureText::getContent() const
{
    return content;
}

void PictureText::setContent(const QString &value)
{
    content = value;
}






