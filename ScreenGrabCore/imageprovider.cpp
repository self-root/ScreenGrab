#include "imageprovider.h"
#include <QThreadPool>
#include "imageprocessing.h"


ImageProvider::ImageProvider()
    : QQuickImageProvider(QQuickImageProvider::Pixmap)
{
    imageToText = new ImageToText;
    connect(&rotationFutureWatcher, &QFutureWatcher<QImage>::finished, this, &ImageProvider::onImageRotated);
    connect(&extractionFutureWatcher, &QFutureWatcher<QString>::finished, this, &ImageProvider::onTextExtracted);
}

QPixmap ImageProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size)
    Q_UNUSED(requestedSize)
    if (id == "newimage")
        return QPixmap::fromImage(image);

    QPixmap img(id);
    return img;
}

QImage ImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    Q_UNUSED(size)
    Q_UNUSED(requestedSize)
    if (id == "newimage")
        return image;

    QImage img(id);
    qDebug() << "Image: " << img.width() << "x" << img.height();
    return img;
}

QImage &ImageProvider::getImage()
{
    return image;
}


void ImageProvider::setImage(const QImage &image_)
{
    qDebug() << "[Image Provider] set image...";
    image = image_;
    processed = QImage();
}

void ImageProvider::extractText(const QString &lang)
{
    if (lang.isEmpty())
        return;
    qDebug() << "[Image Provider] Start text extraction";
    //emit startExtraction(image, lang);
    QMutexLocker locker(&mutex);
    QFuture<QString> res = QtConcurrent::run([&, this](){
        /*if (processed.isNull())
        {
            // implement image processing to enhance result
            processed.save("/home/linus/grayscaled.png");
        }*/
        QString result = imageToText->extract(image, lang);

        return result;
    });

    extractionFutureWatcher.setFuture(res);
}

void ImageProvider::rotate(int angle)
{
    if (previousAngle == angle)
        return;
    if (rotationFutureWatcher.isRunning())
        return;
    QMutexLocker locker(&mutex);

    QFuture<QImage> res = QtConcurrent::run([&, this](){
        ImageProcessing processing(image);
        processing.rotate(angle);

        return processing.image();

    });
    rotationFutureWatcher.setFuture(res);
}

void ImageProvider::onImageRotated()
{
    QMutexLocker locker(&mutex);
    image = rotationFutureWatcher.result();
    qDebug() << "Image rotated: " << image.size();
}

void ImageProvider::aboutToRotate(int initialAngle)
{
    previousAngle = initialAngle;
}

void ImageProvider::onTextExtracted()
{
    emit imageTextReady(extractionFutureWatcher.result());
}


// only image provider to extract text and provide image to the ImageView.qml whatever the source
// Extract text after each setImage()
