#include "imagetotext.h"

#include <string>
#include <QDebug>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include "utils.h"

ImageToText::ImageToText(QObject *parent)
    : QObject(parent)
{

}

Pix *ImageToText::qimage2Pix(const QImage &image)
{
    Pix * pixs;

    QImage myImage = image.rgbSwapped();
    int width = myImage.width();
    int height = myImage.height();
    int depth = myImage.depth();
    int wpl = myImage.bytesPerLine() / 4;

    pixs = pixCreate(width, height, depth);
    pixSetWpl(pixs, wpl);
    pixSetColormap(pixs, NULL);
    l_uint32 *datas = pixs->data;

    for (int y = 0; y < height; y++) {
        l_uint32 *lines = datas + y * wpl;
        QByteArray a((const char*)myImage.scanLine(y), myImage.bytesPerLine());
        for (int j = 0; j < a.size(); j++) {
            *((l_uint8 *)lines + j) = a[j];
        }
    }

    const qreal toDPM = 1.0 / 0.0254;
    int resolutionX = myImage.dotsPerMeterX() / toDPM;
    int resolutionY = myImage.dotsPerMeterY() / toDPM;

    if (resolutionX < 300) resolutionX = 300;
    if (resolutionY < 300) resolutionY = 300;
    pixSetResolution(pixs, resolutionX, resolutionY);

    return pixEndianByteSwapNew(pixs);
}

QString ImageToText::extract(const QImage &image_, const QString &model)
{
    qDebug() << "[Image To text] extracting with config: " << scrgrab::Utils::modelPath().toStdString().c_str() << " : " << model;
    char *text;
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    if (api->Init(scrgrab::Utils::modelPath().toStdString().c_str(), model.toStdString().c_str()))
    {
        emit error("Failed to initialize tesseract");
        qDebug() << "Failed to initialize tesseract";
        return QString();
    }
    //api->DetectOrientationScript()
    qDebug() << "[Image To text] Qimage to Pix";
    Pix *image = qimage2Pix(image_);
    qDebug() << "[Image To text] Qimage to Pix done";
    api->SetImage(image);
    text = api->GetUTF8Text();
    qDebug() << "[Image To text] Text extraction Done";
    //emit textReady(text);
    QString resultText(text);

    api->End();
    delete api;
    delete[] text;
    return resultText;
}
