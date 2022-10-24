#include "image.h"

Image::Image(QObject *parent)
    : QObject{parent}
{

}

Image::Image(int imageId, const QString &imagePath, const QString &imageText, const QDateTime &savedDate)
    : mImageId(imageId), mImagePath(imagePath), mImageText(imageText), mSavedDate(savedDate)
{

}

Image::Image(const QString &imagePath, const QString &imageText)
    : mImagePath(imagePath), mImageText(imageText)
{
}

int Image::imageId() const
{
    return mImageId;
}

void Image::setImageId(int newImageId)
{
    mImageId = newImageId;
    emit imageIdChanged();
}

const QString &Image::imagePath() const
{
    return mImagePath;
}

void Image::setImagePath(const QString &newImagePath)
{
    mImagePath = newImagePath;
    setImageProviderPath("image://provider/" + newImagePath);
    emit imagePathChanged();
}

const QString &Image::imageText() const
{
    return mImageText;
}

void Image::setImageText(const QString &newImageText)
{
    mImageText = newImageText;
    emit imageTextChanged();
}

const QDateTime &Image::savedDate() const
{
    return mSavedDate;
}

void Image::setSavedDate(const QDateTime &newSavedDate)
{
    mSavedDate = newSavedDate;
    emit savedDateChanged();
}

const QString &Image::imageProviderPath() const
{
    return mImageProviderPath;
}

void Image::setImageProviderPath(const QString &newImageProviderPath)
{
    mImageProviderPath = newImageProviderPath;
}

void Image::clear(Image *image)
{
    image->setImageId(-1);
    image->setImagePath("");
    image->setImageText("");
    image->setSavedDate(QDateTime());
}
