#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "ScreenGrabCore_global.h"
#include <QObject>
#include "recentimagemodel.h"
#include "imageprovider.h"
#include "langmodel.h"

class SCREENGRABCORE_EXPORT MainController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Image *image READ image CONSTANT)
    Q_PROPERTY(RecentImageModel *recentImageModel READ getRecentImageModel CONSTANT)
    Q_PROPERTY(LangModel *langModel READ getLangModel CONSTANT)
    Q_PROPERTY(ImageProvider *imageProvider READ getImageProvider CONSTANT)
    Q_PROPERTY(bool isExtracting READ getIsExtracting  NOTIFY extractionStatusChanged)
public:
    MainController(QObject *parent=nullptr);

    ImageProvider *getImageProvider();
    Image *image();
private:
    RecentImageModel *recentImageModel;
    LangModel *langModel;
    ImageProvider *imageProvider;
    Image *mImage;
    bool isExtracting = false;
    QString mLangModel;


signals:
    void selection();
    void captureScreen();
    void imageView();
    void startExtraction(const QString &langModel);
    void extractionStatusChanged();

public slots:
    void onCaptured(QImage &img);
    void onImageSelected(const QUrl &imgPath);
    void onSave(const QUrl &fileName);
    void onSave();
    QString imageDefaultName();
    QString pictureFolder();
    QString homeDir();
    void quit();
    void recentImageSelected(int imageId, QString path, QString text, QDateTime dateTime);
    void recentImageSelected(int index);
    void onTextExtracted(const QString &text);
    void onLangModelChange(const QString &langModel);
    void addNewLanguage(const QUrl &langPath, const QString &language);
    void rotateImage(int angle);
    void removeRecentImage(int index, bool withFile=false);
    void toClipboard(const QString &txt);

public:
    RecentImageModel *getRecentImageModel() const;
    LangModel *getLangModel() const;
    ImageProvider *getImageProvider() const;
    Q_INVOKABLE QString version() const;
    bool getIsExtracting() const;
    void setIsExtracting(bool newIsExtracting);
};

#endif // MAINCONTROLLER_H
