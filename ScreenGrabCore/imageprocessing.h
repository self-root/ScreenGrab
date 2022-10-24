#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include <QImage>

#include "ScreenGrabCore_global.h"

class SCREENGRABCORE_EXPORT ImageProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcessing(QImage image, QObject *parent = nullptr);

    void rotate(int angle);

    const QImage &image() const;
    void setImage(const QImage &newImage);

    void cropTranspatentPixels();

private:
    QImage mImage;

    QPoint topLeftCorner(const QPoint &topLeft, const QPoint &bottomLeft, const QPoint topRight);
    QPoint bottomRightCorner(const QPoint &bottomRight, const QPoint &bottomLeft, const QPoint &topRight);

    QPoint getBottomLeft();
    QPoint getBottomRight();
    QPoint getTopRight();
    QPoint getTopLeft();

};

#endif // IMAGEPROCESSING_H
