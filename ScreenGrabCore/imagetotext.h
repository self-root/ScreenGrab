#ifndef IMAGETOTEXT_H
#define IMAGETOTEXT_H

#include <QObject>
#include <QImage>

#include "ScreenGrabCore_global.h"
struct Pix;
class SCREENGRABCORE_EXPORT ImageToText : public QObject
{
    Q_OBJECT
public:
    ImageToText(QObject *parent=nullptr);
    Pix *qimage2Pix(const QImage &image);

public slots:
    QString extract(const QImage &image_, const QString &model);

signals:
    void textReady(const QString &txt);
    void error(const QString &err);
};

#endif // IMAGETOTEXT_H
