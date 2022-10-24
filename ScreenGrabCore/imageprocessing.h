#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <QObject>
#include <QImage>

#include "ScreenGrabCore_global.h"
/**
 * @brief The ImageProcessing class
 * Contain some fuction for image processing
 */
class SCREENGRABCORE_EXPORT ImageProcessing : public QObject
{
    Q_OBJECT
public:
    explicit ImageProcessing(QImage image, QObject *parent = nullptr);
    /**
     * @brief rotate: Rotate image an angle provided and remove the blank pixels around the retated image
     * @param angle
     */
    void rotate(int angle);

    const QImage &image() const;
    void setImage(const QImage &newImage);

    /**
     * @brief cropTranspatentPixels
     * Crome the image by removing transparent pixels around it
     */
    void cropTranspatentPixels();

private:
    QImage mImage;

    /**
     * @brief topLeftCorner: Identify the top left corner of the image and return the coordinate of that point to be used to crop the image
     * @param topLeft
     * @param bottomLeft
     * @param topRight
     * @return
     */
    QPoint topLeftCorner(const QPoint &topLeft, const QPoint &bottomLeft, const QPoint topRight);

    /**
     * @brief bottomRightCorner: Identify the bottom right corner of the image and return the coordinate of that point to be used to crop the image
     * @param bottomRight
     * @param bottomLeft
     * @param topRight
     * @return
     */
    QPoint bottomRightCorner(const QPoint &bottomRight, const QPoint &bottomLeft, const QPoint &topRight);

    // The following functions are used to identify the four corner of the image, which are the border between blank pixels and the actual image
    QPoint getBottomLeft();
    QPoint getBottomRight();
    QPoint getTopRight();
    QPoint getTopLeft();

};

#endif // IMAGEPROCESSING_H
