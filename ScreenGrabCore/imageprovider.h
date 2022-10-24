#ifndef IMAGEPROVIDER_H
#define IMAGEPROVIDER_H

#include <QQuickImageProvider>
#include <QMutex>
#include <QMutexLocker>
#include <QtConcurrent>

#include "imagetotext.h"
#include "ScreenGrabCore_global.h"

class SCREENGRABCORE_EXPORT ImageProvider : public QQuickImageProvider
{
    Q_OBJECT
public:
    ImageProvider();

    virtual QPixmap requestPixmap(const QString &id, QSize *size, const QSize& requestedSize) override;
    virtual QImage requestImage(const QString &id, QSize *size, const QSize& requestedSize) override;

    QImage &getImage();
    QImage image;
    QImage processed;

public slots:
    void setImage(const QImage &image_);
    void extractText(const QString &lang);
    void rotate(int angle);
    void onImageRotated();
    void aboutToRotate(int initialAngle);
private slots:
    void onTextExtracted();

private:

    ImageToText *imageToText;
    QMutex mutex;
    QFutureWatcher<QImage> rotationFutureWatcher;
    QFutureWatcher<QString> extractionFutureWatcher;
    int previousAngle = 0;

signals:
    void imageTextReady(const QString &text);
    void startExtraction(const QImage &image_, const QString &model);
    void rotateImage(int angle, const QImage &image);
};

#endif // IMAGEPROVIDER_H
