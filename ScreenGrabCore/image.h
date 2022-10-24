#ifndef IMAGE_H
#define IMAGE_H

#include "ScreenGrabCore_global.h"
#include <QObject>
#include <QString>
#include <QDateTime>

class SCREENGRABCORE_EXPORT Image : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int imageId READ imageId WRITE setImageId NOTIFY imageIdChanged)
    Q_PROPERTY(QString imagePath READ imagePath WRITE setImagePath NOTIFY imagePathChanged)
    Q_PROPERTY(QString imageProviderPath READ imageProviderPath WRITE setImageProviderPath NOTIFY imageProviderPathChanged)
    Q_PROPERTY(QString imageText READ imageText WRITE setImageText NOTIFY imageTextChanged)
    Q_PROPERTY(QDateTime savedDate READ savedDate WRITE setSavedDate NOTIFY savedDateChanged)
public:
    explicit Image(QObject *parent = nullptr);
    Image(int imageId, const QString &imagePath, const QString &imageText, const QDateTime &savedDate);
    Image(const QString &imagePath, const QString &imageText);

    int imageId() const;
    void setImageId(int newImageId);

    const QString &imagePath() const;
    void setImagePath(const QString &newImagePath);

    const QString &imageText() const;
    void setImageText(const QString &newImageText);

    const QDateTime &savedDate() const;
    void setSavedDate(const QDateTime &newSavedDate);

    const QString &imageProviderPath() const;
    void setImageProviderPath(const QString &newImageProviderPath);

    static void clear(Image *image);

signals:
    void imageIdChanged();
    void imagePathChanged();
    void imageTextChanged();
    void savedDateChanged();
    void imageProviderPathChanged();

private:
    int mImageId = -1;
    QString mImagePath;
    QString mImageProviderPath;
    QString mImageText;
    QDateTime mSavedDate;

};

#endif // IMAGE_H
