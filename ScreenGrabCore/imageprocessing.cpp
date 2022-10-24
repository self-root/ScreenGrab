#include "imageprocessing.h"

ImageProcessing::ImageProcessing(QImage image, QObject *parent)
    : QObject{parent}, mImage(image)
{

}

void ImageProcessing::rotate(int angle)
{
    QTransform rotation;
    rotation.rotate(angle);
    mImage = mImage.transformed(rotation, Qt::SmoothTransformation);

    cropTranspatentPixels();

}

const QImage &ImageProcessing::image() const
{
    return mImage;
}

void ImageProcessing::setImage(const QImage &newImage)
{
    mImage = newImage;
}

void ImageProcessing::cropTranspatentPixels()
{
    QPoint btmL = getBottomLeft();
    QPoint btmR = getBottomRight();
    QPoint tpR = getTopRight();
    QPoint tpL = getTopLeft();

    QPoint tpLeftCorner = topLeftCorner(tpL, btmL, tpR);
    QPoint btmRightCorner = bottomRightCorner(btmR, btmL, tpR);
    QRect imageRect(tpLeftCorner, btmRightCorner);

    mImage = mImage.copy(imageRect);
}

QPoint ImageProcessing::topLeftCorner(const QPoint &topLeft, const QPoint &bottomLeft, const QPoint topRight)
{
    QPoint t_l;
    if (topLeft.y() < topRight.y())
        t_l.setY(topLeft.y());
    else {
        t_l.setY(topRight.y());
    }

    if (topLeft.x() < bottomLeft.x())
        t_l.setX(topLeft.x());
    else {
        t_l.setX(bottomLeft.x());
    }

    return t_l;
}

QPoint ImageProcessing::bottomRightCorner(const QPoint &bottomRight, const QPoint &bottomLeft, const QPoint &topRight)
{
    QPoint b_l;
    if (bottomRight.x() > topRight.x())
        b_l.setX(bottomLeft.x());
    else
        b_l.setX(topRight.x());

    if (bottomRight.y() > bottomLeft.y())
        b_l.setY(bottomRight.y());
    else
        b_l.setY(bottomLeft.y());

    return b_l;
}

QPoint ImageProcessing::getBottomLeft()
{
    for (int w = 0; w < mImage.width(); w++)
    {
        for (int h = 0; h<mImage.height(); h++)
        {
            if (mImage.pixel(w, h)>0)
            {
                return QPoint(w, h);
            }
        }
    }
    return QPoint();
}

QPoint ImageProcessing::getBottomRight()
{
    for (int h = mImage.height() - 1; h > 0; h--)
    {
        for (int w = mImage.width() -1; w > 0 ; w--)
        {
            if (mImage.pixel(w, h) >0)
            {
                return QPoint(w, h);
            }
        }
    }
    return QPoint();
}

QPoint ImageProcessing::getTopRight()
{
    for (int w = mImage.width() - 1; w > 0; w--)
    {
        for (int h = mImage.height() - 1; h > 0 ; h--)
        {
            if (qAlpha(mImage.pixel(w, h)) >0)
            {
                return QPoint(w, h);
            }
        }
    }
    return QPoint();
}

QPoint ImageProcessing::getTopLeft()
{
    for (int h = 0; h < mImage.height(); h++)
    {
        for (int w = 0; w<mImage.width(); w++)
        {
            if (qAlpha(mImage.pixel(w, h))>0)
            {
                return QPoint(w, h);
            }
        }
    }
    return QPoint();
}
